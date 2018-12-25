#include <GLT/Shader.hpp>
using namespace GLT;


// Standard
#include <fstream>


// Set shader source
void Shader::SetSource(const string src) {
  this->source = src;
}


// Gets file from string
void Shader::LoadSource(const string path) {
  this->SetSource("nope");
}


// Constructor, load shader from file
Shader::Shader(const string path, const GLenum type) {
  this->LoadSource(path);
  char const * ptr = this->source.c_str();
  this->handle = glCreateShader(this->type = type);
  glShaderSource(this->handle, 1, &ptr, NULL);
}
