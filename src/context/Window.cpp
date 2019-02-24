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
  this->size = this->GetWindowSize();
  this->camera.SetViewRatio(this->GetFrameBufferSize());

  // Set window and frame buffer resize callbacks
  glfwSetWindowSizeCallback(this->glfwWindow, this->WindowSizeCallback);
  glfwSetFramebufferSizeCallback(this->glfwWindow, this->FrameBufferSizeCallback);

  // Cursor setup
  this->cursorCaptured = false;
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


// Get frame buffer size
glm::vec2 Window::GetWindowSize(void) {
  int x, y;
  glfwGetWindowSize(this->glfwWindow, &x, &y);
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


// Poll events
void Window::WaitEvents(void) {
  this->MakeCurrent();
  glfwWaitEvents();
}


// Get position of the cursor
glm::vec2 Window::GetCursorPos(void) {
  double x, y;
  glfwGetCursorPos(this->glfwWindow, &x, &y);
  return glm::vec2(x, y);
}


//
glm::vec2 Window::GetCursorDelta(void) {
  return this->cursorDelta;
}


// Set cursor position
void Window::SetCursorPos(glm::vec2 pos) {
  glfwSetCursorPos(this->glfwWindow, pos.x, pos.y);
}


// Place cursor at the middle of the screen
void Window::CenterCursor(void) {
  this->SetCursorPos(this->GetWindowSize() / 2.0f);
}


// Capture the Cursor
void Window::CaptureCursor(void) {
  this->CenterCursor();
  this->cursorPrevPos = this->GetCursorPos();
  this->cursorDelta = glm::vec2(0, 0);
  glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  this->cursorCaptured = true;
}


// Free the cursor
void Window::FreeCursor(void) {
  this->cursorCaptured = false;
  glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


// Refresh cursor position
void Window::RefreshCursor(void) {
  if(this->cursorCaptured) {
    this->cursorDelta = this->GetCursorPos() - this->cursorPrevPos;
    this->CenterCursor();
    this->cursorPrevPos = this->GetCursorPos();
  } else {
    this->cursorDelta = glm::vec2(0, 0);
  }
}


// Refresh window size
void Window::RefreshSize(void) {
  glm::vec2 currentSize = this->GetWindowSize();
  if(this->size != currentSize) {
    glViewport(0, 0, currentSize.x, currentSize.y);
    this->camera.SetViewRatio(this->GetFrameBufferSize());
    this->size = this->GetWindowSize();
  }
}


// Swap buffers
void Window::Refresh(void) {
  this->MakeCurrent();
  glfwSwapBuffers(this->glfwWindow);

  // Refresh all the things
  this->RefreshSize();
  this->RefreshCursor();

  // Clear the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
