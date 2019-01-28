#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Links a list of shaders into this program
void ShaderProgram::LinkShaders(std::vector<Shader>& shaders) {
	std::cout << "Linking shader program - ";

  // Attach the shaders
  for(unsigned i = 0; i < shaders.size(); i++) {
    glAttachShader(this->glHandle, shaders[i].GetGlHandle());
  }

  // Link the program
  glLinkProgram(this->glHandle);

  // Check the program
  GLint result = GL_FALSE; int logLength = 0;
	glGetProgramiv(this->glHandle, GL_LINK_STATUS, &result);
	glGetProgramiv(this->glHandle, GL_INFO_LOG_LENGTH, &logLength);

  // Print out error messages if neccessary
	if(!logLength) {
    std::cout << "SUCCESS\n";
  } else {
    std::cout << "ERROR:\n";
		std::vector<char> log(logLength + 1);
		glGetProgramInfoLog(this->glHandle, logLength, NULL, &log[0]);
    std::cout << log[0] << "\n";
	}

  // Detach the shaders
  for(unsigned i = 0; i < shaders.size(); i++) {
    glDetachShader(this->glHandle, shaders[i].GetGlHandle());
  }
}


// Constructor
ShaderProgram::ShaderProgram(std::vector<Shader> shaders) {
  this->glHandle = defaultContext.NewShaderProgramHandle();
  this->LinkShaders(shaders);
}


// Constructor
ShaderProgram::ShaderProgram(std::vector<Shader> shaders, Context& context) {
  this->glHandle = context.NewShaderProgramHandle();
  this->LinkShaders(shaders);
}


// Use this shader program
void ShaderProgram::Use(void) {
  glUseProgram(this->glHandle);
}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  if(this->refCount.GetCount() == 0) {
    glDeleteProgram(this->glHandle);
  }
}
