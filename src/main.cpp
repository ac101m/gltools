// This project source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/Mesh.hpp>
#include <GLT/Texture.hpp>


// Generates a single triangle test mesh
GLT::Mesh GenTestTriangle(void) {

  // Vertices
  std::vector<GLT::vertex_t> vertices = {
    {glm::vec3(-0.5, -0.5, 0),  glm::vec3(1, 0, 0),   glm::vec2(0, 0)},
    {glm::vec3(0.5, -0.5, 0),   glm::vec3(0, 1, 0),   glm::vec2(1, 0)},
    {glm::vec3(0, 0.5, 0),      glm::vec3(0, 0, 1),   glm::vec2(0.5, 1)}};

  // Indices
  std::vector<unsigned> indices = {0, 1, 2};

  // Textures
  std::vector<GLT::Texture> textures = {
    GLT::Texture("textures/brownrock/colour.png")};

  // Package up into mesh
  return GLT::Mesh(vertices, indices, textures);
}


// Generates a cube test mesh with proper indices
GLT::Mesh GenTestCubeIndexed(void) {
  std::vector<float> vertexData = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f};

  // Vertex list
  std::vector<GLT::vertex_t> vertices;
  for(unsigned i = 0; i < vertexData.size(); i += 5) {
    GLT::vertex_t v;
    v.position = glm::vec3(vertexData[i], vertexData[i + 1], vertexData[i + 2]);
    v.uv = glm::vec2(vertexData[i + 3], vertexData[i + 4]);
    vertices.push_back(v);
  }

  // Compute all indices
  std::vector<unsigned> indices;
  for(unsigned i = 0; i < vertices.size(); i += 4) {
    indices.push_back(i);
    indices.push_back(i + 1);
    indices.push_back(i + 2);
    indices.push_back(i + 2);
    indices.push_back(i + 3);
    indices.push_back(i);
  }

  // Load the side texture
  std::vector<GLT::Texture> textures = {
    GLT::Texture("textures/brownrock/colour.png")};

  // Package up into mesh and return
  return GLT::Mesh(vertices, indices, textures);
}


int main(void) {

  // Create window
  GLT::Window window(glm::vec2(800, 600), "GLT Test");
  window.camera.SetPos(0, 0, -2);
  window.EnableFpsCounter();

  // Build a shader program
  GLT::Shader vertexShader(GLT_SHADER_VERTEX, "shaders/generic-vert.glsl");
  GLT::Shader fragmentShader(GLT_SHADER_FRAGMENT, "shaders/generic-frag.glsl");
  GLT::ShaderProgram shader({vertexShader, fragmentShader});

  // Mesh and model matrix
  GLT::Mesh testMesh = GenTestCubeIndexed();


//====[TEMPORARY]============================================================//
  // Input sensitifity stuff
  float rotateSpeed = 1.0f;
	float moveSpeed = 1.0f;
	float mouseSensitivity = 0.003f;
  float dFwd, dRight, dUp, dr = 0.0f;     // camera movement
//====[TEMPORARY]============================================================//


  // Window 2 loop
  while(!window.ShouldClose()) {


//====[TEMPORARY]============================================================//
    // get current time and print out fps
    float dt = window.GetTimeDelta();

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


    // Generate transform matrix
    glm::mat4 transform1 = glm::rotate(
      glm::mat4(1.0f),
      (float)window.GetTime() / 2,
      glm::vec3(0, 1, 0));

    // Draw the test mesh
    window.Draw(testMesh, shader, transform1);

    // Display output
    window.Refresh();
  }

  // All done
  return 0;
}
