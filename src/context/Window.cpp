#include <GLT/Window.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Variable to track initialisation state of glfw
bool Window::glfwInitialised = false;


// GLFW error callback
void Window::Error(int error, const char* description) {
  std::cerr << "GLFW: " << description << "\n";
}


//========[PRIVATE METHODS]===================================================//

// Common initialisation
void Window::Init(void) {
  if(!glfwInitialised) {
    if(!glfwInit()) {
      std::cerr << "Error, failed to initialise GLFW.\n";
      exit(1);
    } else {
      glfwInitialised = true;
    }
  }

  glfwSetErrorCallback(Window::Error);

  this->glfwWindow = glfwCreateWindow(
    this->size.x, this->size.y,
    name,
    NULL, NULL);

  this->MakeCurrent();
  if(glewInit() != GLEW_OK) {
    std::cerr << "Error, failed to initialise GLEW\n";
    exit(1);
  }

  glfwSwapInterval(1);

  this->name = "";
  this->size = glm::vec2(640, 480);
}


//========[PUBLIC METHODS]====================================================//

// Default constructor
Window::Window(void) {
  this->Init();
}


// Size & description constructor
Window::Window(const glm::vec2 size, const char* name) {
  this->Init();
  this->name = name;
  this->size = size;
}


// Clean up on destruction
Window::~Window(void) {
  glfwDestroyWindow(this->glfwWindow);
}


// Returns true if the window should close
bool Window::ShouldClose(void) {
  return glfwWindowShouldClose(this->glfwWindow);
}


// Poll events
void Window::PollEvents(void) {
  this->MakeCurrent();
  glfwPollEvents();
}


// Make the context current if not already
void Window::MakeCurrent(void) {
  if(glfwGetCurrentContext() != this->glfwWindow) {
    glfwMakeContextCurrent(this->glfwWindow);
  }
}


// Swap buffers
void Window::SwapBuffers(void) {
  this->MakeCurrent();
  glfwSwapBuffers(this->glfwWindow);
}
