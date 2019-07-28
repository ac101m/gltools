#include "GLT/Context.hpp"
using namespace GLT;


// Standard
#include <iostream>
#include <string>


// This project headers
#include "GLT/Texture.hpp"
#include "GLT/Buffer.hpp"
#include "GLT/Mesh.hpp"


// Context object, manages termination of glfw at program exit
Context cxt;


// List of open windows
std::list<GLFWwindow*> Context::openWindows;


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
  if(Context::openWindows.empty()) {
    std::cerr << "GLEW initialisation failed, no active context\n";
    exit(1);
  }

  // Do the initialisation
  Context::MakeCurrent();
  if(glewInit() != GLEW_OK) {
    std::cerr << "GLEW initialisation failed, nothing to be done\n";
    exit(1);
  } else {
    std::cout << "Initialised GLEW\n";
  }
}


// Initialise opengl behaviour
void Context::InitGLT(void) {

  // Temporary [TODO]
  glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

  // Initialise GLT stuff
  Texture::Init();
  Buffer::Init();
  VertexArray::Init();
}


// Constructor, just notifies
Context::Context(void) {
  std::cout << "GLT context handler initialised\n";
}


// Make the shared context current
void Context::MakeCurrent(void) {
  if(Context::openWindows.empty()) {
    std::cerr << "ERROR: Cannot make context current, no active context\n";
    exit(1);
  } else {
    glfwMakeContextCurrent(Context::openWindows.front());
  }
}


// Create a window attached to this context
GLFWwindow* Context::NewGlfwWindow(
  glm::vec2 const size,
  std::string const name,
  GLFWmonitor* const mon) {

  // Initialise GLFW if it isn't already initialised
  GLFWwindow* parentWindow = NULL;
  if(Context::openWindows.empty()) {
    Context::InitGlfw();
  } else {
    parentWindow = Context::openWindows.front();
  }

  // Create a new GLFW window handle
  GLFWwindow* window = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, parentWindow);

  // Add window to window list
  Context::openWindows.push_back(window);

  // If this is our first window, that means this is a new context
  // New context means there is some initialisation to do
  if(Context::openWindows.size() == 1) {
    Context::InitGlew();
    Context::InitGLT();
  }

  // Return the window handle
  return window;
}


// Close a glfw window and remove it from the window list
void Context::CloseGlfwWindow(GLFWwindow* const window) {
  glfwDestroyWindow(window);
  Context::openWindows.remove(window);

  // Terminate glfw if that was our last window
  if(Context::openWindows.empty()) {
    glfwTerminate();
  }
}


// Context is (conceptually) static and global, [TODO]
// this only runs when the program exits. Context really needs a rework...
Context::~Context(void) {
  if(!Context::openWindows.empty()) {
    std::cout << "GLT Terminated with " << Context::openWindows.size();
    std::cout << " remaining GLFW windows\n";
    std::cout << "Tsk tsk, you really ought to close those yourself\n";
    glfwTerminate();
  } else {
    std::cout << "GLT Terminated, bye!\n";
  }
}
