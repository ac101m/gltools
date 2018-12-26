#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>


int main(void) {

  // Instantiate a context
  GLT::Context cxt;

  // Create two windows in the current context
  GLT::Window* win1 = cxt.NewWindow(glm::vec2(640, 480), "Test window 1", NULL);

  // Window 2 loop
  while(!win1->ShouldClose()) {
    win1->PollEvents();
    win1->SwapBuffers();
  }

  // All done
  return 0;
}
