#include "GLT/GL/Texture.hpp"
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include "GLT/Extern/stb_image.h"


// Standard
#include <iostream>


// Texture cache
ElementCache<std::string, Texture> Texture::fileCache;


// Texture binding stack
ElementStack<Texture> Texture::bindStack;


// Initialise static members (cache and bind stack)
void Texture::Init() {

  // Initially the default texture is bound
  bindStack.Clear();
  bindStack.Push(GLT::Texture(0));
  glBindTexture(GL_TEXTURE_2D, 0);

  // Empty the texture cache
  fileCache.Clear();
}


// Constructor, from pre initialised GLuint
Texture::Texture(GLuint const textureHandle) {
  this->glHandle = textureHandle;
}


// Constructor, full initialisation
Texture::Texture(
  GLint const mipMapLevel,
  GLint const internalFormat,
  GLsizei const width,
  GLsizei const height,
  GLenum const format,
  GLenum const type,
  GLvoid const * data) {

  // Generate and bind handle
  glGenTextures(1, &this->glHandle);
  this->Bind();

  // Generate our texture
  glTexImage2D(
    GL_TEXTURE_2D,
    mipMapLevel,
    internalFormat,
    width,
    height,
    0,
    format,
    type,
    data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  this->Unbind();
}


// Constructor, loads the image from file
Texture::Texture(
  std::string const path,
  unsigned const mipMapLevel) {

  std::cout << "Loading texture '" << path << "' - ";

  // Check the texture cache first
  if(fileCache.Contains(path)) {
    *this = fileCache.Get(path);
    std::cout << "CACHED\n";
    return;
  }

  // Load image data
  int width, height, channelCount;
  unsigned char* data = stbi_load(
    path.c_str(),
    &width, &height,
    &channelCount, 0);

  // Only continue if the texture load was successful
  if(!data) {
    std::cout << "ERROR\n";
    std::cout << "stbi_load failure. Unsupported texture format?\n";
    exit(1);
  }

  // Load the texture
  glGenTextures(1, &this->glHandle);
  this->SetData(width, height, data, mipMapLevel);

  // Done with the texture data
  stbi_image_free(data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  if(mipMapLevel) {
    this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  } else {
    this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  // Add the texture to the texture cache
  fileCache.Add(path, *this);

  // Loading complete
  std::cout << "SUCCESS\n";
}


// Constructor, loads image from string of bytes
Texture::Texture(
  int const width,
  int const height,
  std::vector<unsigned char> const data) {

  glGenTextures(1, &this->glHandle);
  this->SetData(width, height, data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


// Set texture data from raw pointer
void Texture::SetData(
  int const width,
  int const height,
  unsigned char const * const data,
  unsigned const mipMapLevel) {

  // Texture data
  this->Bind();
  glTexImage2D(
    GL_TEXTURE_2D,
    0, GL_RGB,
    width, height,
    0, GL_RGB,
    GL_UNSIGNED_BYTE,
    data);

  // Generate mipmaps if apropriate
  if(mipMapLevel) {
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  // Restore binding
  this->Unbind();
}


// Set texture data from vector of chars
void Texture::SetData(
  int const width,
  int const height,
  std::vector<unsigned char> const data,
  unsigned const mipMapLevel) {

  this->SetData(width, height, data.data(), mipMapLevel);
}


// Bind this texture and remember the state of the current binding
void Texture::Bind() const {

  // If the currently bound texture is not this one, bind this texture
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    glBindTexture(GL_TEXTURE_2D, this->glHandle);
  }

  // Push this textures object onto the bind stack
  bindStack.Push(*this);
}


// Restore the texture bind target to its previous state
void Texture::Unbind() const {

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    std::cerr << "ERROR: Attempt to unbind already unbound texture\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this texture off the bind stack
  bindStack.Pop();

  // Restore the previous binding
  if(bindStack.Top().GetGlHandle() != this->glHandle) {
    glBindTexture(GL_TEXTURE_2D, bindStack.Top().GetGlHandle());
  }
}


// Set texture integer parameter
void Texture::Parameteri(GLenum const pname, GLint const param) {
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D, pname, param);
  this->Unbind();
}


// Reference counting destructor
Texture::~Texture() {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glHandle);
  }
}
