#include "GLT/GL/CubeMap.hpp"
using namespace GLT;


// Image loading
#include "GLT/Extern/stb_image.h"


// Standard
#include <iostream>


// Load from textures
void CubeMap::FromFiles(std::vector<std::string> const& texPaths) {
  std::cout << "Loading cube map - ";

  // A little initial checking
  if(texPaths.size() < 6) {
    std::cout << "ERROR\n";
    std::cout << "Cube maps require at least 6 textures\n";
    exit(1);
  }

  // Create opengl handles
  glGenTextures(1, &this->glHandle);
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->glHandle);

  // Load the textures
  for(unsigned i = 0; i < 6; i++) {
    int width, height, channelCount;
    unsigned char* data = stbi_load(
      texPaths[i].c_str(),
      &width, &height,
      &channelCount, 0);
    if(!data) {
      std::cout << "ERROR\n";
      std::cout << "stbi_load failure. Unsupported texture format?\n";
      exit(1);
    } else {
      glTexImage2D(
        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
        0, GL_RGB, width, height,
        0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }
  }

  // Sampling behaviour
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  // All is well
  std::cout << "SUCCESS\n";
  if(texPaths.size() > 6) {
    std::cout << "Info, cubemaps only need 6 textures. ";
    std::cout << "the following files were ignored:\n";
    for(unsigned i = 6; i < texPaths.size(); i++) {
      std::cout << "'" << texPaths[i] << "'\n";
    }
  }
}


// Constructor, from paths
CubeMap::CubeMap(std::vector<std::string> const texPaths) {

  // Raw vertex data
  std::vector<float> v = {
    -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f};

   // Step 2, build vector of vertices
   std::vector<vertex_t> vertices;
   for(unsigned i = 0; i < v.size(); i += 3) {
     GLT::vertex_t vertex;
     vertex.position = glm::vec3(v[i], v[i + 1], v[i + 2]);
     vertices.push_back(vertex);
   }

   // Step 3, Indices
   std::vector<unsigned> indices;
   for(unsigned i = 0; i < vertices.size(); i += 4) {
     indices.push_back(i + 2);
     indices.push_back(i + 1);
     indices.push_back(i);
     indices.push_back(i);
     indices.push_back(i + 3);
     indices.push_back(i + 2);
   }

   // Build the vertex buffer and gl cube map
   this->vertexBuffer = VertexArray(vertices, indices);
   this->FromFiles(texPaths);
}


// Default draw routine. Just a polite reminder to the developer
// that they need to provide their own draw code
void __attribute__((weak)) CubeMap::Draw(
  Camera& camera,
  ShaderProgram& shader,
  glm::mat4& m) {

  std::cout << "Error, draw method not specified (GLT::CubeMap)\n";
  std::cout << "Please provide a draw method\n";
  exit(1);
}


// Reference counted destructor
CubeMap::~CubeMap() {
  if(!this->ReferencedElsewhere()) {
    glDeleteTextures(1, &this->glHandle);
  }
}
