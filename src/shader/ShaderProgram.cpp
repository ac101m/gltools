#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Constructor
ShaderProgram::ShaderProgram(void) {

}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  glDeleteProgram(this->glHandle);
}
