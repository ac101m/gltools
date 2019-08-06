#ifndef GLT_BUFFER_INCLUDED
#define GLT_BUFFER_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/GlObject.hpp"
#include "GLT/Util/ElementStack.hpp"


// Standard
#include <vector>


namespace GLT {

  // Class wraps opengl buffer construct
  class Buffer : public GlObject {
  private:

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

    // Constructor, void
    Buffer() {glGenBuffers(1, &this->glName);}

    // Constructor, direct from GLuint
    Buffer(GLuint const glName) : GlObject(glName) {}

    // Loads data into the GL buffer
    template <class T>
    void SetData(
      std::vector<T> const data,
      GLenum const bindTarget,
      GLenum const usageHint = defaultUsageHint) {

      // Load data into buffer
      this->Bind(bindTarget);
      glBufferData(
        bindTarget,
        data.size() * sizeof(T),
        data.data(),
        usageHint);
      this->Unbind(bindTarget);
    }

    // Constructor, loads data
    template <class T>
    Buffer(
      std::vector<T> const data,
      GLenum const bindTarget,
      GLenum const usageHint = defaultUsageHint) {

      glGenBuffers(1, &this->glName);
      this->SetData<T>(data, bindTarget, usageHint);
    }

    // Binding routines, selectable target (many different ways to use buffers)
    void Bind(GLenum const bindTarget);
    void Unbind(GLenum const bindTarget);

    // Reference counted destructor
    ~Buffer();
  };

} // namespace GLT

#endif // GLT_BUFFER_INCLUDED
