#ifndef GLT_TEXTURE2D_INCLUDED
#define GLT_TEXTURE2D_INCLUDED


// Internal
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/GL/Texture.hpp"
#include "GLT/Util/ElementCache.hpp"


// Standard
#include <string>
#include <vector>


namespace GLT {

  // Class represents a two-dimensional texture
  class Texture2D : public Texture {
  private:

    // Cache for textures loaded from file
    static ElementCache<std::string, Texture2D> fileCache;

    // Bind stack
    static ElementStack<Texture> bindStack;

  public:

    // Initialise static members (cache and bind stack)
    static void Init();

    // Constructor, complete initialisation
    Texture2D(
      GLint const mipMapLevel,
      GLint const internalFormat,
      GLsizei const width,
      GLsizei const height,
      GLenum const format,
      GLenum const type,
      GLvoid const * data);

    // Constructor, from file
    Texture2D(
      std::string const path,
      unsigned const mipMapLevel = 0);

    // Constructor, from data
    Texture2D(
      int const width,
      int const height,
      std::vector<unsigned char> const data);

    // Set texture data, std::vector and raw pointer
    void SetData(
      int const width,
      int const height,
      std::vector<unsigned char> const data,
      unsigned const mipMapLevel = 0);
    void SetData(
      int const width,
      int const height,
      unsigned char const * const data,
      unsigned const mipMapLevel = 0);

    // Set texture parameter
    void Parameteri(GLenum const pname, GLint const param);

    // Binding control
    void Bind() const {this->BindAny(GL_TEXTURE_2D, bindStack);}
    void Unbind() const {this->UnbindAny(GL_TEXTURE_2D, bindStack);}
  };

} // namespace GLT

#endif // GLT_TEXTURE2D_INCLUDED
