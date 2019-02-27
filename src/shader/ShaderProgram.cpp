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
    std::cout << &log[0] << "\n";
	}

  // Detach the shaders
  for(unsigned i = 0; i < shaders.size(); i++) {
    glDetachShader(this->glHandle, shaders[i].GetGlHandle());
  }
}


// Fill uniform cache with data
void ShaderProgram::LocateUniforms(void) {
	this->uniformMap->clear();

	// Get uniform count
	GLint uniformCount = 0;
	glGetProgramiv(this->glHandle, GL_ACTIVE_UNIFORMS, &uniformCount);

	// Struct to contain uniform data
	uniform_t uniformData;

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
			&uniformData.size,
			&uniformData.type,
			nameBuf
		);

		// Get GL handle for uniform (redundant? i good enough?)
		uniformData.handle = glGetUniformLocation(this->glHandle, nameBuf);

		// Print out uniform stuff, temporary, to confirm the above
		std::cout << i << " - Found uniform '" << nameBuf;
		std::cout << "', length " << uniformData.size;
		std::cout << ", handleID " << uniformData.handle << "\n";

		// Add the uniform to the uniform map
		this->uniformMap->insert(
			std::pair<std::string, uniform_t>(std::string(nameBuf), uniformData));
	}
}


// Get uniform by name
uniform_t ShaderProgram::GetUniform(std::string& name) {
	this->Use();
	if(this->uniformMap->find(name) != this->uniformMap->end()) {
		return (*(this->uniformMap))[name];
	} else {
		std::cout << "Error, uniform '" << name << "' does not exist\n";
		exit(1);
	}
}

// Common initialisation
void ShaderProgram::Init(std::vector<Shader>& shaders, Context& context) {
	this->glHandle = context.NewShaderProgramHandle();
  this->LinkShaders(shaders);
	this->uniformMap = new std::map<std::string, uniform_t>;
	this->LocateUniforms();
}

// Constructor, default context
ShaderProgram::ShaderProgram(std::vector<Shader> shaders) {
  this->Init(shaders, defaultContext);
}


// Constructor, custom context
ShaderProgram::ShaderProgram(std::vector<Shader> shaders, Context& context) {
  this->Init(shaders, context);
}


// Bind a texture to a uniform
void ShaderProgram::SetTexture(unsigned texUnit, std::string name, Texture tex) {
	uniform_t uniform = this->GetUniform(name);
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glUniform1i(uniform.handle, texUnit);
	tex.Bind();
}


// Set 3 element vector uniform
void ShaderProgram::SetVec3(std::string name, glm::vec3 value) {
	uniform_t uniform = this->GetUniform(name);
	glUniform3f(uniform.handle, value.x, value.y, value.z);
}


// Set matrix uniform
void ShaderProgram::SetMat3(std::string name, glm::mat3 value) {
	uniform_t uniform = this->GetUniform(name);
	glUniformMatrix3fv(uniform.handle, 1, GL_FALSE, &value[0][0]);
}


// Set matrix uniform
void ShaderProgram::SetMat4(std::string name, glm::mat4 value) {
	uniform_t uniform = this->GetUniform(name);
	glUniformMatrix4fv(uniform.handle, 1, GL_FALSE, &value[0][0]);
}


// Use this shader program
void ShaderProgram::Use(void) {
  glUseProgram(this->glHandle);
}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  if(!this->ReferencedElsewhere()) {
		delete this->uniformMap;
    glDeleteProgram(this->glHandle);
  }
}
