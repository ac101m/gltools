#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// This library stuff
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Camera.hpp>


// Matrix math
#include <glm/glm.hpp>


// Begin GLT namespace
namespace GLT {

  // Class to wrap GLFW context and window
  class Window {
  private:

    // Static variable for tracking initialisation state of glfw
    static bool glfwInitialised;

    // Window data
    glm::vec2 size;
    const char* name;

    // GLFW window handle
    GLFWwindow* glfwWindow;

    // Camera
    GLT::Camera camera;

  private:

    // Common initialisation
    void Init(void);

    // GLFW Error callback
    static void Error(int error, const char* description);

  public:

    // Constructor/destructor
    Window(void);
    Window(const glm::vec2 size, const char* name);
    ~Window(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // General utility
    bool ShouldClose(void);
    void PollEvents(void);
    void SwapBuffers(void);

    // Camera set and get
    void SetCamera(const GLT::Camera cam);
    GLT::Camera GetCamera(void) {return this->camera;}
  };

} // GLT namespace

#endif // _GLT_CONTEXT_INCLUDED
