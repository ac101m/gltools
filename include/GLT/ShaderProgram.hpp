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

    // Reference count for shader deletion
    RefCount refCount;

    // OpenGL handle & reference counter
    GLuint glHandle;

  private:

    // Links an array of shaders into this program
    void LinkShaders(std::vector<Shader>& shaders);

  public:

    // Constructor
    ShaderProgram(std::vector<Shader> shaders);
    ShaderProgram(std::vector<Shader> shaders, Context& context);

    // Use this shader program
    void Use(void);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
