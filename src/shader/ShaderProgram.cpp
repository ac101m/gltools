#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Constructor
ShaderProgram::ShaderProgram(GLuint glHandle) {
  this->handle = glHandle;
}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  glDeleteProgram(this->handle);
}
