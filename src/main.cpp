#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>


int main(void) {

  // Create a camera
  GLT::Camera cam;
  cam.SetPos(0, 0, 2);

  // Set up a window and add our camera to it
  GLT::Window win(glm::vec2(640, 480), "Test window 1");
  win.SetCamera(cam);

  // Main draw loop
  while(!win.ShouldClose()) {
    win.PollEvents();
    win.SwapBuffers();
  }

  // All done
  return 0;
}
