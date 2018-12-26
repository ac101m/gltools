#include <GLT/Context.hpp>
using namespace GLT;


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Standard
#include <iostream>


// Track the number of GLFW contexts
int Context::contextCount = 0;
std::mutex Context::contextCountMx;


// GLFW error callback
void Context::Error(int error, const char* description) {
  std::cerr << "GLFW: " << description << "\n";
}


// Common initialisation
void Context::Init(void) {

  // Lock the context count static variable
  contextCountMx.lock();

  // If we are the first context, do GLFW setup
  if(contextCount == 0) {

    // Initialise GLFW
    if(!glfwInit()) {
      std::cerr << "CONTEXT: Failed to initialise GLFW.\n";
      exit(1);
    } else {
      std::cout << "CONTEXT: Initialised GLFW\n";
    }

    // Add glfw error callback
    glfwSetErrorCallback(Context::Error);
  }

  // Increment the context count
  contextCount++;
  contextCountMx.unlock();

  // Last window handle, NULL means glfwCreateWindow will
  // kick off a new opengl context.
  this->prevGlfwHandle = NULL;

  // Glew hasn't been intialised yet (we can't until we have a context)
  this->glewInitialised = false;
  this->windows.clear();
}


// Initialise GLEW
void Context::InitGlew(GLFWwindow* window) {
  if(!this->glewInitialised) {

    // Make one of the windows from this context active
    glfwMakeContextCurrent(window);

    // Do the initialisation
    if(glewInit() != GLEW_OK) {
      std::cerr << "CONTEXT: Failed to initialise GLEW\n";
      exit(1);
    } else {
      std::cout << "CONTEXT: GLEW Initialised\n";
      this->glewInitialised = true;
    }
  }
}


// Initialise the context
Context::Context(void) {
  this->Init();
}


// Add a window
Window* Context::NewWindow(glm::vec2 size, std::string name, GLFWmonitor* mon) {

  // Create a GLFW window
  GLFWwindow* glfwHandle = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, this->prevGlfwHandle);

  // Initialise GLEW
  if(this->prevGlfwHandle == NULL) {
    this->InitGlew(glfwHandle);
  }

  // The next window will share this ones context
  this->prevGlfwHandle = glfwHandle;

  // Create the new window
  this->windows.push_back(new Window(glfwHandle));

  // Return a pointer to the newly created window
  return this->windows[this->windows.size() - 1];
}


// Context going out of scope, close all windows
Context::~Context(void) {

  // Clean up windows
  for(unsigned i = 0; i < this->windows.size(); i++) {
    delete windows[i];
  }

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

  // Cleaned up context
  std::cout << "CONTEXT: Context cleaned up\n";
}
