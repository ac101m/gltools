#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Get the size of the datatype
unsigned Uniform::GetTypeSize(void) {
  switch(this->type) {
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_SAMPLER_2D:
      return 4;
    case GL_FLOAT_VEC2:
    case GL_INT_VEC2:
    case GL_UNSIGNED_INT_VEC2:
    case GL_DOUBLE:
      return 8;
    case GL_FLOAT_VEC3:
    case GL_INT_VEC3:
    case GL_UNSIGNED_INT_VEC3:
      return 12;
    case GL_FLOAT_VEC4:
    case GL_FLOAT_MAT2:
    case GL_INT_VEC4:
    case GL_UNSIGNED_INT_VEC4:
    case GL_DOUBLE_VEC2:
      return 16;
    //case GL_FLOAT_MAT2x3:
    //case GL_FLOAT_MAT3x2:
    case GL_DOUBLE_VEC3:
      return 24;
    //case GL_FLOAT_MAT2x4:
    //case GL_FLOAT_MAT4x2:
    case GL_DOUBLE_VEC4:
    case GL_DOUBLE_MAT2:
      return 32;
    case GL_FLOAT_MAT3:
      return 36;
    //case GL_FLOAT_MAT3x4:
    //case GL_FLOAT_MAT4x3:
    //case GL_DOUBLE_MAT2x3:
    //case GL_DOUBLE_MAT3x2:
    //  return 48;
    case GL_FLOAT_MAT4:
    //case GL_DOUBLE_MAT2x4:
    //case GL_DOUBLE_MAT4x2:
      return 64;
    case GL_DOUBLE_MAT3:
      return 72;
    //case GL_DOUBLE_MAT3x4:
    //case GL_DOUBLE_MAT4x3:
    //  return 96;
    case GL_DOUBLE_MAT4:
      return 128;
    default:
      std::cout << "Uniform error, type enum " << this->type;
      std::cout << " not recognised\n";
      exit(1);
  }
}


// Constructor, nil
Uniform::Uniform(void) {
  this->elemCount = 0;
  this->type = 0;
  this->handle = 0;
  this->data = (void*)0;
}


// Constructor, initialising
Uniform::Uniform(GLuint const handle,
                 GLenum const type,
                 GLint const elemCount) {

  // Initialise basic data
  this->handle = handle;
  this->type = type;
  this->elemCount = elemCount;

  //  Multi-element uniform buffers not yet implemented
  if(elemCount != 1) {
    std::cout << "Uniform error, multi-element uniforms not implemented yet!\n";
    exit(1);
  }

  // Allocate memory for uniform
  this->AllocateDataMemory();
}


// Allocate data memory
void Uniform::AllocateDataMemory(void) {
  this->dataSize = this->elemCount * this->GetTypeSize();
  this->data = new char[this->dataSize];
  for(unsigned i = 0; i < this->dataSize; i++) {
    ((char*)this->data)[i] = 0;
  }
}


// Type check
void Uniform::AssertType(GLenum const type) {
  if(this->type != type) {
    std::cout << "Uniform error, type mismatch\n";
    exit(1);
  }
}


// Data buffer size check
void Uniform::AssertDataSize(unsigned const size) {
  if(this->dataSize != size) {
    std::cout << "Uniform error, size mismatch\n";
    exit(1);
  }
}


// Check data buffer and such
void Uniform::AssertMatch(GLenum const type, unsigned const size) {
  this->AssertType(type);
  this->AssertDataSize(size);
}


// single integer
void Uniform::SetTex2D(int const value) {
  this->AssertMatch(GL_SAMPLER_2D, sizeof(int));
  if(value != *((int*)this->data)) {
     glUniform1i(this->handle, value);
     *((int*)this->data) = value;
  }
}


// 3 element float vector
void Uniform::SetFVec3(glm::fvec3 const value) {
  this->AssertMatch(GL_FLOAT_VEC3, sizeof(glm::fvec3));
  if(value != *((glm::fvec3*)this->data)) {
	   glUniform3fv(this->handle, 1, &value[0]);
     *((glm::fvec3*)this->data) = value;
  }
}


// 4 x 4 float matrix
void Uniform::SetFMat4(glm::fmat4 const value) {
  this->AssertMatch(GL_FLOAT_MAT4, sizeof(glm::fmat4));
  if(value != *((glm::fmat4*)this->data)) {
	   glUniformMatrix4fv(this->handle, 1, GL_FALSE, &value[0][0]);
     *((glm::fmat4*)this->data) = value;
  }
}


// Destructor, deallocates memory
Uniform::~Uniform(void) {
  if(!this->ReferencedElsewhere()) {
    if(this->data) {
      delete [] (char*)this->data;
    }
  }
}
