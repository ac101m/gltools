#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>


int main(void) {

  // Instantiate a context
  GLT::Context cxt;

  // Create two windows in the current context
  GLT::Window* win = cxt.NewWindow(glm::vec2(640, 480), "Test 1", NULL);

  // Window 2 loop
  while(!win->ShouldClose()) {
    win->PollEvents();
    win->SwapBuffers();
  }

  // All done
  return 0;
}
