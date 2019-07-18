#include <GLT/Context.hpp>
using namespace GLT;


// Standard
#include <iostream>
#include <string>


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

  // Initialise GLFW
  if(!glfwInit()) {
    std::cerr << "Failed to initialise GLFW, nothing to be done\n";
    exit(1);
  }

  // Add glfw error callback
  glfwSetErrorCallback(Context::GLFWError);

  // Glew hasn't been intialised yet (we can't until we have a context)
  this->glewInitialised = false;
}


// Make the shared context current
void Context::MakeCurrent(void) {
  if(this->openWindows.empty()) {
    std::cout << "ERROR: Cannot make context current, no active context\n";
    exit(1);
  } else {
    glfwMakeContextCurrent(this->openWindows.front());
  }
}


// Create a window attached to this context
GLFWwindow* Context::NewGlfwWindow(
  glm::vec2 const size,
  std::string const name,
  GLFWmonitor* const mon) {

  // Window to share context with
  GLFWwindow* parentWindow = NULL;
  if(!this->openWindows.empty()) {
    parentWindow = this->openWindows.front();
  }

  // Create a new GLFW window handle
  GLFWwindow* glfwWindow = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, parentWindow);

  // If this is our first window, initialise glew
  if(this->openWindows.empty()) {
    this->InitGlew(glfwWindow);
  }

  // Add the newly created window to the window list
  this->openWindows.push_back(glfwWindow);

  // Initialise some opengl stuff, needs a rework [TODO]
  this->InitGL();

  // Return the window handle
  return glfwWindow;
}


// Close a glfw window and remove it from the window list
void Context::CloseGlfwWindow(GLFWwindow* const window) {
  glfwDestroyWindow(window);
  this->openWindows.remove(window);
}


// Get current render behaviour
RenderBehaviour& Context::GetCurrentRenderBehaviour(void) {
  return *(this->currentRenderBehaviour);
}


// Set current render behaviour
void Context::SetCurrentRenderBehaviour(RenderBehaviour const& rb) {
  *(this->currentRenderBehaviour) = rb;
}


// Context is (conceptually) static and global, [TODO]
// this only runs when the program exits. Context really needs a rework...
Context::~Context(void) {
  delete this->currentRenderBehaviour;
  glfwTerminate();
}
