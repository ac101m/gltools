#include "GLT/GL/Shader.hpp"
using namespace GLT;


// Standard
#include <fstream>
#include <iostream>


// Generates debug prints
void Shader::Compile(void) {

  // Perform compilation
  const char * srcPtr = this->source.c_str();
  glShaderSource(this->glName, 1, &srcPtr, NULL);
  glCompileShader(this->glName);

  // Get error log status
  GLint result = GL_FALSE; int logLength = 0;
  glGetShaderiv(this->glName, GL_COMPILE_STATUS, &result);
	glGetShaderiv(this->glName, GL_INFO_LOG_LENGTH, &logLength);

  // Print log output if there were errors
	if(!logLength) {
    std::cout << "SUCCESS\n";
  } else {
    std::cout << "ERROR\n";
		std::vector<char> log(logLength + 1);
		glGetShaderInfoLog(this->glName, logLength, NULL, &log[0]);
    std::cout << &log[0] << "\n";
    exit(1);
	}
}


// Constructor, specified context
Shader::Shader(GLenum const type, std::string const path) {

  // Set up type information
  this->type = type;
  this->glName = glCreateShader(type);

  // Load the shader source
  this->LoadSource(path);

  // Compile the shader
  std::cout << "Compiling shader '" << path << "' - ";
  this->Compile();
}


// Gets file from string
void Shader::LoadSource(const std::string& path) {

  // Open the file
  std::ifstream fp(path, std::ios::in);
  if(!fp.is_open()) {
    std::cout << "Failed to open shader source file: '" << path << "'\n";
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
void Shader::SetSource(const std::string& src) {
  this->source = src;
}


// Reference counted destructor
Shader::~Shader(void) {
  if(!this->ReferencedElsewhere()) {
    glDeleteShader(this->glName);
  }
}
