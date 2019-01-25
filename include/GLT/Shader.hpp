#ifndef _GLT_SHADER_INCLUDED
#define _GLT_SHADER_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Standard
#include <string>


namespace GLT {

  // Shader type ENUM
  typedef enum {
    GLT_SHADER_VERTEX = GL_VERTEX_SHADER,
    GLT_SHADER_FRAGMENT = GL_FRAGMENT_SHADER
  } ShaderType;


  // Class encapsulates a shader
  class Shader {
  private:

    // OpenGL handle
    GLuint handle;
    ShaderType type;

    // Shader source
    std::string source;

  private:

    // Loads entire file into string and returns it
    void SetSource(const std::string src);
    void LoadSource(const std::string path);

  public:

    // Constructors/destructor
    Shader(const std::string path, const ShaderType type);

    // Deconstruct
    ~Shader(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_INCLUDED
