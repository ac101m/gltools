#ifndef GLT_FRAMEBUFFER_INCLUDED
#define GLT_FRAMEBUFFER_INCLUDED


// Internal headers
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/GlObject.hpp"
#include "GLT/GL/Texture2D.hpp"
#include "GLT/GL/RenderBuffer.hpp"


// Standard
#include <vector>
#include <memory>


namespace GLT {

  class FrameBuffer : public GlObject {
  private:

    // Colour buffers
    std::vector<Texture2D>* colorAttachments;

    // Bind stacks
    static ElementStack<FrameBuffer> bindStack_GL_DRAW_FRAMEBUFFER;
    static ElementStack<FrameBuffer> bindStack_GL_READ_FRAMEBUFFER;

//====[METHODS]==============================================================//

    // Return a reference to the selected bind target stack
    static ElementStack<FrameBuffer>& GetTargetStack(GLenum const bindTarget);

    // Check for completeness, error if not
    void VerifyCompleteness();

    // Indicates which draw buffers are attached
    void UpdateColorAttachments();

  public:

    // Initialise bind stacks
    static void Init();

    // Void constructor, generates new name
    FrameBuffer();

    // Constructor, direct from name
    FrameBuffer(GLuint const glName);

    // Constructor, full
    FrameBuffer(
      unsigned const width,
      unsigned const height,
      std::vector<Texture2D> const colorBuffers);

    // Attach a texture as a colour buffer
    void AttachTexture2D(Texture2D const texture);

    // Get color buffers
    std::vector<Texture2D> GetColorBuffers() {return *this->colorAttachments;}

    // Attach a renderbuffer
    void AttachRenderBuffer(
      RenderBuffer const renderBuffer,
      GLenum const attachment);

    // Clear method
    void Clear(GLbitfield const mask);

    // Bind and unbind
    void Bind(GLenum const bindTarget);
    void Unbind(GLenum const bindTarget);

    // Reference counted destructor
    ~FrameBuffer();
  };

} // namespace GLT

#endif // GLT_FRAMEBUFFER_INCLUDED
