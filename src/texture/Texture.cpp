#include <GLT/Texture.hpp>
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include <sdb_image.h>


// Standard
#include <iostream>


// Common initialisation
void Texture::Init(const std::string& path) {

  // Load the texture from file unless already loaded
  this->LoadFromFile(path);
}


// Load texture from file
void Texture::LoadFromFile(const std::string& path) {
  std::cout << "Loading texture '" << path << "' - ";

  // Check the context texture cache first
  if(this->parentContext->TextureCached(path)) {
    *this = this->parentContext->GetTexture(path);
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
    std::cout << "Error, stbi_load failed. Unsupported texture format?\n";
    exit(1);
  }

  // Load the texture
  this->glHandle = this->parentContext->NewTextureHandle();
  this->Bind();

  // Sampling behaviour, may generalize later
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Texture data
  glTexImage2D(
    GL_TEXTURE_2D,
    0, GL_RGB,
    width, height,
    0, GL_RGB,
    GL_UNSIGNED_BYTE,
    data);
  glGenerateMipmap(GL_TEXTURE_2D);
  this->Unbind();

  // Done with the texture data
  stbi_image_free(data);

  // Add the texture to the context texture path
  this->parentContext->AddTexture(path, *this);

  // Loading complete
  std::cout << "SUCCESS\n";
}


// Constructor, loads the image from file
Texture::Texture(const std::string path) :
  parentContext(&defaultContext) {
  this->Init(path);
}


// Reference counting destructor
Texture::~Texture(void) {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glHandle);
  }
}
