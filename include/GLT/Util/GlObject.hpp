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
    GLuint GetGlName() const {return this->glName;}
  };

} // namespace GLT

#endif // GLT_GLOBJECT_INCLUDED
