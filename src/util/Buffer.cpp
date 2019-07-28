#include "GLT/Buffer.hpp"
using namespace GLT;


// Standard
#include <iostream>


// Default buffer usage hint
GLenum Buffer::defaultUsageHint = GL_STATIC_DRAW;


// Bind target stacks
ElementStack<Buffer> Buffer::bindStack_GL_ARRAY_BUFFER;
ElementStack<Buffer> Buffer::bindStack_GL_ELEMENT_ARRAY_BUFFER;


// Return a reference to the stack specified by
ElementStack<Buffer>& Buffer::GetTargetStack(GLenum const bindTarget) {
  switch(bindTarget) {
    case GL_ARRAY_BUFFER:
      return bindStack_GL_ARRAY_BUFFER;
    case GL_ELEMENT_ARRAY_BUFFER:
      return bindStack_GL_ELEMENT_ARRAY_BUFFER;
    default:
      std::cerr << "ERROR, Buffer bind target '";
      std::cerr << bindTarget << "' not recognised\n";
      exit(1);
  }
}


// Initialise bind target stacks
void Buffer::Init() {

  // GL_ARRAY_BUFFER
  bindStack_GL_ARRAY_BUFFER = ElementStack<Buffer>();
  bindStack_GL_ARRAY_BUFFER.Push(Buffer(0));
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // GL_ELEMENT_ARRAY_BUFFER
  bindStack_GL_ELEMENT_ARRAY_BUFFER = ElementStack<Buffer>();
  bindStack_GL_ELEMENT_ARRAY_BUFFER.Push(Buffer(0));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


// Bind the buffer and remember the state of the current binding
void Buffer::Bind(GLenum const bindTarget) {

  // Get reference to apropriate bind stack
  ElementStack<Buffer>& bindStack = GetTargetStack(bindTarget);

  // If the currently bound buffer is not this one, bind this buffer
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    glBindBuffer(bindTarget, this->glHandle);
  }

  // Push this buffer onto the bind stack
  bindStack.Push(*this);
}


// Unbind the buffer and restore the previous binding
void Buffer::Unbind(GLenum const bindTarget) {

  // Get reference to apropriate bind stack
  ElementStack<Buffer>& bindStack = GetTargetStack(bindTarget);

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    std::cerr << "ERROR: Attempt to unbind already unbound buffer\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this object off the bind stack
  bindStack.Pop();

  // Restore the binding to what it was previously (if neccessary)
  if(bindStack.Top().GetGlHandle() != this->glHandle) {
    glBindBuffer(bindTarget, bindStack.Top().GetGlHandle());
  }
}


// Reference counted destructor
Buffer::~Buffer() {
  if(!this->ReferencedElsewhere()) {
    glDeleteBuffers(1, &this->glHandle);
  }
}
