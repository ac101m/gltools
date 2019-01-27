#ifndef _GLT_SHADER_INCLUDED
#define _GLT_SHADER_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/ShaderType.hpp>
#include <GLT/Context.hpp>
#include <GLT/RefCount.hpp>


// Standard
#include <string>


namespace GLT {

  // Class encapsulates a shader
  class Shader {
  private:

    // OpenGL handle
    ShaderType type;
    GLuint glHandle;
    RefCount refCount;

    // Shader source
    std::string source;

  private:

    // Loads entire file into string and returns it
    void SetSource(std::string src);
    void LoadSource(std::string path);

  public:

    // Constructors
    Shader(ShaderType type, std::string path, Context* context);
    Shader(ShaderType type, std::string path);

    // Deconstruct
    ~Shader(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_INCLUDED
