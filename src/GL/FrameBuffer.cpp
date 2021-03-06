#include "GLT/GL/FrameBuffer.hpp"
using namespace GLT;


// Bind stacks
ElementStack<FrameBuffer> FrameBuffer::bindStack_GL_DRAW_FRAMEBUFFER;
ElementStack<FrameBuffer> FrameBuffer::bindStack_GL_READ_FRAMEBUFFER;


// Initialise bind stacks
void FrameBuffer::Init() {

  // Draw framebuffer target
  bindStack_GL_DRAW_FRAMEBUFFER.Clear();
  bindStack_GL_DRAW_FRAMEBUFFER.Push(FrameBuffer(0));
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  // Read framebuffer target
  bindStack_GL_READ_FRAMEBUFFER.Clear();
  bindStack_GL_READ_FRAMEBUFFER.Push(FrameBuffer(0));
  glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}


// Get reference to apropriate bind stack
ElementStack<FrameBuffer>& FrameBuffer::GetTargetStack(GLenum const bindTarget) {
  switch(bindTarget) {
    case GL_DRAW_FRAMEBUFFER:
      return bindStack_GL_DRAW_FRAMEBUFFER;
    case GL_READ_FRAMEBUFFER:
      return bindStack_GL_READ_FRAMEBUFFER;
    default:
      std::cerr << "ERROR, Framebuffer bind target '";
      std::cerr << bindTarget << "' not recognised\n";
      exit(1);
  }
}


// Check for completeness, error if not
void FrameBuffer::VerifyCompleteness() {
  this->Bind(GL_FRAMEBUFFER);
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "Error, frame buffer incomplete, errorcode: ";
    std::cout << glCheckFramebufferStatus(GL_FRAMEBUFFER) << "\n";
    exit(1);
  }
  this->Unbind(GL_FRAMEBUFFER);
}


// Update color attachments
void FrameBuffer::UpdateColorAttachments() {
  this->Bind(GL_FRAMEBUFFER);

  // Attach all textures to renderbuffer
  GLenum attachmentIndices[this->colorAttachments->size()];
  for(unsigned i = 0; i < this->colorAttachments->size(); i++) {
    attachmentIndices[i] = GL_COLOR_ATTACHMENT0 + i;
    glFramebufferTexture2D(
      GL_FRAMEBUFFER,
      GL_COLOR_ATTACHMENT0 + i,
      GL_TEXTURE_2D,
      (*this->colorAttachments)[i].GetGlName(), 0);
  }

  // Update draw buffer attachment points
  glDrawBuffers(this->colorAttachments->size(), attachmentIndices);
  this->Unbind(GL_FRAMEBUFFER);
}


// Void constructor, generates new name
FrameBuffer::FrameBuffer() {
  glGenFramebuffers(1, &this->glName);
  this->colorAttachments = new std::vector<Texture2D>();
}


// Constructor, direct from name
FrameBuffer::FrameBuffer(GLuint const glName) : GlObject(glName) {

  // [TODO] figure out how to get attachments from the frame buffer name
  this->colorAttachments = new std::vector<Texture2D>();
}


// Constructor, full
FrameBuffer::FrameBuffer(
  unsigned const width,
  unsigned const height,
  std::vector<Texture2D> const colorBuffers) {

  // Allocate colour buffer texture storage
  this->colorAttachments = new std::vector<Texture2D>();

  // Construct framebuffer object
  glGenFramebuffers(1, &this->glName);
  this->Bind(GL_FRAMEBUFFER);

  // Add color buffers to textures
  std::vector<GLuint> attachments(colorBuffers.size());
  for(unsigned i = 0; i < colorBuffers.size(); i++) {

    // Attach color buffers
    this->AttachTexture2D(colorBuffers[i]);

    // Add attachment indices
    attachments[i] = GL_COLOR_ATTACHMENT0 + i;
  }

  // Add attachments to buffer
  glDrawBuffers(attachments.size(), attachments.data());

  // Completeness check
  this->VerifyCompleteness();

  this->Unbind(GL_FRAMEBUFFER);
}


// Attach a texture as a colour buffer
void FrameBuffer::AttachTexture2D(Texture2D const texture) {
  this->colorAttachments->push_back(texture);
  this->UpdateColorAttachments();

  // Check for oopsies
  this->VerifyCompleteness();
}


// Attach a renderbuffer
void FrameBuffer::AttachRenderBuffer(
  RenderBuffer const renderBuffer,
  GLenum const attachmentType) {

  this->Bind(GL_FRAMEBUFFER);
  glFramebufferRenderbuffer(
    GL_FRAMEBUFFER,
    attachmentType,
    GL_RENDERBUFFER,
    renderBuffer.GetGlName());
  this->Unbind(GL_FRAMEBUFFER);

  // Check for oopsies
  this->VerifyCompleteness();
}


// Clear method
void FrameBuffer::Clear(GLbitfield const mask) {
  this->Bind(GL_FRAMEBUFFER);
  glClear(mask);
  this->Unbind(GL_FRAMEBUFFER);
}


// Bind and record current binding
void FrameBuffer::Bind(GLenum const bindTarget) {

  // If the bind target is GL_FRAMEBUFFER, bind both targets. This works
  // because binding GL_DRAW_FRAMEBUFFER will also bind GL_FRAMEBUFFER
  // At least from my experimentation.
  if(bindTarget == GL_FRAMEBUFFER) {
    this->Bind(GL_DRAW_FRAMEBUFFER);
    this->Bind(GL_READ_FRAMEBUFFER);
    return;
  }

  // Get reference to apropriate bind stack
  ElementStack<FrameBuffer>& bindStack = GetTargetStack(bindTarget);

  // If the currently bound buffer is not this one, bind this buffer
  if(this->glName != bindStack.Top().GetGlName()) {
    glBindFramebuffer(bindTarget, this->glName);
  }

  // Push this buffer onto the bind stack
  bindStack.Push(*this);
}


// Unbind and restore previous binding
void FrameBuffer::Unbind(GLenum const bindTarget) {

  // If the bind target is GL_FRAMEBUFFER, unbind both targets. This works
  // because binding GL_DRAW_FRAMEBUFFER will also bind GL_FRAMEBUFFER
  // At least from my experimentation.
  if(bindTarget == GL_FRAMEBUFFER) {
    this->Unbind(GL_DRAW_FRAMEBUFFER);
    this->Unbind(GL_READ_FRAMEBUFFER);
    return;
  }

  // Get reference to apropriate bind stack
  ElementStack<FrameBuffer>& bindStack = GetTargetStack(bindTarget);

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glName != bindStack.Top().GetGlName()) {
    std::cerr << "ERROR: Attempt to unbind already unbound framebuffer\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this object off the bind stack
  bindStack.Pop();

  // Restore the binding to what it was previously (if neccessary)
  if(bindStack.Top().GetGlName() != this->glName) {
    glBindFramebuffer(bindTarget, bindStack.Top().GetGlName());
  }
}


// Reference counted destructor
FrameBuffer::~FrameBuffer() {
  if(!this->ReferencedElsewhere()) {
    glDeleteFramebuffers(1, &this->glName);
    delete colorAttachments;
  }
}
