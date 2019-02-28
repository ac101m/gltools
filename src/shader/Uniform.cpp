#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Constructor, nil
Uniform::Uniform(void) {
  this->size = 0;
  this->type = 0;
  this->handle = 0;
  this->data = (void*)0;
}


// Constructor, initialising
Uniform::Uniform(GLint const size,
                 GLenum const type,
                 GLuint const handle,
                 void const * const data) {

  // Initialise basic data
  this->size = size;
  this->type = type;
  this->handle = handle;

  // Allocate memory for uniform
  this->AllocateDataMemory();
}


// Allocate data memory
void Uniform::AllocateDataMemory(void) {
  unsigned dataElementSize;

  // Calculate datatype size, default to 1 for now
  dataElementSize = 1;

  unsigned bytes = this->size * dataElementSize;
  this->data = new char[bytes];
}


// Destructor eallocates memory
Uniform::~Uniform(void) {
  if(!this->ReferencedElsewhere()) {
    if(this->data) {
      delete [] this->data;
    }
  }
}
