#include <iostream>


// This library source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/RefCount.hpp>
#include <GLT/Mesh.hpp>


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


// Generates a single triangle test mesh
GLT::VertexBuffer GenTestVB(void) {
  std::vector<unsigned> indices = {0, 1, 2};
  std::vector<GLT::vertex_t> vertices = {
    {glm::vec3(-0.5, -0.5, 0), glm::vec3(1, 0, 0), glm::vec2()},
    {glm::vec3(0.5, -0.5, 0), glm::vec3(0, 1, 0), glm::vec2()},
    {glm::vec3(0, 0.5, 0), glm::vec3(0, 0, 1), glm::vec2()}
  };

  // All done
  return GLT::VertexBuffer(vertices, indices);
}


int main(void) {

  // Create window
  GLT::Window win(glm::vec2(800, 600), "GLT Test");
  win.MakeCurrent();

  // Build a shader program
  GLT::Shader vertexShader(GLT_SHADER_VERTEX, "shaders/generic-vert.glsl");
  GLT::Shader fragmentShader(GLT_SHADER_FRAGMENT, "shaders/generic-frag.glsl");
  GLT::ShaderProgram shader({vertexShader, fragmentShader});

  // Build a simple mesh
  auto test = GenTestMesh();

  // Window 2 loop
  while(!win.ShouldClose()) {
    test.Draw(shader);
    win.PollEvents();
    win.SwapBuffers();
  }

  // All done
  return 0;
}
