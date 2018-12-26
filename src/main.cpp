#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>


int main(void) {

  // Create two windows
  GLT::Window win1(glm::vec2(640, 480), "Test window 1");
  GLT::Window win2(glm::vec2(640, 480), "Test window 2");

  // Window 2 loop
  win1.Open();
  while(!win1.ShouldClose()) {
    win1.PollEvents();
    win1.SwapBuffers();
  }
  win1.Close();

  // Window 2 loop
  win2.Open();
  while(!win2.ShouldClose()) {
    win2.PollEvents();
    win2.SwapBuffers();
  }
  win2.Close();

  // All done
  return 0;
}
