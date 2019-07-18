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


// Intialise GLFW
void Context::InitGlfw(void) {
  if(!glfwInit()) {
    std::cerr << "GLFW initialisation failed, nothing to be done\n";
    exit(1);
  } else {
    std::cout << "Initialised GLFW\n";
  }
}


// Initialise GLEW
void Context::InitGlew(void) {

  // Check that there is at least one active window
  if(this->openWindows.empty()) {
    std::cerr << "GLEW initialisation failed, no active context\n";
    exit(1);
  }

  // Do the initialisation
  this->MakeCurrent();
  if(glewInit() != GLEW_OK) {
    std::cerr << "GLEW initialisation failed, nothing to be done\n";
    exit(1);
  } else {
    std::cout << "Initialised GLEW\n";
  }
}


// Initialise opengl behaviour
void Context::InitGL(void) {
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
  this->currentRenderBehaviour = new RenderBehaviour();
  this->currentRenderBehaviour->ApplyAll();
}


// Constructor, just notifies
Context::Context(void) {
  std::cout << "GLT context handler initialised\n";
}


// Make the shared context current
void Context::MakeCurrent(void) {
  if(this->openWindows.empty()) {
    std::cerr << "ERROR: Cannot make context current, no active context\n";
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

  // Initialise GLFW if it isn't already initialised
  GLFWwindow* parentWindow = NULL;
  if(this->openWindows.empty()) {
    this->InitGlfw();
  } else {
    parentWindow = this->openWindows.front();
  }

  // Create a new GLFW window handle
  GLFWwindow* window = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, parentWindow);

  // Add window to window list
  this->openWindows.push_back(window);

  // If this is our first window, glew must be initialised
  if(this->openWindows.size() == 1) {
    this->InitGlew();
  }

  // Initialise some opengl stuff, needs a rework [TODO]
  this->InitGL();

  // Return the window handle
  return window;
}


// Close a glfw window and remove it from the window list
void Context::CloseGlfwWindow(GLFWwindow* const window) {
  glfwDestroyWindow(window);
  this->openWindows.remove(window);

  // Terminate glfw if that was our last window
  if(this->openWindows.empty()) {
    glfwTerminate();
  }
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
  if(!this->openWindows.empty()) {
    std::cout << "GLT Terminated with " << this->openWindows.size();
    std::cout << " remaining GLFW windows\n";
    std::cout << "Tsk tsk, you really ought to close those yourself\n";
    glfwTerminate();
  } else {
    std::cout << "GLT Terminated, bye!\n";
  }
}
