#include <GLT/Window.hpp>
using namespace GLT;


// Standard
#include <iostream>


//========[PRIVATE METHODS]===================================================//

// Common initialisation
void Window::Init(void) {
  if(!glfwInit()) {
    std::cerr << "Error, failed to initialise GLFW.\n";
    exit(1);
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
}


// Make the context current if not already
void Window::MakeCurrent(void) {
  if(glfwGetCurrentContext() != this->glfwWindow) {
    glfwMakeContextCurrent(this->glfwWindow);
  }
}


//========[PUBLIC METHODS]====================================================//

// Size constructor
Window::Window(const glm::vec2 size, const char* name) {
  this->name = name;
  this->size = size;
  this->Init();
  glfwSwapInterval(1);
}


// Clean up on destruction
Window::~Window(void) {
  glfwDestroyWindow(this->glfwWindow);
}


// GLFW error callback
void Window::Error(int error, const char* description) {
  std::cerr << "Error: " << description << "\n";
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


// Swap buffers
void Window::SwapBuffers(void) {
  this->MakeCurrent();
  glfwSwapBuffers(this->glfwWindow);
}
