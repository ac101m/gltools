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

    // Window data
    glm::vec2 size;
    std::string name;

    // GLFW window and context handles
    GLFWwindow* glfwWindow;
    Context* context;

    // Camera
    Camera camera;

  private:

    // Common initialisation
    void Init(void);

    // Open in specific context
    void Open(Context* context);

  public:

    // Constructor/destructor
    Window(void);
    Window(const glm::vec2 size, const std::string name);
    ~Window(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // General utility
    bool ShouldClose(void);
    void PollEvents(void);
    void SwapBuffers(void);

    // Camera set and get
    void SetCamera(const Camera cam);
    Camera GetCamera(void) {return this->camera;}
  };

} // namespace GLT

#endif // _GLT_CONTEXT_INCLUDED
