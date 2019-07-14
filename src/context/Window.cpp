#include <GLT/Window.hpp>
using namespace GLT;


// Standard
#include <iostream>
#include <sstream>


// Constructor
Window::Window(unsigned const x, unsigned const y,
               std::string const title,
               GLFWmonitor* mon) :
               parentContext(&defaultContext) {

  this->size = glm::vec2(x, y);
  this->glfwWindow = this->parentContext->NewGlfwWindow(this->size, title, mon);
  this->active = true;
  this->title = title;
  this->camera.SetViewRatio(this->GetFrameBufferSize());

  // General run-to-run state data setup
  this->InitCursor();
  this->InitTime();

  // Fps counter is not enabled
  this->fpsCounterEnabled = false;
}


// Set the window title
void Window::SetTitle(const std::string title) {
  glfwSetWindowTitle(this->glfwWindow, title.c_str());
  this->title = title;
}


// Get frame buffer size
glm::vec2 Window::GetFrameBufferSize(void) const {
  int x, y;
  glfwGetFramebufferSize(this->glfwWindow, &x, &y);
  return glm::vec2(x, y);
}


// Get frame buffer size
glm::vec2 Window::GetWindowSize(void) const {
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
    this->renderBehaviour.Apply();
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
bool Window::ShouldClose(void) const {
  return glfwWindowShouldClose(this->glfwWindow);
}


// Poll events
void Window::PollEvents(void) {
  this->MakeCurrent();
  glfwPollEvents();
}


//====[CURSOR ROUTINES]======================================================//

// Initialisation routine for cursor data
void Window::InitCursor(void) {
  this->cursorCaptured = false;
  this->cursorDelta = glm::vec2(0, 0);
  this->cursorPrevPos = this->GetCursorPos();
}


// Refresh cursor position
void Window::RefreshCursor(void) {
  if(this->cursorCaptured) {
    this->cursorDelta = this->GetCursorPos() - this->cursorPrevPos;
    this->CenterCursor();
  } else {
    this->cursorDelta = glm::vec2(0, 0);
  }
  this->cursorPrevPos = this->GetCursorPos();
}


// Capture the Cursor
void Window::CaptureCursor(void) {
  this->CenterCursor();
  glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  this->cursorPrevPos = this->GetCursorPos();
  this->cursorDelta = glm::vec2(0, 0);
  this->cursorCaptured = true;
}


// Free the cursor
void Window::FreeCursor(void) {
  glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  this->cursorCaptured = false;
}


// Get position of the cursor
glm::vec2 Window::GetCursorPos(void) const {
  double x, y;
  glfwGetCursorPos(this->glfwWindow, &x, &y);
  return glm::vec2(x, y);
}


// Set the position of the cursor
void Window::SetCursorPos(glm::vec2 pos) {
  glfwSetCursorPos(this->glfwWindow, pos.x, pos.y);
}


// Place cursor at the middle of the screen
void Window::CenterCursor(void) {
  this->SetCursorPos(this->GetWindowSize() / 2.0f);
}


// How much has the cursor moved?
glm::vec2 Window::GetCursorDelta(void) const {
  return this->cursorDelta;
}


//====[TIME HANDLING ROUTINES]===============================================//

// Initialise time state data
void Window::InitTime(void) {
  this->prevRefreshTime = this->windowCreationTime = glfwGetTime();
  this->timeDelta = 0;
}


// Refresh time data
void Window::RefreshTime(void) {
  double currentTime = this->GetTime();
  this->timeDelta = currentTime - this->prevRefreshTime;
  this->prevRefreshTime = currentTime;
}


//====[WINDOW AND FRAME BUFFER ROUTINES]=====================================//

// Refresh window size
void Window::RefreshSize(void) {
  glm::vec2 currentSize = this->GetWindowSize();
  if(this->size != currentSize) {
    glViewport(0, 0, currentSize.x, currentSize.y);
    this->camera.SetViewRatio(this->GetFrameBufferSize());
    this->size = this->GetWindowSize();
  }
}


// Empty the draw queue
void Window::EmptyDrawQueue(void) {
  for(unsigned i = 0; i < this->drawQueue.size(); i++) {
    this->drawQueue[i].object.Draw(
      this->camera,
      this->drawQueue[i].shader,
      this->drawQueue[i].transform);
  }
  this->drawQueue.clear();
}


// Draw a drawable object (well, add it to the draw queue)
void Window::Draw(Drawable& object, ShaderProgram& shader, glm::mat4& transform) {
  this->drawQueue.push_back({object, shader, transform});
}


// Refresh the display
void Window::RefreshDisplay(void) {
  glfwSwapBuffers(this->glfwWindow);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


//====[FPS COUNTER ROUTINES]=================================================//

// Enable FPS counter
void Window::EnableFpsCounter(void) {
  this->fpsCounterEnabled = true;
}


// Disable FPS counter
void Window::DisableFpsCounter(void) {
  this->fpsCounterEnabled = false;
  this->SetTitle(this->title);
}


// Refresh the FPS counter at the top of the window (if enabled)
void Window::RefreshFpsCounter(void) {
  if(this->fpsCounterEnabled) {
    std::stringstream ss;
    ss << this->title << " (" << unsigned(1 / this->GetTimeDelta()) << " FPS)";
    glfwSetWindowTitle(this->glfwWindow, ss.str().c_str());
  }
}


//====[MISC]=================================================================//

// Key pressed?
bool Window::KeyPressed(int key) {
  return glfwGetKey(this->glfwWindow, key) == GLFW_PRESS;
}


// Perform window refresh cycle
void Window::Refresh(void) {
  this->MakeCurrent();

  // Majority of refresh cycle should be here
  this->EmptyDrawQueue();
  this->PollEvents();

  // Refresh beginning-of-loop things
  this->RefreshDisplay();
  this->RefreshSize();
  this->RefreshCursor();
  this->RefreshTime();
  this->RefreshFpsCounter();
}


// Clean up on destruction
Window::~Window(void) {
  this->Close();
  std::cout << "Window cleaned up\n";
}
