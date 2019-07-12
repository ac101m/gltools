#include <GLT/Texture.hpp>
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include <GLT/stb_image.h>


// Standard
#include <iostream>


// Constructor, loads the image from file
Texture::Texture(const std::string path) :
  parentContext(&defaultContext) {

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
    std::cout << "ERROR\n";
    std::cout << "stbi_load failure. Unsupported texture format?\n";
    exit(1);
  }

  // Load the texture
  this->glHandle = this->parentContext->NewTextureHandle();
  this->SetData(width, height, data);

  // Done with the texture data
  stbi_image_free(data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Add the texture to the context texture path
  this->parentContext->AddTexture(path, *this);

  // Loading complete
  std::cout << "SUCCESS\n";
}


// Constructor, loads image from string of bytes
Texture::Texture(int const width, int const height,
                 std::vector<unsigned char> const data) :
                 parentContext(&defaultContext) {

  this->glHandle = this->parentContext->NewTextureHandle();
  this->SetData(width, height, data);

  // Use nearest neighbour filtering by default
  this->Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  this->Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}


// Constructor, full initialisation
Texture::Texture(GLint const mipMapLevel,
                 GLint const internalFormat,
                 GLsizei const width,
                 GLsizei const height,
                 GLenum const format,
                 GLenum const type,
                 GLvoid const * data) :
                 parentContext(&defaultContext) {

  this->glHandle = this->parentContext->NewTextureHandle();
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
}


// Set texture data from raw pointer
void Texture::SetData(
  int const width, int const height,
  unsigned char const * const data) {

  this->Bind();

  // Texture data
  glTexImage2D(
    GL_TEXTURE_2D,
    0, GL_RGB,
    width, height,
    0, GL_RGB,
    GL_UNSIGNED_BYTE,
    data);

  this->Unbind();
}


void Texture::Parameteri(GLenum const pname, GLint const param) {
  this->Bind();
  glTexParameteri(GL_TEXTURE_2D, pname, param);
  this->Unbind();
}


void Texture::GenerateMipmaps(void) {
  this->Bind();
  glGenerateMipmap(GL_TEXTURE_2D);
  this->Unbind();
}


// Set texture data from vector of chars
void Texture::SetData(
  int const width, int const height,
  std::vector<unsigned char> const data) {

  this->SetData(width, height, data.data());
}


// Reference counting destructor
Texture::~Texture(void) {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glHandle);
  }
}
