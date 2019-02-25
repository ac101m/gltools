#include <GLT/Texture.hpp>
using namespace GLT;


// Image loading
#define STB_IMAGE_IMPLEMENTATION
#include <sdb_image.h>


// Standard
#include <iostream>


// Common initialisation
void Texture::Init(std::string& path, Context& context) {

  // Load image data
  int width, height, channelCount;
  unsigned char *data = stbi_load(
    path.c_str(),
    &width, &height,
    &channelCount, 0);

  // Only continue if the texture load was successful
  if(!data) {
    std::cout << "Error loading texture '" << path << "'\n";
    exit(1);
  }

  // Load the texture
  this->glHandle = context.NewTexture();
  this->Bind();
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
}


// Constructor, loads the image from file
Texture::Texture(std::string path) {
  this->Init(path, defaultContext);
}


// Reference counting destructor
Texture::~Texture(void) {
  if(this->rc.GetCount() == 0) {
    glDeleteTextures(1, &this->glHandle);
  }
}
