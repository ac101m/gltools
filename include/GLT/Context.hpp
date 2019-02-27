#ifndef _GLT_CONTEXT_INCLUDED
#define _GLT_CONTEXT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/ShaderType.hpp>
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


  // Class encapsulates an opengl context
  class Context {
  private:

    // Keep track of whether GLFW is initialised or not.
    static int contextCount;
    static std::mutex contextCountMx;

    // Is glew initialised?
    bool glewInitialised;

    // Pointers to windows attached to this context
    GLFWwindow* prevGlfwWindow;

    // Texture cache
    ElementCache<std::string, Texture> textureCache;

//====[METHODS]==============================================================//

    // GLFW Error callback
    static void Error(int error, const char *description);

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
    GLuint NewShaderHandle(ShaderType type);
    GLuint NewShaderProgramHandle(void);
    GLuint NewVertexArrayHandle(void);
    GLuint NewBufferHandle(void);
    GLuint NewTextureHandle(void);

    // Texture caching routines
    bool TextureCached(const std::string& path);
    Texture GetTexture(const std::string& path);
    void AddTexture(const std::string& path, const Texture& texture);

    // Destructor manages termination of glfw
    ~Context(void);
  };

  // Global default context variable
  extern Context defaultContext;

} // namespace GLT


#endif // _GLT_CONTEXT_INCLUDED
