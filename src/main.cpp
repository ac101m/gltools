// This project source
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
    {glm::vec3(0, 0.5, 0), glm::vec3(0, 0, 1), glm::vec2()}};
  return GLT::Mesh(vertices, indices);
}


int main(void) {

  // Create window
  GLT::Window window(glm::vec2(800, 600), "GLT Test");
  window.camera.SetPos(0, 0, -2);

  // Build a shader program
  GLT::Shader vertexShader(GLT_SHADER_VERTEX, "shaders/generic-vert.glsl");
  GLT::Shader fragmentShader(GLT_SHADER_FRAGMENT, "shaders/generic-frag.glsl");
  GLT::ShaderProgram shader({vertexShader, fragmentShader});

  // Mesh and model matrix
  GLT::Mesh testMesh = GenTestMesh();
  glm::mat4 m = glm::mat4(1.0);

/*
//====[TEMPORARY]============================================================//
  // Input sensitifity stuff
  float rotateSpeed = 1.0f;
	float moveSpeed = 1.0f;
	float mouseSensitivity = 0.003f;
  double mouseX, mouseY;

  // Time stuff
  double tLast = glfwGetTime();
  double tCurrent;
  float dt = 0.0f;
  float dx, dy, dr = 0.0f;            // pitch roll and yaw
  float dFwd, dRight, dUp = 0.0f;     // camera movement

  // Zero cursor pos to make things less jumpy
  glfwSetCursorPos(window.GetGlfwHandle(), 400, 300);
//====[TEMPORARY]============================================================//
*/

  // Window 2 loop
  while(!window.ShouldClose()) {

/*
//====[TEMPORARY]============================================================//
    // get current time
    tCurrent = glfwGetTime();
    dt = float(tCurrent - tLast);
    tLast = tCurrent;

    // reset input control deltas
    dr = dFwd = dRight = dUp = dx = dy = 0.0f;

    // get mouse position & use it to calculate camera angle
    glfwGetCursorPos(window.GetGlfwHandle(), &mouseX, &mouseY);
    glfwSetCursorPos(window.GetGlfwHandle(), 400, 300);
    float dx = mouseSensitivity * float(400 - mouseX);
    float dy = mouseSensitivity * - float(300 - mouseY);

    // do input handling
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_W) == GLFW_PRESS) dFwd += (dt * moveSpeed);      // forwards
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_S) == GLFW_PRESS) dFwd -= (dt * moveSpeed);      // backwards
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_A) == GLFW_PRESS) dRight += (dt * moveSpeed);    // right
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_D) == GLFW_PRESS) dRight -= (dt * moveSpeed);    // left
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_SPACE) == GLFW_PRESS) dUp += (dt * moveSpeed);   // up
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_C) == GLFW_PRESS) dUp -= (dt * moveSpeed);       // down
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_E) == GLFW_PRESS) dr += (dt * rotateSpeed);      // clockwise
    if(glfwGetKey(window.GetGlfwHandle(), GLFW_KEY_Q) == GLFW_PRESS) dr -= (dt * rotateSpeed);

    // update camera orientation
    window.GetCamera().Move(dRight, dUp, dFwd);
    window.GetCamera().MoveLook(dx, dy, dr);
//====[TEMPORARY]============================================================//
*/

    // Rotate the "mesh"
    glm::mat4 m = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0, 1, 0));

    // Clear the screen and draw
    window.Clear();
    testMesh.Draw(window, shader, m);

    // Display output
    window.SwapBuffers();
    window.PollEvents();
  }

  // All done
  return 0;
}
