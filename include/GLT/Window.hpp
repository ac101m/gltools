#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// Include GLT master once (needed for glew/glfw)
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Standard
#include <string>
using namespace std;


// Matrix math
#include <glm/glm.hpp>


// Begin GLT namespace
namespace GLT {

  // Class to wrap GLFW context and window
  class Window {
  private:

    // metadata
    glm::vec2 size;
    const char* name;

    // GLFW window handle
    GLFWwindow* glfwWindow;

  private:

    // Makes sure that the context is current
    void Init(void);
    void MakeCurrent(void);

  public:

    // Constructor/destructor
    Window(const glm::vec2 size, const char* name);
    ~Window(void);

    // GLFW Error callback
    static void Error(int error, const char* description);

    // General utility
    bool ShouldClose(void);
    void PollEvents(void);
    void SwapBuffers(void);
  };

} // GLT namespace

#endif // _GLT_CONTEXT_INCLUDED
