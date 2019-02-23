#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
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

    // Some general window info
    glm::vec2 size;
    std::string name;

    // GLFW window and context handles
    GLFWwindow* glfwWindow;

    // Camera
    Camera camera;

  private:

    // Get frame buffer size
    glm::vec2 GetFrameBufferSize(void);

    // Window and framebuffer resize callbacks
    static void WindowResizeCallback(GLFWwindow *window, int x, int y);
    static void FrameBufferResizeCallback(GLFWwindow *window, int x, int y);

    // Common initialisation
    void Init(glm::vec2 size, std::string name, Context *context);

  public:

    // Constructor
    Window(glm::vec2 size, std::string name, Context *context);
    Window(glm::vec2 size, std::string name);

    // Window open & close methods
    void Close(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // Get the GLFW window handle pointer
    GLFWwindow* GetGlfwHandle(void) {return this->glfwWindow;}

    // General utility
    bool ShouldClose(void);
    void PollEvents(void);
    void SwapBuffers(void);

    // Camera set and get
    void SetCamera(const Camera cam);
    Camera& GetCamera(void) {return this->camera;}

    // Drawing routines
    void Clear(void);

    // Destructor, clean things up
    ~Window(void);
  };

} // namespace GLT

#endif // _GLT_CONTEXT_INCLUDED
