#ifndef GLT_TEXTURE_INCLUDED
#define GLT_TEXTURE_INCLUDED


// This project
#ifndef GLT_MASTER_INCLUDED
#include "GLT/Master.hpp"
#endif
#include "GLT/RefCount.hpp"
#include "GLT/ElementCache.hpp"
#include "GLT/ElementStack.hpp"


// Standard
#include <string>
#include <vector>


namespace GLT {

  // Class represents a two-dimensional texture
  class Texture : public RefCount {
  private:

    // Opengl handle
    GLuint glHandle;

    // Cache for textures loaded from file
    static ElementCache<std::string, Texture> fileCache;

    // Texture binding stack, keeps track of the GL_TEXTURE_2D bind target
    static ElementStack<Texture> bindStack;

  public:

    // Initialise static members (cache and bind stack)
    static void Init();

    // Constructor, from arbitrary handle
    Texture(
      GLuint const textureHandle);

    // Constructor, complete initialisation
    Texture(
      GLint const mipMapLevel,
      GLint const internalFormat,
      GLsizei const width,
      GLsizei const height,
      GLenum const format,
      GLenum const type,
      GLvoid const * data);

    // Constructor, from file
    Texture(
      std::string const path,
      unsigned const mipMapLevel = 0);

    // Constructor, from data
    Texture(
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

    // Return the opengl handle
    GLuint GetGlHandle() const {return this->glHandle;}

    // Binding control
    void Bind() const;    // Bind this texture
    void Unbind() const;  // Unbind this texture and restore previous binding

    // Set texture parameters
    void Parameteri(GLenum const pname, GLint const param);

    // Reference counted destructor
    ~Texture();
  };

} // namespace GLT


#endif // GLT_TEXTURE_INCLUDED
