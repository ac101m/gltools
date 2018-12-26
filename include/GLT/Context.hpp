#ifndef _GLT_CONTEXT_INCLUDED
#define _GLT_CONTEXT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Window.hpp>


// Standard
#include <vector>
#include <mutex>


namespace GLT {


  // Window class will exist, Promise
  class Window;

  // Class encapsulates an opengl context
  class Context {
  private:

    // Keep track of whether GLFW is initialised or not.
    static int contextCount;
    static std::mutex contextCountMx;

    // Is the context initialized?
    bool active;

    // Pointers to windows attached to this context
    std::vector<Window*> windows;

  private:

    // Common initialisation
    void Init(void);

    // GLFW Error callback
    static void Error(int error, const char* description);

  public:

    // Constructor/destructor
    Context(void);
    ~Context(void);

    // Register things with the context
    void RegisterWindow(Window* window);
  };

  // Context for GLT, used by all GLT objects
  extern Context glContext;
}


#endif // _GLT_CONTEXT_INCLUDED
