#include "GLT/GL/Shader.hpp"
using namespace GLT;


// Standard
#include <fstream>
#include <iostream>


// Constructor, from file path
Shader::Shader(GLenum const type, std::string const path) {

  // Set up type information
  this->glName = glCreateShader(type);

  // Load the shader source
  this->FromFile(path);
}


// Load shader from source string
void Shader::FromSource(std::string const source) {

  // Compile the shader
  char const * scrPtr = source.c_str();
  glShaderSource(this->glName, 1, &scrPtr, NULL);
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


// Load shader from file
void Shader::FromFile(std::string const path) {

  // Open the file
  std::ifstream fp(path, std::ios::in);
  if(!fp.is_open()) {
    std::cout << "Failed to open shader source file: '" << path << "'\n";
    exit(1);
  }

  // Get the sourcecode from the file
  std::string line, source;
  while(getline(fp, line)) {
    source += line + "\n";
  }

  // Compile the source
  std::cout << "Compiling shader '" << path << "' - ";
  this->FromSource(source);

  // Close the file
  fp.close();
}


// Reference counted destructor
Shader::~Shader(void) {
  if(!this->ReferencedElsewhere()) {
    glDeleteShader(this->glName);
  }
}
