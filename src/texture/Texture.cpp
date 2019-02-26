#include <GLT/Texture.hpp>
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include <sdb_image.h>


// Standard
#include <iostream>


// Common initialisation
void Texture::Init(std::string& path, Context& context) {

  // Load the texture from file unless already loaded
  if(!context.TextureLoaded(path)) {
    this->LoadFromFile(path, context);
    context.AddTexture(path, *this);
  } else {
    *this = context.GetLoadedTexture(path);
  }
}


// Load texture from file
void Texture::LoadFromFile(std::string& path, Context& context) {
  std::cout << "Loading texture '" << path << "' - ";

  // Load image data
  int width, height, channelCount;
  unsigned char *data = stbi_load(
    path.c_str(),
    &width, &height,
    &channelCount, 0);

  // Only continue if the texture load was successful
  if(!data) {
    std::cout << "ERROR\n";
    exit(1);
  }

  // Load the texture
  this->glHandle = context.NewTextureHandle();
  this->Bind();

  // Sampling behaviour
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

  // Loading complete
  std::cout << "SUCCESS\n";
}


// Constructor, loads the image from file
Texture::Texture(std::string path) {
  this->Init(path, defaultContext);
}


// Reference counting destructor
Texture::~Texture(void) {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glHandle);
  }
}
