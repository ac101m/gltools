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


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // Forward declarations where neccessary
  class Texture;
  class RenderBehaviour;


  // Class encapsulates an opengl context
  class Context {
  private:

    // Keep track of whether GLFW is initialised or not.
    static int contextCount;
    static std::mutex contextCountMx;

    // Is glew initialised?
    bool glewInitialised;

    // Pointers to most recent GLFW window
    GLFWwindow* prevGlfwWindow;

    // Texture cache
    ElementCache<std::string, Texture> textureCache;

    // Current render behaviour
    RenderBehaviour* currentRenderBehaviour;

    // Currently active shader program
    GLuint activeShaderProgram;

//====[METHODS]==============================================================//

    // GLFW Error callback
    static void GLFWError(int error, const char *description);

    // Common initialisation
    void InitGlew(GLFWwindow *window);

    // Initialise opengl
    void InitGL(void);

  public:

    // Constructor/destructor
    Context(void);

    // Make this context current
    void MakeCurrent(void);

    // Create things within this context
    GLFWwindow* NewGlfwWindow(glm::vec2 size, std::string name, GLFWmonitor *mon);
    GLuint NewVertexArrayHandle(void);
    GLuint NewBufferHandle(void);
    GLuint NewTextureHandle(void);

    // Texture caching routines
    bool TextureCached(const std::string& path);
    Texture GetTexture(const std::string& path);
    void AddTexture(const std::string& path, const Texture& texture);

    // Sets and gets for render behaviour
    RenderBehaviour& GetCurrentRenderBehaviour(void);
    void SetCurrentRenderBehaviour(const RenderBehaviour& rb);

    GLuint GetCurrentShaderProgram(void);
    void SetCurrentShaderProgram(GLuint const sp);

    // Destructor manages termination of glfw
    ~Context(void);
  };

  // Global default context variable
  extern Context defaultContext;

} // namespace GLT


#endif // _GLT_CONTEXT_INCLUDED
