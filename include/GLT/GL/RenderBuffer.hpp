#ifndef GLT_RENDERBUFFER_INCLUDED
#define GLT_RENDERBUFFER_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/GlObject.hpp"
#include "GLT/Util/ElementStack.hpp"


namespace GLT {

  class RenderBuffer : public GlObject {
  private:

    // Stack for renderbuffer bind target
    static ElementStack<RenderBuffer> bindStack;

  public:

    // Initialise bind stack
    static void Init();

    // Void constructor, generate name but nothing else
    RenderBuffer() {glGenRenderbuffers(1, &this->glName);}

    // Construct directly from name
    RenderBuffer(GLuint const glName) : GlObject(glName) {}

    // Construct from parameters
    RenderBuffer(
      GLenum const format,
      unsigned const width,
      unsigned const height);

    // Assign storage for render buffer
    void Storage(
      GLenum const format,
      unsigned const width,
      unsigned const height);

    // Bind and unbind
    void Bind() const;
    void Unbind() const;

    // Reference counted destructor
    ~RenderBuffer();
  };

} // namespace GLT


#endif // GLT_RENDERBUFFER_INCLUDED
