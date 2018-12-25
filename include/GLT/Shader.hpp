#ifndef _GLT_SHADER_INCLUDED
#define _GLT_SHADER_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Standard
#include <string>
using namespace std;


namespace GLT {

  // Class encapsulates a shader
  class Shader {
  private:

    // Shader source
    string source;

    // OpenGL handle
    GLuint handle;
    GLenum type;

  private:

    // Loads entire file into string and returns it
    void SetSource(const string src);
    void LoadSource(const string path);

  public:

    // Constructors/destructor
    Shader(const string path, const GLenum type);

  };

} // namespace GLT


#endif // _GLT_SHADER_INCLUDED
