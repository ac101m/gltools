#include "GLT/GL/Texture.hpp"
using namespace GLT;


// Bind with arbitrary bind stack and target
void Texture::BindAny(
  GLenum const bindTarget,
  ElementStack<Texture>& bindStack) const {

  // If the currently bound texture is not this one, bind this texture
  if(this->glName != bindStack.Top().GetGlName()) {
    glBindTexture(bindTarget, this->glName);
  }

  // Push this textures object onto the bind stack
  bindStack.Push(*this);
}


// Unbind from arbitrary stack and target
void Texture::UnbindAny(
  GLenum const bindTarget,
  ElementStack<Texture>& bindStack) const {

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glName != bindStack.Top().GetGlName()) {
    std::cerr << "ERROR: Attempt to unbind already unbound texture\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this texture off the bind stack
  bindStack.Pop();

  // Restore the previous binding
  if(bindStack.Top().GetGlName() != this->glName) {
    glBindTexture(GL_TEXTURE_2D, bindStack.Top().GetGlName());
  }
}


// Reference counted destructor
Texture::~Texture() {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glName);
  }
}
