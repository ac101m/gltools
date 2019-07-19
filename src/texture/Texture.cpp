#include <GLT/Texture.hpp>
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include <GLT/stb_image.h>


// Standard
#include <iostream>


// This project
#include <GLT/ElementCache.hpp>


// Texture cache
ElementCache<std::string, Texture> fileCache;


// Texture binding stack
ElementStack<GLuint> Texture::bindStack;


// Initialise static members (cache and bind stack)
void Texture::Init() {

  // Initially the default texture is bound
  bindStack.Clear();
  bindStack.Push(0);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Empty the texture cache
  fileCache.Clear();
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


// Set texture data from raw pointer
void Texture::SetData(
  int const width,
  int const height,
  unsigned char const * const data,
  unsigned const mipMapLevel) {

  this->Bind();

  // Texture data
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

  this->Unbind();
}


// Set texture data from vector of chars
void Texture::SetData(
  int const width,
  int const height,
  std::vector<unsigned char> const data,
  unsigned const mipMapLevel) {

  this->SetData(width, height, data.data());
}


// Bind texture and add it to the top of the bind stack
// Call glBindTexture if appropriate
void Texture::Bind() const {

  // If the currently bound texture is not this one, bind this texture
  if(this->glHandle != bindStack.Top()) {
    glBindTexture(GL_TEXTURE_2D, this->glHandle);
  }

  // Push this textures glhandle onto the bind stack
  bindStack.Push(this->glHandle);
}


// Unbind texture and bind the last thing that was bound
void Texture::Unbind() const {

  // Can't unbind a texture that isn't bound, without leaving the bind
  // stack in an invalid state
  if(this->glHandle != bindStack.Top()) {
    std::cerr << "ERROR: Attempt to unbind already unbound texture\n";
    std::cerr << "Did you forget to unbind a texture somewhere?\n";
    exit(1);
  }

  // Pop this textures opengl handle off the bind stack
  bindStack.Pop();

  // If the last bound opengl handle was not this textures
  if(bindStack.Top() != this->glHandle) {
    glBindTexture(GL_TEXTURE_2D, bindStack.Top());
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
