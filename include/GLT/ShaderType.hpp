#ifndef _GLT_SHADERTYPE_INCLUDED
#define _GLT_SHADERTYPE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Shader type enum, matches the opengl values
typedef enum {
  GLT_SHADER_VERTEX = GL_VERTEX_SHADER,
  GLT_SHADER_FRAGMENT = GL_FRAGMENT_SHADER
} ShaderType;


#endif // _GLT_SHADERTYPE_INCLUDED
