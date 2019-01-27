#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Constructor
ShaderProgram::ShaderProgram(void) {

}


// Delete the shader program
ShaderProgram::~ShaderProgram(void) {
  if(this->refCount.GetCount() == 0) {
    glDeleteProgram(this->glHandle);
  }
}
