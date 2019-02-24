#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Context.hpp>
#include <GLT/Camera.hpp>
#include <GLT/Drawable.hpp>


// Standard
#include <string>


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // The context class will exist. Promise...
  class Context;


  // Struct to contain
  typedef struct  {
    Drawable& object;
    ShaderProgram shader;
  } drawQueue_t;


  // Class to wrap GLFW context and window
  class Window {
  private:

    // Is the window active?
    bool active;

    // Some general window info
    std::string name;
    glm::vec2 size;

    // GLFW window and context handles
    GLFWwindow* glfwWindow;

    // Cursor stuff
    bool cursorCaptured;
    glm::vec2 cursorDelta;
    glm::vec2 cursorPrevPos;

    // Drawing stuff
    std::vector<drawQueue_t> drawQueue;

//====[METHODS]==============================================================//

    // Get frame buffer size
    glm::vec2 GetFrameBufferSize(void);
    glm::vec2 GetWindowSize(void);

    // Window and framebuffer resize callbacks
    static void WindowSizeCallback(GLFWwindow *window, int x, int y);
    static void FrameBufferSizeCallback(GLFWwindow *window, int x, int y);

    // Common initialisation
    void Init(glm::vec2 size, std::string name, Context& context);

    // General refresh routines
    void RefreshCursor(void);
    void RefreshSize(void);
    void RefreshDisplay(void);
    void PollEvents(void);

  public:

    // Camera
    Camera camera;

//====[METHODS]==============================================================//

    // Constructors
    Window(glm::vec2 size, std::string name, Context& context);
    Window(glm::vec2 size, std::string name);

    // Window open & close methods
    void Close(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // Get the GLFW window handle pointer
    GLFWwindow* GetGlfwHandle(void) {return this->glfwWindow;}

    // General utility
    bool ShouldClose(void);

    // Cursor
    glm::vec2 GetCursorPos(void);
    glm::vec2 GetCursorDelta(void);
    void SetCursorPos(glm::vec2 pos);
    void CenterCursor(void);
    void CaptureCursor(void);
    void FreeCursor(void);

    // Keypresses
    bool KeyPressed(int key);

    // Drawing routines
    void Draw(Drawable& object, ShaderProgram& shader);
    void Refresh(void);
    void Clear(void);

    // Destructor, clean things up
    ~Window(void);
  };

} // namespace GLT

#endif // _GLT_CONTEXT_INCLUDED
