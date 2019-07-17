#include <GLT/Context.hpp>
using namespace GLT;


// Standard
#include <iostream>
#include <string>


// Track the number of GLFW contexts
int Context::contextCount = 0;
std::mutex Context::contextCountMx;


// Default global context
Context GLT::defaultContext;


// GLFW error callback
void Context::GLFWError(int error, const char* description) {
  std::cerr << "GLFW ERROR: " << description << "\n";
}


// Initialise GLEW
void Context::InitGlew(GLFWwindow* window) {
  if(!this->glewInitialised) {

    // Make one of the windows from this context active
    glfwMakeContextCurrent(window);

    // Do the initialisation
    if(glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialise GLEW\n";
      exit(1);
    } else {
      std::cout << "Initialised GLEW\n";
      this->glewInitialised = true;
    }
  }
}


// Initialise opengl behaviour
void Context::InitGL(void) {
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
  this->currentRenderBehaviour = new RenderBehaviour();
  this->currentRenderBehaviour->ApplyAll();
}


// Common initialisation
Context::Context(void) {

  // Begin context lock
  contextCountMx.lock();

  // If we are the first context, do GLFW setup
  if(contextCount == 0) {

    // Initialise GLFW
    if(!glfwInit()) {
      std::cerr << "Failed to initialise GLFW\n";
      exit(1);
    } else {
      std::cout << "Initialised GLFW\n";
    }

    // Add glfw error callback
    glfwSetErrorCallback(Context::GLFWError);
  }

  // End context lock
  contextCount++;
  contextCountMx.unlock();

  // Last window handle, NULL means glfwCreateWindow will
  // kick off a new opengl context when called
  this->prevGlfwWindow = NULL;

  // Glew hasn't been intialised yet (we can't until we have a context)
  this->glewInitialised = false;

  // 0 indicates no bound shader
  this->activeShaderProgram = 0;
}


// Make this context current
void Context::MakeCurrent(void) {
  if(this->prevGlfwWindow != NULL) {
    glfwMakeContextCurrent(this->prevGlfwWindow);
  }
}


// Create a window that is attached to this context
GLFWwindow* Context::NewGlfwWindow(glm::vec2 size, std::string name, GLFWmonitor* mon) {

  // Create a GLFW window
  GLFWwindow* glfwWindow = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, this->prevGlfwWindow);

  // Initialise GLEW
  if(this->prevGlfwWindow == NULL) {
    this->InitGlew(glfwWindow);
  }

  // The next window will share this ones context
  this->prevGlfwWindow = glfwWindow;
  this->MakeCurrent();

  // Initialise opengl
  this->InitGL();

  // Return the window handle
  return glfwWindow;
}


// Make a new vertex buffer object within the current context
GLuint Context::NewVertexArrayHandle(void) {
  this->MakeCurrent();
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return vao;
}


// Make a new vertex buffer object within the current context
GLuint Context::NewBufferHandle(void) {
  this->MakeCurrent();
  GLuint buf;
  glGenBuffers(1, &buf);
  return buf;
}


// Make a new vertex buffer object within the current context
GLuint Context::NewTextureHandle(void) {
  this->MakeCurrent();
  GLuint id;
  glGenTextures(1, &id);
  return id;
}


// Check if a texture has been previously loaded
bool Context::TextureCached(const std::string& path) {
  return this->textureCache.Contains(path);
}


// Get a loaded texture, segfaults if it doesn't exist
Texture Context::GetTexture(const std::string& path) {
  return this->textureCache.Get(path);
}


// Add a loaded texture to the
void Context::AddTexture(std::string const& path, Texture const& texture) {
  return this->textureCache.Add(path, texture);
}


// Get current render behaviour
RenderBehaviour& Context::GetCurrentRenderBehaviour(void) {
  return *(this->currentRenderBehaviour);
}


// Set current render behaviour
void Context::SetCurrentRenderBehaviour(RenderBehaviour const& rb) {
  *(this->currentRenderBehaviour) = rb;
}


// Get current shader program
GLuint Context::GetCurrentShaderProgram(void) {
  return this->activeShaderProgram;
}


// Set current shader program
void Context::SetCurrentShaderProgram(GLuint const sp) {
  this->activeShaderProgram = sp;
}


// Context going out of scope
Context::~Context(void) {

  // Clean up any allocated items
  delete this->currentRenderBehaviour;

  // Decrement reference count
  contextCountMx.lock();
  contextCount--;

  // Last one out, turn out the lights
  if(contextCount == 0) {
    glfwTerminate();
  }

  // Unlock mutex
  contextCountMx.unlock();

  // Context has no attached windows at the moment
  this->glewInitialised = false;

  // Print cleanup messages
  std::cout << "Context cleaned up\n";
  if(!contextCount) {
    std::cout << "All contexts destroyed, GLFW terminated\n";
  }
}
