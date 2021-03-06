#ifndef GLT_CONTEXT_INCLUDED
#define GLT_CONTEXT_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif


// Standard
#include <vector>
#include <mutex>
#include <map>
#include <list>


// Matrix math
#include "glm/glm.hpp"


namespace GLT {

  // Class encapsulates an opengl context
  class Context {
  private:

    // Pointers to open GLFW windows
    static std::list<GLFWwindow*> openWindows;

//====[METHODS]==============================================================//

    // GLFW Error callback
    static void GLFWError(int error, const char *description);

    // Common initialisation
    static void InitGlfw(void);
    static void InitGlew(void);

    // Initialise GLT
    static void InitGLT(void);

  public:

    // Constructor, doesn't do much to be honest
    Context(void);

    // Make GLT context current
    static void MakeCurrent(void);

    // Create things within this context
    static GLFWwindow* NewGlfwWindow(
      glm::vec2 const size,
      std::string const name,
      GLFWmonitor* const mon = NULL);

    // Close a glfw window and remove it from the window list
    static void CloseGlfwWindow(GLFWwindow* const window);

    // Destructor closes active windows and manages final glfw termination
    ~Context(void);
  };

} // namespace GLT


#endif // GLT_CONTEXT_INCLUDED
