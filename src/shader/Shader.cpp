#include <GLT/Shader.hpp>
using namespace GLT;


// Standard
#include <fstream>
#include <iostream>
using namespace std;


// Constructor, load shader from file
Shader::Shader(const string path, const ShaderType type) {

  // Set up type information
  this->type = type;
  this->handle = glCreateShader(this->type);

  // Load the shader source
  this->LoadSource(path);
}


// Gets file from string
void Shader::LoadSource(const string path) {

  // Open the file
  ifstream fp(path, ios::in);
  if(!fp.is_open()) {
    std::cout << "SHADER: Could not open shader source '" << path << "'\n";
    exit(1);
  }

  // Get the source from the file
  string line, source;
  while(getline(fp, line)) {
    source += line + "\n";
  }

  // Close the file stream
  this->SetSource(source);
  fp.close();
}


// Set shader source
void Shader::SetSource(const string src) {
  this->source = src;
  const char * srcPtr = this->source.c_str();
  glShaderSource(this->handle, 1, &srcPtr, NULL);
}


// Deconstruct
Shader::~Shader(void) {
  this->source = "";
  glDeleteShader(this->handle);
}
