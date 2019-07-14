#ifndef _GLT_TEXTURE_INCLUDED
#define _GLT_TEXTURE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/Context.hpp>


// Standard
#include <string>
#include <vector>


namespace GLT {

  // Context will exist, promise
  class Context;


  // Class represents a texture handle
  class Texture : public RefCount {
  private:

    // Pointer to local context
    Context* parentContext;

    // Texture path, used as name
    GLuint glHandle;

  public:

    // Constructor, from file
    Texture(std::string const path);

    // Constructor, from data
    Texture(
      int const width, int const height,
      std::vector<unsigned char> const data);

    // Constructor, from initialised handle
    Texture(GLuint const textureHandle);

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
      int const width, int const height,
      std::vector<unsigned char> const data);
    void SetData(
      int const width, int const height,
      unsigned char const * const data);

    // Texture properties
    void Parameteri(GLenum const pname, GLint const param);

    // Bind and unbind the texture
    void Bind(void) const {glBindTexture(GL_TEXTURE_2D, this->glHandle);}
    void Unbind(void) const {glBindTexture(GL_TEXTURE_2D, 0);}

    // Get the opengl handle
    GLuint GetGlHandle(void) const {return this->glHandle;}

    // Destructor, uses reference count
    ~Texture(void);
  };

} // namespace GLT


#endif // _GLT_TEXTURE_INCLUDED
