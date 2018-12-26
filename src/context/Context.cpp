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


// Global context, used by all GLT objects
Context GLT::glContext;


// GLFW error callback
void Context::Error(int error, const char* description) {
  std::cerr << "GLFW: " << description << "\n";
}


// Common initialisation
void Context::Init(void) {

  // Lock the context count static variable
  contextCountMx.lock();

  // Initialise GLFW if not already done
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

  // Context isn't actrive until there are attached windows
  this->glewInitialised = false;
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


// Context going out of scope, close all windows
Context::~Context(void) {

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
}


// Add a window
GLFWwindow* Context::MakeGlfwWindow(Window* window) {
  GLFWwindow* glfwWindow;

  // Make first window
  if(this->windows.size() == 0) {
    glfwWindow = glfwCreateWindow(
      window->GetSize().x, window->GetSize().y,
      window->GetName().c_str(),
      NULL, NULL);

  // Otherwise, make new window a child of the existing ones
  } else {
    glfwWindow = glfwCreateWindow(
      window->GetSize().x, window->GetSize().y,
      window->GetName().c_str(),
      NULL, this->windows[0]->GetWindowHandle());
  }

  // Add window pointer & initialise GLEW
  this->windows.push_back(window);
  this->InitGlew(glfwWindow);
  return glfwWindow;
}
