#include "GLT/GL/ShaderProgram.hpp"
using namespace GLT;


// Standard
#include <iostream>


// Links a list of shaders into this program
void ShaderProgram::LinkShaders(const std::vector<Shader>& shaders) {
	std::cout << "Linking shader program - ";

  // Attach the shaders
  for(unsigned i = 0; i < shaders.size(); i++) {
    glAttachShader(this->glHandle, shaders[i].GetGlName());
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
    std::cout << &log[0] << "\n";
	}

  // Detach the shaders
  for(unsigned i = 0; i < shaders.size(); i++) {
    glDetachShader(this->glHandle, shaders[i].GetGlName());
  }
}


// Fill uniform cache with data
void ShaderProgram::FillUniformCache(void) {

	// Construct a uniform map
	this->uniformCache = new ElementCache<std::string, Uniform>;

	// Get uniform count
	GLint uniformCount = 0;
	glGetProgramiv(this->glHandle, GL_ACTIVE_UNIFORMS, &uniformCount);

	// Uniform data
	GLuint uniformHandle;
	GLenum uniformType;
	GLint uniformElementCount;

	// Uniform name constants
	const GLsizei nameBufSize = 16;
	GLchar nameBuf[nameBufSize];
	GLsizei nameLength;

	// Add all uniforms and their GLuints to the map so we can find them later
	for(int i = 0; i < uniformCount; i++) {

		// Get our uniform data
		glGetActiveUniform(
			this->glHandle,
			(GLuint)i,
			nameBufSize,
			&nameLength,
			&uniformElementCount,
			&uniformType,
			nameBuf);

		// Get GL handle for uniform (redundant? i good enough?)
		uniformHandle = glGetUniformLocation(this->glHandle, nameBuf);

		// Print out uniform stuff, temporary, to confirm the above
		std::cout << i << " - Found uniform '" << nameBuf;
		std::cout << "', elements " << uniformElementCount;
		std::cout << ", handleID " << uniformHandle;
		std::cout << ", type " << uniformType << "\n";

		// Add the uniform to the cache
		Uniform uniform(std::string(nameBuf),
										uniformHandle,
										uniformType,
										uniformElementCount);
		this->uniformCache->Add(std::string(nameBuf), uniform);
	}
}


// Get uniform by name
Uniform ShaderProgram::GetUniform(const std::string name) {
	this->Use();
	if(this->uniformCache->Contains(name)) {
		return this->uniformCache->Get(name);
	} else {
		std::cout << "Error, shader uniform id '" << name;
		std::cout << "' not found, substituting null uniform\n";
		this->uniformCache->Add(name, Uniform());
		return Uniform();
	}
}

// Constructor, default context
ShaderProgram::ShaderProgram(std::vector<Shader> const shaders) {
	this->glHandle = glCreateProgram();
  this->LinkShaders(shaders);
	this->FillUniformCache();
}


// Bind a texture to a uniform
void ShaderProgram::SetTexture(unsigned const texUnit,
															 std::string const& name,
															 Texture const& tex) {

	glActiveTexture(GL_TEXTURE0 + texUnit);
	this->GetUniform(name).SetTex2D(texUnit);
	tex.Bind();
}


// Use this shader program
void ShaderProgram::Use(void) {
  glUseProgram(this->glHandle);
}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  if(!this->ReferencedElsewhere()) {
		delete this->uniformCache;
    glDeleteProgram(this->glHandle);
  }
}
