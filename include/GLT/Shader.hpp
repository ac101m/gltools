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
  class Shader : public RefCount {
  private:

    // OpenGL handle
    ShaderType type;
    GLuint glHandle;

    // Shader source
    std::string source;

//====[METHODS]==============================================================//

    // Common initialisation
    void Init(ShaderType type, std::string path, Context& context);

    // Generates debug prints
    void Compile(void);

    // Loads entire file into string and returns it
    void SetSource(std::string src);
    void LoadSource(std::string path);

  public:

    // Constructors
    Shader(ShaderType type, std::string path, Context& context);
    Shader(ShaderType type, std::string path);

    // Get GL handle
    GLuint GetGlHandle(void) {return this->glHandle;}

    // Deconstruct
    ~Shader(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_INCLUDED
