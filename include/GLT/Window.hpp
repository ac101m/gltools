#ifndef _GLT_WINDOW_INCLUDED
#define _GLT_WINDOW_INCLUDED


// Include GLT master once (needed for glew/glfw)
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Matrix math
#include <glm/glm.hpp>


// Begin GLT namespace
namespace GLT {

  // Class
  class Window {
  private:

  public:
    // Initialisation
    void Init(void);
    Window(glm::vec2 size);
  };

} // GLT namespace

#endif // _GLT_CONTEXT_INCLUDED
