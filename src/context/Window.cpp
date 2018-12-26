#include <GLT/Window.hpp>
using namespace GLT;


// Standard
#include <iostream>
using namespace std;


// Common initialisation
void Window::Init(void) {

  // Default name and resolution
  this->name = "GLT";
  this->size = glm::vec2(640, 480);

  // Default camera
  this->camera.SetViewRatio(this->size);
}


// Default constructor
Window::Window(void) {
  this->Init();
  this->Open(&GLT::glContext);
}


// Size & description constructor
Window::Window(const glm::vec2 size, const string name) {
  this->Init();
  this->name = name;
  this->size = size;
  this->Open(&GLT::glContext);
}


// Clean up on destruction
Window::~Window(void) {
  glfwDestroyWindow(this->glfwWindow);
}


// Make the context current if not already
void Window::MakeCurrent(void) {
  if(glfwGetCurrentContext() != this->glfwWindow) {
    glfwMakeContextCurrent(this->glfwWindow);
  }
}


// Open the window and inform the context
void Window::Open(Context* context) {

  // Store pointer to parent context
  this->context = context;

  // Create the window
  this->glfwWindow = glfwCreateWindow(
    this->size.x, this->size.y,
    this->name.c_str(), NULL, NULL);

  // Register window with context
  this->context->RegisterWindow(this);
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


// Set the camera to use
void Window::SetCamera(const Camera cam) {
  this->camera = cam;
  this->camera.SetViewRatio(this->size);
}
