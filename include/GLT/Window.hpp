#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// This project
#include <GLT/Context.hpp>
#include <GLT/Camera.hpp>


// Standard
#include <string>


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // The context class will exist. Promise...
  class Context;

  // Class to wrap GLFW context and window
  class Window {
  private:

    // Is the window active?
    bool active;

    // GLFW window and context handles
    GLFWwindow* glfwWindow;

    // Camera
    Camera camera;

  private:

    // Get frame buffer size
    glm::vec2 GetFrameBufferSize(void);

  public:

    // Constructor/destructor
    Window(GLFWwindow* glfwWindow);

    // Window open & close methods
    void Close(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // General utility
    bool ShouldClose(void);
    void PollEvents(void);
    void SwapBuffers(void);

    // Camera set and get
    void SetCamera(const Camera cam);
    Camera GetCamera(void) {return this->camera;}

    // Destructor, clean things up
    ~Window(void);
  };

} // namespace GLT

#endif // _GLT_CONTEXT_INCLUDED
