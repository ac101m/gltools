#ifndef _GLT_CONTEXT_INCLUDED
#define _GLT_CONTEXT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Window.hpp>
#include <GLT/Shader.hpp>
#include <GLT/ShaderProgram.hpp>


// Standard
#include <vector>
#include <mutex>


// Matrix math
#include <glm/glm.hpp>


namespace GLT {

  // Window class will exist, Promise
  class Window;

  // Class encapsulates an opengl context
  class Context {
  private:

    // Keep track of whether GLFW is initialised or not.
    static int contextCount;
    static std::mutex contextCountMx;

    // Is glew initialised?
    bool glewInitialised;

    // Pointers to windows attached to this context
    std::vector<Window*> windows;
    std::vector<Shader*> shaders;
    GLFWwindow* prevGlfwHandle;

  private:

    // Common initialisation
    void Init(void);
    void InitGlew(GLFWwindow* window);

    // GLFW Error callback
    static void Error(int error, const char* description);

  public:

    // Constructor/destructor
    Context(void);

    // Make this context current
    void MakeCurrent(void);

    // Create things within this context
    Window* NewWindow(glm::vec2 size, std::string name, GLFWmonitor* mon);
    Shader* NewShader(std::string path, ShaderType type);
    ShaderProgram* NewShaderProgram(std::string vertexPath, std::string fragmentPath);

    // Destructor manages termination of glfw
    ~Context(void);
  };

} // namespace GLT


#endif // _GLT_CONTEXT_INCLUDED
