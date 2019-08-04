#ifndef GLT_GLOBJECT_INCLUDED
#define GLT_GLOBJECT_INCLUDED


// Internal
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/RefCount.hpp"


// Standard
#include <iostream>


namespace GLT {

  // Base object for opengl
  class GlObject : public RefCount {
  protected:

    // Opengl name
    GLuint glName;

  public:

    GlObject() {this->glName = 0;}
    GlObject(GLuint const glName) : glName(glName) {}

    // Get the opengl name
    GLuint GetGlName() {return this->glName;}

    // Bind and unbind the object
    virtual void Bind() const {
      std::cout << "ERROR: Pure virtual GlObject bind\n";
      exit(1);
    }
    virtual void Unbind() const {
      std::cout << "ERROR: Pure virtual GlObject unbind\n";
      exit(1);
    }

    // Reference counted destructor
    virtual ~GlObject() {}
  };

} // namespace GLT

#endif // GLT_GLOBJECT_INCLUDED
