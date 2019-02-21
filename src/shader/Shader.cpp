#include <GLT/Shader.hpp>
using namespace GLT;


// Standard
#include <fstream>
#include <iostream>


// Common initialisation for constructors
void Shader::Init(ShaderType type, std::string path, Context& context) {

  // Set up type information
  this->type = type;
  this->glHandle = context.NewShaderHandle(this->type);

  // Load the shader source
  this->LoadSource(path);

  // Compile the shader
  std::cout << "Compiling shader '" << path << "' - ";
  this->Compile();
}


// Generates debug prints
void Shader::Compile(void) {

  // Perform compilation
  const char * srcPtr = this->source.c_str();
  glShaderSource(this->glHandle, 1, &srcPtr, NULL);
  glCompileShader(this->glHandle);

  // Get error log status
  GLint result = GL_FALSE; int logLength = 0;
  glGetShaderiv(this->glHandle, GL_COMPILE_STATUS, &result);
	glGetShaderiv(this->glHandle, GL_INFO_LOG_LENGTH, &logLength);

  // Print log output if there were errors
	if(!logLength) {
    std::cout << "SUCCESS\n";
  } else {
    std::cout << "ERROR:\n";
		std::vector<char> log(logLength + 1);
		glGetShaderInfoLog(this->glHandle, logLength, NULL, &log[0]);
    std::cout << &log[0] << "\n";
	}
}


// Constructor, specified context
Shader::Shader(ShaderType type, std::string path, Context& context) {
  this->Init(type, path, context);
}


// Constructor, default context
Shader::Shader(ShaderType type, std::string path) {
  this->Init(type, path, defaultContext);
}


// Gets file from string
void Shader::LoadSource(std::string path) {

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
void Shader::SetSource(std::string src) {
  this->source = src;
}


// Deconstruct
Shader::~Shader(void) {
  if(this->refCount.GetCount() == 0) {
    glDeleteShader(this->glHandle);
  }
}
