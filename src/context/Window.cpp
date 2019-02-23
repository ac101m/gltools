#include <GLT/Window.hpp>
using namespace GLT;


// Standard
#include <iostream>
using namespace std;


// Window resize callback
void Window::WindowSizeCallback(GLFWwindow *window, int x, int y) {

}


// Frame buffer resize callback
void Window::FrameBufferSizeCallback(GLFWwindow *window, int x, int y) {

}


// Common initialisation
void Window::Init(glm::vec2 size, string name, Context& context) {
  this->glfwWindow = context.NewGlfwWindow(size, name, NULL);
  this->active = true;
  this->camera.SetViewRatio(this->GetFrameBufferSize());

  // Set window and frame buffer resize callbacks
  glfwSetWindowSizeCallback(this->glfwWindow, this->WindowSizeCallback);
  glfwSetFramebufferSizeCallback(this->glfwWindow, this->FrameBufferSizeCallback);
}


// Constructor, with specified context
Window::Window(glm::vec2 size, string name, Context& context) {
  this->Init(size, name, context);
}


// Constructor, with default context
Window::Window(glm::vec2 size, string name) {
  this->Init(size, name, defaultContext);
}


// Get frame buffer size
glm::vec2 Window::GetFrameBufferSize(void) {
  int x, y;
  glfwGetFramebufferSize(this->glfwWindow, &x, &y);
  return glm::vec2(x, y);
}


// Make the context current if not already
void Window::MakeCurrent(void) {
  if(this->active) {
    if(glfwGetCurrentContext() != this->glfwWindow) {
      glfwMakeContextCurrent(this->glfwWindow);
    }
  } else {
    std::cerr << "Cannot make window current, window not active\n";
    exit(1);
  }
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

  // Handle frame buffer size changes
  glm::vec2 fbSize = this->GetFrameBufferSize();
  if(fbSize != this->size) {
    glViewport(0, 0, fbSize.x, fbSize.y);
    this->camera.SetViewRatio(fbSize);
    this->size = fbSize;
  }
}


// Clear the window
void Window::Clear(void) {
  this->MakeCurrent();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Clean up on destruction
Window::~Window(void) {
  this->Close();
  std::cout << "Window cleaned up\n";
}
