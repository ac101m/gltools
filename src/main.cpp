#include <iostream>

#include <GLT/Window.hpp>

int main(void) {

  // Create a window
  GLT::Window w(glm::vec2(640, 480), "Test window");

  // Main draw loop
  while(!w.ShouldClose()) {
    w.PollEvents();
    w.SwapBuffers();
  }

  // Close the window
  return 0;
}
