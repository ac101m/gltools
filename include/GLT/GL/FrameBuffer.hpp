#ifndef GLT_FRAMEBUFFER_INCLUDED
#define GLT_FRAMEBUFFER_INCLUDED


// Internal headers
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/RefCount.hpp"
#include "GLT/GL/Texture.hpp"


// Standard
#include <vector>
#include <memory>


namespace GLT {

  class FrameBuffer : public RefCount {
  private:

    // Opengl name
    GLuint glName;

    // Colour buffers
    std::shared_ptr<std::vector<Texture>> colorBuffers;

    // Bind stacks
    static ElementStack<FrameBuffer> bindStack_GL_DRAW_FRAMEBUFFER;
    static ElementStack<FrameBuffer> bindStack_GL_READ_FRAMEBUFFER;

//====[METHODS]==============================================================//

    // Return a reference to the selected bind target stack
    static ElementStack<FrameBuffer>& GetTargetStack(GLenum const bindTarget);

    // Check for completeness, error if not
    void VerifyCompleteness();

  public:

    // Initialise bind stacks
    static void Init();

    // Constructor, direct from name
    FrameBuffer(GLuint const glName = 0);

    // Constructor, full
    FrameBuffer(
      unsigned const width,
      unsigned const height,
      std::vector<Texture> const colorBuffers);

    // Return gl name
    GLuint GetGlName() {return this->glName;}

    // Bind and unbind
    void Bind(GLenum const bindTarget);
    void Unbind(GLenum const bindTarget);

    // Reference counted destructor
    ~FrameBuffer();
  };

} // namespace GLT

#endif // GLT_FRAMEBUFFER_INCLUDED
