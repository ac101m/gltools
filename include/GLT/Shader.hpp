#ifndef GLT_SHADER_INCLUDED
#define GLT_SHADER_INCLUDED


// This project
#ifndef GLT_MASTER_INCLUDED
#include "GLT/Master.hpp"
#endif
#include "GLT/RefCount.hpp"


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
    GLenum type;
    GLuint glHandle;

    // Shader source
    std::string source;

//====[METHODS]==============================================================//

    // Generates debug prints
    void Compile(void);

    // Loads entire file into string and returns it
    void SetSource(const std::string& src);
    void LoadSource(const std::string& path);

  public:

    // Constructors
    Shader(const GLenum type, const std::string path);

    // Get GL handle
    GLuint GetGlHandle(void) const {return this->glHandle;}

    // Deconstruct
    ~Shader(void);
  };

} // namespace GLT


#endif // GLT_SHADER_INCLUDED
