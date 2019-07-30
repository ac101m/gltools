#ifndef GLT_SHADER_INCLUDED
#define GLT_SHADER_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/RefCount.hpp"


// Standard
#include <string>
#include <vector>


// External
#include <glm/glm.hpp>


namespace GLT {

  // Class encapsulates a shader
  class Shader : public RefCount {
  private:

    // OpenGL handle
    GLuint glName;

    // Shader source
    std::string source;

//====[METHODS]==============================================================//

    // Generates debug prints
    void Compile(void);

    // Loads entire file into string and returns it
    void SetSource(const std::string& src);
    void LoadSource(const std::string& path);

  public:

    // Constructor, no path
    Shader(GLenum const type) {this->glName = glCreateShader(type);}

    // Constructor, from path
    Shader(GLenum const type, std::string const path);

    GLuint GetGlName(void) const {return this->glName;}

    // Reference counted destructor
    ~Shader(void);
  };

} // namespace GLT


#endif // GLT_SHADER_INCLUDED
