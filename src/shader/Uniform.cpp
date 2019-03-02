#include <GLT/ShaderProgram.hpp>
using namespace GLT;


// Null uniform
#define GLT_NULL_UNIFORM 0


// Get the size of the datatype
unsigned Uniform::GetTypeSize(GLenum const type) {
  switch(type) {
    case GLT_NULL_UNIFORM:
      return 0;
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_SAMPLER_2D:
    case GL_SAMPLER_CUBE:
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
      std::cout << "Shader uniform error, type enum value " << type;
      std::cout << " not recognised\n";
      exit(1);
  }
}


// Get the size of the datatype
std::string Uniform::GetTypeName(GLenum const type) {
  switch(type) {
    case GLT_NULL_UNIFORM:      return "GLT_NULL_UNIFORM";
    case GL_SAMPLER_2D:         return "GL_SAMPLER_2D";
    case GL_SAMPLER_CUBE:       return "GL_SAMPLER_CUBE";
    case GL_FLOAT:              return "GL_FLOAT";
    case GL_INT:                return "GL_INT";
    case GL_UNSIGNED_INT:       return "GL_UNSIGNED_INT";
    case GL_FLOAT_VEC2:         return "GL_FLOAT_VEC2";
    case GL_INT_VEC2:           return "GL_INT_VEC2";
    case GL_UNSIGNED_INT_VEC2:  return "GL_UNSIGNED_INT_VEC2";
    case GL_DOUBLE:             return "GL_DOUBLE";
    case GL_FLOAT_VEC3:         return "GL_FLOAT_VEC3";
    case GL_INT_VEC3:           return "GL_INT_VEC3";
    case GL_UNSIGNED_INT_VEC3:  return "GL_UNSIGNED_INT_VEC3";
    case GL_FLOAT_VEC4:         return "GL_FLOAT_VEC4";
    case GL_FLOAT_MAT2:         return "GL_FLOAT_MAT2";
    case GL_INT_VEC4:           return "GL_INT_VEC4";
    case GL_UNSIGNED_INT_VEC4:  return "GL_UNSIGNED_INT_VEC4";
    case GL_DOUBLE_VEC2:        return "GL_DOUBLE_VEC2";
    //case GL_FLOAT_MAT2x3:
    //case GL_FLOAT_MAT3x2:
    case GL_DOUBLE_VEC3:        return "GL_DOUBLE_VEC3";
    //case GL_FLOAT_MAT2x4:
    //case GL_FLOAT_MAT4x2:
    case GL_DOUBLE_VEC4:        return "GL_DOUBLE_VEC4";
    case GL_DOUBLE_MAT2:        return "GL_DOUBLE_MAT2";
    case GL_FLOAT_MAT3:         return "GL_FLOAT_MAT3";
    //case GL_FLOAT_MAT3x4:
    //case GL_FLOAT_MAT4x3:
    //case GL_DOUBLE_MAT2x3:
    //case GL_DOUBLE_MAT3x2:
    case GL_FLOAT_MAT4:         return "GL_FLOAT_MAT4";
    //case GL_DOUBLE_MAT2x4:
    //case GL_DOUBLE_MAT4x2:
    case GL_DOUBLE_MAT3:        return "GL_DOUBLE_MAT3";
    //case GL_DOUBLE_MAT3x4:
    //case GL_DOUBLE_MAT4x3:
    case GL_DOUBLE_MAT4:        return "GL_DOUBLE_MAT4";
    default:
      std::cout << "Shader uniform error, type enum value " << type;
      std::cout << " not recognised\n";
      exit(1);
  }
}


// Constructor, nil
Uniform::Uniform(void) {
  this->handle = 0;
  this->type = GLT_NULL_UNIFORM;
  this->elemCount = 0;
  this->buf = (void*)0;
  this->bufSize = 0;
  this->name = new std::string(this->GetTypeName(this->type));
}


// Constructor, initialising
Uniform::Uniform(std::string const name,
                 GLuint const handle,
                 GLenum const type,
                 GLint const elemCount) :
                 handle(handle), type(type), elemCount(elemCount) {

  // Initialise the uniform name
  this->name = new std::string(name);

  // TODO
  if(elemCount != 1) {
    std::cout << "Shader uniform error, multi-element uniforms not implemented!\n";
    exit(1);
  }

  // Allocate memory for uniform
  this->AllocateBuffer();
}


// Allocate data memory
void Uniform::AllocateBuffer(void) {
  this->bufSize = this->elemCount * GetTypeSize(this->type);
  this->buf = new char[this->bufSize];
  for(unsigned i = 0; i < this->bufSize; i++) {
    ((char*)this->buf)[i] = 0;
  }
}


// Type check
void Uniform::AssertType(GLenum const type) {
  if(this->type != type) {
    std::cout << "Error, shader uniform '" << *(this->name) << "' ";
    std::cout << "expects " << this->GetTypeName(this->type);
    std::cout << ", but got " << this->GetTypeName(type) << "\n";
    exit(1);
  }
}


// Data buffer size check
void Uniform::AssertDataSize(unsigned const size) {
  if(this->bufSize != size) {
    std::cout << "Shader uniform error, size mismatch\n";
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
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_SAMPLER_2D, sizeof(int));
  if(value != *((int*)this->buf)) {
     glUniform1i(this->handle, value);
     *((int*)this->buf) = value;
  }
}


// single integer
void Uniform::SetTexCube(int const value) {
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_SAMPLER_CUBE, sizeof(int));
  if(value != *((int*)this->buf)) {
     glUniform1i(this->handle, value);
     *((int*)this->buf) = value;
  }
}


// single integer
void Uniform::SetF1(float const value) {
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_FLOAT, sizeof(float));
  if(value != *((float*)this->buf)) {
     glUniform1f(this->handle, value);
     *((float*)this->buf) = value;
  }
}


// 3 element float vector
void Uniform::SetFVec3(glm::fvec3 const value) {
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_FLOAT_VEC3, sizeof(glm::fvec3));
  if(value != *((glm::fvec3*)this->buf)) {
	   glUniform3fv(this->handle, 1, &value[0]);
     *((glm::fvec3*)this->buf) = value;
  }
}


// 4 x 4 float matrix
void Uniform::SetFMat3(glm::fmat3 const value) {
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_FLOAT_MAT3, sizeof(glm::fmat3));
  if(value != *((glm::fmat3*)this->buf)) {
	   glUniformMatrix3fv(this->handle, 1, GL_FALSE, &value[0][0]);
     *((glm::fmat3*)this->buf) = value;
  }
}


// 4 x 4 float matrix
void Uniform::SetFMat4(glm::fmat4 const value) {
  if(this->type == GLT_NULL_UNIFORM) return;
  this->AssertMatch(GL_FLOAT_MAT4, sizeof(glm::fmat4));
  if(value != *((glm::fmat4*)this->buf)) {
	   glUniformMatrix4fv(this->handle, 1, GL_FALSE, &value[0][0]);
     *((glm::fmat4*)this->buf) = value;
  }
}


// Destructor, deallocates memory
Uniform::~Uniform(void) {
  if(!this->ReferencedElsewhere()) {
    delete this->name;
    if(this->buf) {
      delete [] (char*)this->buf;
    }
  }
}
