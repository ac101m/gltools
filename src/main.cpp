#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/RefCount.hpp>
#include <GLT/Mesh.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// Generates a single triangle test mesh
GLT::Mesh GenTestMesh(void) {
  std::vector<unsigned> indices = {0, 1, 2};
  std::vector<GLT::vertex_t> vertices = {
    {glm::vec3(-0.5, -0.5, 0), glm::vec3(1, 0, 0), glm::vec2()},
    {glm::vec3(0.5, -0.5, 0), glm::vec3(0, 1, 0), glm::vec2()},
    {glm::vec3(0, 0.5, 0), glm::vec3(0, 0, 1), glm::vec2()}
  };

  // All done
  return GLT::Mesh(vertices, indices);
}


int main(void) {

  // Create window
  GLT::Window window(glm::vec2(800, 600), "GLT Test");

  // Build a shader program
  GLT::Shader vertexShader(GLT_SHADER_VERTEX, "shaders/generic-vert.glsl");
  GLT::Shader fragmentShader(GLT_SHADER_FRAGMENT, "shaders/generic-frag.glsl");
  GLT::ShaderProgram shader({vertexShader, fragmentShader});

  // Mesh and model matrix
  GLT::Mesh testMesh = GenTestMesh();
  glm::mat4 mmx = glm::mat4(1.0);

  // Window 2 loop
  while(!window.ShouldClose()) {

    // Clear the screen and draw
    window.Clear();
    testMesh.Draw(window, shader, mmx);

    // Rotate the triangle
    mmx = glm::rotate(mmx, 0.1f, glm::vec3(0, 1, 0));

    // Display output
    window.PollEvents();
    window.SwapBuffers();
  }

  // All done
  return 0;
}
