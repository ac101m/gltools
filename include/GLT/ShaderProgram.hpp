#ifndef _GLT_SHADER_PROGRAM_INCLUDED
#define _GLT_SHADER_PROGRAM_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Shader.hpp>
#include <GLT/RefCount.hpp>


// Standard
#include <string>
#include <vector>


namespace GLT {

  class ShaderProgram {
  private:

    // OpenGL handle & reference counter
    GLuint glHandle;
    RefCount refCount;

  public:

    // Constructor
    ShaderProgram(void);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);

  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
