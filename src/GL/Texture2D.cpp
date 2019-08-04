#include "GLT/GL/Texture2D.hpp"
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include "GLT/Extern/stb_image.h"


// Standard
#include <iostream>


// Texture cache
ElementCache<std::string, Texture2D> Texture2D::fileCache;


// Texture binding stack
ElementStack<Texture> Texture2D::bindStack;


// Initialise static members (cache and bind stack)
void Texture2D::Init() {

  // Initially the default texture is bound
  bindStack.Clear();
  bindStack.Push(Texture(0));

  // Empty the texture cache
  fileCache.Clear();
}


// Constructor, full initialisation
Texture2D::Texture2D(
  GLint const mipMapLevel,
  GLint const internalFormat,
  GLsizei const width,
  GLsizei const height,
  GLenum const format,
  GLenum const type,
  GLvoid const * data) {

  // Generate and bind handle
  //glGenTextures(1, &this->glName);
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
Texture2D::Texture2D(
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
  //glGenTextures(1, &this->glName);
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
Texture2D::Texture2D(
  int const width,
  int const height,
  std::vector<unsigned char> const data) {

  //glGenTextures(1, &this->glName);
  this->SetData(width, height, data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


// Set texture data from raw pointer
void Texture2D::SetData(
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
void Texture2D::SetData(
  int const width,
  int const height,
  std::vector<unsigned char> const data,
  unsigned const mipMapLevel) {

  this->SetData(width, height, data.data(), mipMapLevel);
}
