#include "GLT/GL/RenderBuffer.hpp"
using namespace GLT;


// Stack for renderbuffer bind target
ElementStack<RenderBuffer> RenderBuffer::bindStack;


// Initialise bind stack
void RenderBuffer::Init() {
  bindStack.Clear();
  bindStack.Push(RenderBuffer(0));
  glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


// Initialise from parameters
RenderBuffer::RenderBuffer(
  GLenum const format,
  unsigned const width,
  unsigned const height) {

  // Generate a name and assign storage
  glGenRenderbuffers(1, &this->glName);
  this->Storage(format, width, height);
}


// Assign storage for render buffer
void RenderBuffer::Storage(
  GLenum const format,
  unsigned const width,
  unsigned const height) {

  this->Bind();
  glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
  this->Unbind();
}


// Bind render buffer
void RenderBuffer::Bind() const {

  // If the currently bound buffer is not this one, bind this buffer
  if(this->glName != bindStack.Top().GetGlName()) {
    glBindRenderbuffer(GL_RENDERBUFFER, this->glName);
  }

  // Push this buffer onto the bind stack
  bindStack.Push(*this);
}


// Unbind render buffer
void RenderBuffer::Unbind() const {

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glName != bindStack.Top().GetGlName()) {
    std::cerr << "ERROR: Attempt to unbind already unbound renderbuffer\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this object off the bind stack
  bindStack.Pop();

  // Restore the binding to what it was previously (if neccessary)
  if(bindStack.Top().GetGlName() != this->glName) {
    glBindRenderbuffer(GL_RENDERBUFFER, bindStack.Top().GetGlName());
  }
}


// Reference counted destructor
RenderBuffer::~RenderBuffer() {
  if(!this->ReferencedElsewhere()) {
    glDeleteRenderbuffers(1, &this->glName);
  }
}
