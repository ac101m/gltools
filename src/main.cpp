#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>


int main(void) {

  // Create two windows
  GLT::Window win1(glm::vec2(640, 480), "Test window 1");
  GLT::Window win2(glm::vec2(720, 540), "Test window 2");

  // Main draw loop
  while(!win1.ShouldClose() || !win2.ShouldClose()) {
    if(!win1.ShouldClose()) {
      win1.PollEvents();
      win1.SwapBuffers();
    }
    if(!win2.ShouldClose()) {
      win2.PollEvents();
      win2.SwapBuffers();
    }
  }

  // All done
  return 0;
}
