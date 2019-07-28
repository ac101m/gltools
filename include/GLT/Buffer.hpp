#ifndef GLT_BUFFER_INCLUDED
#define GLT_BUFFER_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/GL.hpp"
#endif
#include "GLT/RefCount.hpp"
#include "GLT/ElementStack.hpp"


// Standard
#include <vector>


namespace GLT {

  // Class wraps opengl buffer construct
  class Buffer : public RefCount {
  private:

    // Underlying opengl handle
    GLuint glHandle;

    // Default buffer usage hint
    static GLenum defaultUsageHint;

    // Buffer bind target stacks
    static ElementStack<Buffer> bindStack_GL_ARRAY_BUFFER;
    static ElementStack<Buffer> bindStack_GL_ELEMENT_ARRAY_BUFFER;

//====[METHODS]==============================================================//

    // Return a reference to the selected bind target stack
    static ElementStack<Buffer>& GetTargetStack(GLenum const bindTarget);

  public:

    // Initialise bind stacks
    static void Init();

    // Constructor, direct from GLuint
    Buffer(GLuint const glHandle = 0) : glHandle(glHandle) {}

    // Loads data into the GL buffer
    template <class T>
    void SetData(
      std::vector<T> const data,
      GLenum const usageHint = defaultUsageHint) {

      // Load data into buffer
      glNamedBufferData(
        this->glHandle,
        data.size() * sizeof(T),
        data.data(),
        usageHint);
    }

    // Constructor, loads data
    template <class T>
    Buffer(
      std::vector<T> const data,
      GLenum const usageHint = defaultUsageHint) {

      glCreateBuffers(1, &this->glHandle);
      this->SetData<T>(data, usageHint);
    }

    // Get the underlying opengl handle
    GLuint GetGlHandle() {return this->glHandle;}

    // Binding routines, selectable target (many different ways to use buffers)
    void Bind(GLenum const bindTarget);
    void Unbind(GLenum const bindTarget);

    // Reference counted destructor
    ~Buffer();
  };

} // namespace GLT

#endif // GLT_BUFFER_INCLUDED
