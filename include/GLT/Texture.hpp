#ifndef _GLT_TEXTURE_INCLUDED
#define _GLT_TEXTURE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/ElementCache.hpp>
#include <GLT/ElementStack.hpp>


// Standard
#include <string>
#include <vector>


namespace GLT {

  // Class represents a texture handle
  class Texture : public RefCount {
  private:

    // Texture path, used as name
    GLuint glHandle;

    // Cache for textures loaded from file
    static ElementCache<std::string, Texture> fileCache;

    // Texture binding stack, keeps track of the GL_TEXTURE_2D bind target
    static ElementStack<Texture> bindStack;

  public:

    // Initialise static members (cache and bind stack)
    static void Init();

    // Constructor, from file
    Texture(
      std::string const path,
      unsigned const mipMapLevel = 0);

    // Constructor, from data
    Texture(
      int const width,
      int const height,
      std::vector<unsigned char> const data);

    // Constructor, from initialised handle
    Texture(
      GLuint const textureHandle);

    // Constructor, full initialisation
    Texture(
      GLint const mipMapLevel,
      GLint const internalFormat,
      GLsizei const width,
      GLsizei const height,
      GLenum const format,
      GLenum const type,
      GLvoid const * data);

    // Set texture data
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

    // Set texture integer parameter
    void Parameteri(GLenum const pname, GLint const param);

    // Bind and unbind the texture
    void Bind() const;
    void Unbind() const;

    // Get the opengl handle
    GLuint GetGlHandle() const {return this->glHandle;}

    // Destructor, uses reference count
    ~Texture();
  };

} // namespace GLT


#endif // _GLT_TEXTURE_INCLUDED
