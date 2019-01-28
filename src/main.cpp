#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/RefCount.hpp>


int main(void) {

  // Create window
  GLT::Window win(glm::vec2(800, 600), "Test 1");

  // Build a shader program
  GLT::Shader vertShader(GLT_SHADER_VERTEX, "shaders/generic-vert.glsl");
  GLT::Shader fragShader(GLT_SHADER_FRAGMENT, "shaders/generic-frag.glsl");
  GLT::ShaderProgram shader({vertShader, fragShader});

  // Window 2 loop
  while(!win.ShouldClose()) {
    win.PollEvents();
    win.SwapBuffers();
  }

  // All done
  return 0;
}
