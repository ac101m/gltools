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

    // OpenGL name
    GLuint glName;

  public:

    // Constructor, blank
    Shader(GLenum const type) {this->glName = glCreateShader(type);}

    // Constructor, from path
    Shader(GLenum const type, std::string const path);

    // Shader source compilation
    void FromSource(std::string const source);
    void FromFile(std::string const path);

    // Get opengl name
    GLuint GetGlName(void) const {return this->glName;}

    // Reference counted destructor
    ~Shader(void);
  };

} // namespace GLT


#endif // GLT_SHADER_INCLUDED
