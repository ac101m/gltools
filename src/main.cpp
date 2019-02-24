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
  GLT::MeshInstance meshInstance(testMesh);
  glm::mat4 m = glm::mat4(1.0);


//====[TEMPORARY]============================================================//
  // Input sensitifity stuff
  float rotateSpeed = 1.0f;
	float moveSpeed = 1.0f;
	float mouseSensitivity = 0.003f;

  // Time stuff
  float dt, dr = 0.0f;                    // pitch roll and yaw
  float dFwd, dRight, dUp = 0.0f;     // camera movement
//====[TEMPORARY]============================================================//


  // Window 2 loop
  while(!window.ShouldClose()) {


//====[TEMPORARY]============================================================//
    // get current time
    dt = window.GetTimeDelta();

    // reset input control deltas
    dr = dFwd = dRight = dUp = 0.0f;

    // get mouse position delta
    glm::vec2 cursorDelta = window.GetCursorDelta() * mouseSensitivity;

    // Cursor captured?
    if(window.KeyPressed(GLFW_KEY_ESCAPE)) window.FreeCursor();
    if(window.KeyPressed(GLFW_KEY_M)) window.CaptureCursor();

    // do input handling
    if(window.KeyPressed(GLFW_KEY_W)) dFwd += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_S)) dFwd -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_A)) dRight += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_D)) dRight -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_SPACE)) dUp += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_C)) dUp -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_E)) dr += (dt * rotateSpeed);
    if(window.KeyPressed(GLFW_KEY_Q)) dr -= (dt * rotateSpeed);

    // update camera orientation
    window.camera.Move(dRight, dUp, dFwd);
    window.camera.MoveLook(-cursorDelta.x, cursorDelta.y, dr);
//====[TEMPORARY]============================================================//


    // Draw the test mesh
    meshInstance.Rotate(dt, glm::vec3(0, 1, 0));
    window.Draw(meshInstance, shader);

    // Display output
    window.Refresh();
  }

  // All done
  return 0;
}
