#ifndef _GLT_SHADER_PROGRAM_INCLUDED
#define _GLT_SHADER_PROGRAM_INCLUDED


// This project
#include <GLT/Shader.hpp>


// Standard
#include <string>


namespace GLT {

  class ShaderProgram {
  private:

    // OpenGL handle
    GLuint handle;

  public:

    // Constructor
    ShaderProgram(GLuint glHandle);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);

  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
