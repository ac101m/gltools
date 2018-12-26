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
  this->active = false;
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
  this->active = false;
}


// Add a window
void Context::RegisterWindow(Window* window) {

  // Add the window to the
  window->MakeCurrent();
  this->windows.push_back(window);

  // Initialise GLEW if neccessary
  if(!this->active) {
    if(glewInit() != GLEW_OK) {
      std::cerr << "CONTEXT: Failed to initialise GLEW\n";
      exit(1);
    } else {
      std::cout << "CONTEXT: Initialised GLEW\n";
      this->active = true;
    }
  }
}
