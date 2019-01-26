#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/RefCount.hpp>


int main(void) {

  // Create two windows in the current context
  GLT::Window win(glm::vec2(800, 600), "Test 1");

  // Window 2 loop
  while(!win.ShouldClose()) {
    win.PollEvents();
    win.SwapBuffers();
  }

  // All done
  return 0;
}
