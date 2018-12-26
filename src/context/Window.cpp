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

  // Window handle does not exist
  this->glfwWindow = NULL;
  this->active = false;
}


// Default constructor
Window::Window(void) {
  this->Init();
}


// Size & description constructor
Window::Window(const glm::vec2 size, const string name) {
  this->Init();
  this->name = name;
  this->size = size;
}


// Make the context current if not already
void Window::MakeCurrent(void) {
  if(this->active) {
    if(glfwGetCurrentContext() != this->glfwWindow) {
      glfwMakeContextCurrent(this->glfwWindow);
    }
  } else {
    std::cerr << "WINDOW: Cannot make current, window not active\n";
    exit(1);
  }
}


// Get the GLFW window handle
GLFWwindow* Window::GetWindowHandle(void) {
  if(this->glfwWindow != NULL) {
    return this->glfwWindow;
  } else {
    std::cerr << "WINDOW: Cannot fetch window handle, window not active\n";
    exit(1);
  }
}


// Open the window and inform the context
void Window::Open(Context* context) {
  this->context = context;
  this->glfwWindow = context->MakeGlfwWindow(this);
  this->active = true;
}


// Open with default context
void Window::Open(void) {
  this->Open(&GLT::glContext);
}


// Close the window
void Window::Close() {
  if(this->active) {
    glfwDestroyWindow(this->glfwWindow);
    this->active = false;
  }
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


// Clean up on destruction
Window::~Window(void) {
  this->Close();
}
