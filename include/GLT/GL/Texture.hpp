#ifndef GLT_TEXTURE_INCLUDED
#define GLT_TEXTURE_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/GlObject.hpp"
#include "GLT/Util/ElementStack.hpp"


// Standard
#include <string>
#include <vector>
#include <iostream>


namespace GLT {

  // Base class for textures
  class Texture : public GlObject {
  protected:

    // Bind to specific target and bind stack
    void BindAny(
      GLenum const bindTarget,
      ElementStack<Texture>& bindStack) const;
    void UnbindAny(
      GLenum const bindTarget,
      ElementStack<Texture>& bindStack) const;

  public:

    // Basic constructors
    Texture() {glGenTextures(1, &this->glName);}
    Texture(GLuint const glName) : GlObject(glName) {}

    // Set texture parameters
    virtual void Parameteri(GLenum const pname, GLint const param) {}

    // Virtual bind methods
    virtual void Bind() const {
      std::cout << "ERROR: Pure virtual Texture bind\n";
      exit(1);
    }
    virtual void Unbind() const {
      std::cout << "ERROR: Pure virtual GlObject unbind\n";
      exit(1);
    }

    // Reference counted destructor
    ~Texture();
  };

} // namespace GLT

#endif // GLT_TEXTURE_INCLUDED
