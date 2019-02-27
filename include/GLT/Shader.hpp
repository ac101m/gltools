#ifndef _GLT_SHADER_INCLUDED
#define _GLT_SHADER_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/Context.hpp>


// Standard
#include <string>


namespace GLT {

  // Forward declaration of context
  class Context;


  // Class encapsulates a shader
  class Shader : public RefCount {
  private:

    // Parent context pointer
    Context* parentContext;

    // OpenGL handle
    GLenum type;
    GLuint glHandle;

    // Shader source
    std::string source;

//====[METHODS]==============================================================//

    // Generates debug prints
    void Compile(void);

    // Loads entire file into string and returns it
    void SetSource(std::string src);
    void LoadSource(const std::string& path);

  public:

    // Constructors
    Shader(const GLenum type, const std::string path);

    // Get GL handle
    GLuint GetGlHandle(void) {return this->glHandle;}

    // Deconstruct
    ~Shader(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_INCLUDED
