#ifndef GLT_TEXTURE_INCLUDED
#define GLT_TEXTURE_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/RefCount.hpp"
#include "GLT/Util/ElementCache.hpp"
#include "GLT/Util/ElementStack.hpp"


// Standard
#include <string>
#include <vector>


namespace GLT {

  // Base class for textures
  template<class T>
  class TextureBase : public RefCount {
  protected:

    // Opengl name
    GLuint glName;

    // Binding stack
    static ElementStack<TextureBase> bindStack;

    // Bind to specific target
    void Bind(GLenum const bindTarget);
    void Unbind(GLenum const bindTarget);

  public:

    static void Init();

    // Basic constructors
    TextureBase() {glGenTextures(1, &this->glName);}
    TextureBase(GLuint const glName) : glName(glName) {}

    // Get the GL name
    GLuint GetGlName() {return this->glName;}

    // Bind and unbind control
    virtual void Bind();
    virtual void Unbind();

    // Reference counted destructor
    ~TextureBase();
  };


  // Class represents a two-dimensional texture
  class Texture : public RefCount {
  private:

    // Opengl name
    GLuint glName;

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
    GLuint GetGlName() const {return this->glName;}

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
