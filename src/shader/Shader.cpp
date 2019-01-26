#include <GLT/Shader.hpp>
using namespace GLT;


// Standard
#include <fstream>
#include <iostream>


// Constructor, specified context
Shader::Shader(ShaderType type, std::string path, Context* context) {

  // Set up type information
  this->type = type;
  this->glHandle = context->NewShaderHandle(this->type);

  // Load the shader source
  this->LoadSource(path);
}


// Constructor, default context
Shader::Shader(ShaderType type, std::string path) {

  // Set up type information
  this->type = type;
  this->glHandle = defaultContext.NewShaderHandle(this->type);

  // Load the shader source
  this->LoadSource(path);
}


// Gets file from string
void Shader::LoadSource(std::string path) {

  // Open the file
  std::ifstream fp(path, std::ios::in);
  if(!fp.is_open()) {
    std::cout << "SHADER: Could not open shader source '" << path << "'\n";
    exit(1);
  }

  // Get the source from the file
  std::string line, source;
  while(getline(fp, line)) {
    source += line + "\n";
  }

  // Close the file stream
  this->SetSource(source);
  fp.close();
}


// Set shader source
void Shader::SetSource(std::string src) {
  this->source = src;
  const char * srcPtr = this->source.c_str();
  glShaderSource(this->glHandle, 1, &srcPtr, NULL);
}


// Deconstruct
Shader::~Shader(void) {
  this->source = "";
}
