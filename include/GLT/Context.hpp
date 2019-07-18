#ifndef _GLT_CONTEXT_INCLUDED
#define _GLT_CONTEXT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Texture.hpp>
#include <GLT/RenderBehaviour.hpp>
#include <GLT/ElementCache.hpp>


// Standard
#include <vector>
#include <mutex>
#include <map>
#include <list>


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // Forward declarations where neccessary
  class RenderBehaviour;


  // Class encapsulates an opengl context
  class Context {
  private:

    // Pointers to open GLFW windows
    std::list<GLFWwindow*> openWindows;

    // Current render behaviour
    RenderBehaviour* currentRenderBehaviour;

//====[METHODS]==============================================================//

    // GLFW Error callback
    static void GLFWError(int error, const char *description);

    // Common initialisation
    void InitGlfw(void);
    void InitGlew(void);
    void InitGL(void);

  public:

    // Constructor
    Context(void);

    // Make this context current
    void MakeCurrent(void);

    // Create things within this context
    GLFWwindow* NewGlfwWindow(
      glm::vec2 const size,
      std::string const name,
      GLFWmonitor* const mon = NULL);

    // Close a glfw window and remove it from the window list
    void CloseGlfwWindow(GLFWwindow* const window);

    // Sets and gets for render behaviour
    RenderBehaviour& GetCurrentRenderBehaviour(void);
    void SetCurrentRenderBehaviour(const RenderBehaviour& rb);

    // Destructor manages termination of glfw
    ~Context(void);
  };

  // Global default context variable
  extern Context defaultContext;

} // namespace GLT


#endif // _GLT_CONTEXT_INCLUDED
