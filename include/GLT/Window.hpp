#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Camera.hpp>
#include <GLT/Drawable.hpp>
#include <GLT/RenderBehaviour.hpp>


// Standard
#include <string>


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // The context class will exist. Promise...
  class Context;


  // Struct to contain draw queue entry
  typedef struct  {
    Drawable& object;
    ShaderProgram& shader;
    glm::mat4& transform;
  } drawQueue_t;


  // Class to wrap GLFW context and window
  class Window {
  private:

    // Parent context
    Context* parentContext;

    // Is the window active?
    bool active;

    // Some general window info
    std::string title;
    glm::vec2 size;

    // GLFW window and context handles
    GLFWwindow* glfwWindow;

    // Cursor stuff
    bool cursorCaptured;
    glm::vec2 cursorDelta;
    glm::vec2 cursorPrevPos;

    // Time data
    double windowCreationTime;
    double prevRefreshTime;
    double timeDelta;

    // Drawing stuff
    std::vector<drawQueue_t> drawQueue;

    // FPS counter enabled?
    bool fpsCounterEnabled;

//====[METHODS]==============================================================//

    // Get frame buffer size
    glm::vec2 GetFrameBufferSize(void) const;
    glm::vec2 GetWindowSize(void) const;

    // General refresh routines
    void InitCursor(void);
    void RefreshCursor(void);

    // Time handling
    void InitTime(void);
    void RefreshTime(void);

    // General window handling
    void RefreshSize(void);
    void PollEvents(void);
    void EmptyDrawQueue(void);
    void RefreshDisplay(void);
    void RefreshFpsCounter(void);

  public:

    // Camera
    Camera camera;

    // Render behaviour
    RenderBehaviour renderBehaviour;

//====[METHODS]==============================================================//

    // Constructors
    Window(unsigned const x, unsigned const y, std::string const title);

    // Set the window title
    void SetTitle(const std::string title);
    std::string GetTitle(void) const {return this->title;}

    // Option routines
    void EnableFpsCounter(void);
    void DisableFpsCounter(void);

    // Select the context associated with this window
    void MakeCurrent(void);

    // Cursor routines
    glm::vec2 GetCursorPos(void) const;
    glm::vec2 GetCursorDelta(void) const;
    void SetCursorPos(glm::vec2 pos);
    void CenterCursor(void);
    void CaptureCursor(void);
    void FreeCursor(void);

    // Keypresses
    bool KeyPressed(int key);

    // Time routines
    double GetTime(void) const {return glfwGetTime() - this->windowCreationTime;}
    double GetTimeDelta(void) const {return this->timeDelta;}

    // Drawing routines
    void Draw(Drawable& object, ShaderProgram& shader, glm::mat4& transform);
    void Refresh(void);

    // Window closing
    bool ShouldClose(void) const;
    void Close(void);

    // Destructor, clean things up
    ~Window(void);
  };

} // namespace GLT

#endif // _GLT_CONTEXT_INCLUDED
