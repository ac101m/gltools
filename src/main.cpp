// This project source
#include <GLT/Window.hpp>
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/Mesh.hpp>
#include <GLT/Texture.hpp>
#include <GLT/CubeMap.hpp>


// Standard
#include <iostream>
#include <unistd.h>


// Generates a single triangle test mesh
GLT::Mesh GenTestTriangle(void) {

  // Vertices
  std::vector<GLT::vertex_t> vertices = {
    {glm::vec3(-0.5, 0, -0.5),  glm::vec2(0, 0),    glm::vec3(1, 0, 0)},
    {glm::vec3(0.5, 0, -0.5),   glm::vec2(1, 0),    glm::vec3(0, 1, 0)},
    {glm::vec3(0, 0, 0.5),      glm::vec2(0.5, 1),  glm::vec3(0, 0, 1)}};

  // Indices
  std::vector<unsigned> indices = {0, 2, 1};

  // Textures
  std::vector<GLT::Texture> textures = {
    GLT::Texture("textures/brownrock/colour.png"),
    GLT::Texture("textures/brownrock/normal.png")};

  // Package up into mesh
  return GLT::Mesh(vertices, indices, textures);
}


// Generates a cube test mesh with proper indices
GLT::Mesh GenTestCubeIndexed(void) {
  std::vector<float> vertexData = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  1.0f};

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
    GLT::Texture("textures/brownrock/colour.png"),
    GLT::Texture("textures/brownrock/normal.png"),
    GLT::Texture("textures/brownrock/depth.png"),
    GLT::Texture("textures/brownrock/ao.png")};

  // Package up into mesh and return
  return GLT::Mesh(vertices, indices, textures);
}


// Mesh draw override
void GLT::Mesh::Draw(
  GLT::Camera& camera,
  GLT::ShaderProgram& shader,
  glm::mat4& m) {

  // Multiply out the matrices IN THE RIGHT FUCKING ORDER THIS TIME
  // GOD DMAN NON-COMMUTATIVE BASTARDS FKN 4 HOURS RIGHT THERE
  glm::mat4 mvp = camera.GetProjMat() * camera.GetViewMat() * m;
  glm::mat3 mv3 = glm::mat3(camera.GetViewMat() * m);

  // Shader uniform setup
  shader.GetUniform("mMx").SetFMat4(m);
  shader.GetUniform("vMx").SetFMat4(camera.GetViewMat());
  shader.GetUniform("mv3Mx").SetFMat3(mv3);
  shader.GetUniform("mvpMx").SetFMat4(mvp);

  // Bind textures to texture units
  std::string name = "texture0";
  for(unsigned i = 0; i < this->textures.size(); i++) {
    name[7] = 48 + i;
    shader.SetTexture(i, name, this->textures[i]);
  }

  // Draw the things
  this->vertexBuffer.Bind();
  glDrawElements(
    GL_TRIANGLES,
    this->vertexBuffer.GetIndexBufferLength(),
    GL_UNSIGNED_INT, 0);
  this->vertexBuffer.Unbind();

  // Set texture back to texture 0
  glActiveTexture(GL_TEXTURE0);
}


// Cube map draw override
void GLT::CubeMap::Draw(
  GLT::Camera& camera,
  GLT::ShaderProgram& shader,
  glm::Mat4& m) {

  // Strip the translation component from the view matrix
  glm::mat4 vMx(glm::mat3(camera.GetViewMat()));
  shader.GetUniform("vMx").SetFMat4(vMx);
  shader.GetUniform("pMx").SetFMat4(camera.GetProjMat());

  // Bind cube map texture
  glBindTexture(GL_TEXTURE_CUBE_MAP, this->glHandle);

  // Execute the actual draw call
  this->vertexBuffer.Bind();
  glDrawElements(
    GL_TRIANGLES,
    this->vertexBuffer.GetIndexBufferLength(),
    GL_UNSIGNED_INT, 0);
  this->vertexBuffer.Unbind();
}


int main(void) {

  // Create window
  GLT::Window window(glm::vec2(1280, 720), "GLT Test");
  window.camera.SetPos(0, 0, -2);
  window.EnableFpsCounter();
  window.renderBehaviour.SetDepthTestFunction(GL_LEQUAL);
  glfwSwapInterval(0);

  // Build object shader program
  GLT::Shader vertexShader(GL_VERTEX_SHADER, "shaders/lighting-vert.glsl");
  GLT::Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/lighting-frag.glsl");
  GLT::ShaderProgram objectShader({vertexShader, fragmentShader});

  // Build skybox shader program
  vertexShader = GLT::Shader(GL_VERTEX_SHADER, "shaders/skybox-vert.glsl");
  fragmentShader = GLT::Shader(GL_FRAGMENT_SHADER, "shaders/skybox-frag.glsl");
  GLT::ShaderProgram skyboxShader({vertexShader, fragmentShader});

  // Scene uniforms
  objectShader.GetUniform("aLightPow").SetFVec3(glm::vec3(0.1, 0.1, 0.1));
  objectShader.GetUniform("pLightPow").SetFVec3(glm::vec3(3, 3, 3));
  objectShader.GetUniform("pLightPosWs").SetFVec3(glm::vec3(0, 1, -2));
  objectShader.GetUniform("parallaxCoeff").SetF1(0.1f);

  // Test mesh
  GLT::Mesh testMesh = GenTestCubeIndexed();
  testMesh.AutoGenerateNormals();

  // Skybox
  GLT::CubeMap skybox({
    "textures/skybox/right.jpg",
    "textures/skybox/left.jpg",
    "textures/skybox/top.jpg",
    "textures/skybox/bottom.jpg",
    "textures/skybox/front.jpg",
    "textures/skybox/back.jpg"});


//====[TEMPORARY]============================================================//
  // Input sensitifity stuff
  float rotateSpeed = 1.0f;
	float moveSpeed = 1.0f;
	float mouseSensitivity = 0.003f;
  float dFwd, dRight, dUp, dr = 0.0f;     // camera movement

  // Frame cap stuff
  unsigned frameCount = 0;
  double tStart = window.GetTime();
//====[TEMPORARY]============================================================//


  // Window 2 loop
  while(!window.ShouldClose()) {


//====[TEMPORARY]============================================================//
    // get current time
    float dt = window.GetTimeDelta();

    // Cursor capture control
    glm::vec2 cursorDelta = window.GetCursorDelta() * mouseSensitivity;
    if(window.KeyPressed(GLFW_KEY_ESCAPE)) window.FreeCursor();
    if(window.KeyPressed(GLFW_KEY_M)) window.CaptureCursor();

    // Camera translation & rotation
    dr = dFwd = dRight = dUp = 0.0f;
    if(window.KeyPressed(GLFW_KEY_W)) dFwd += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_S)) dFwd -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_A)) dRight += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_D)) dRight -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_SPACE)) dUp += (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_C)) dUp -= (dt * moveSpeed);
    if(window.KeyPressed(GLFW_KEY_E)) dr += (dt * rotateSpeed);
    if(window.KeyPressed(GLFW_KEY_Q)) dr -= (dt * rotateSpeed);

    // Update window camera
    window.camera.Move(dRight, dUp, dFwd);
    window.camera.MoveLook(-cursorDelta.x, cursorDelta.y, dr);
//====[TEMPORARY]============================================================//


    // Generate transform matrix
    glm::mat4 skyboxTransform = glm::mat4(1.0f);
    glm::mat4 objectTransform = glm::rotate(
      glm::mat4(1.0f),
      (float)window.GetTime() / 3,
      glm::vec3(0, 1, 0));

    // Draw the mesh first, then the skybox
    window.Draw(testMesh, objectShader, objectTransform);
    window.Draw(skybox, skyboxShader, skyboxTransform);

    // Display output
    usleep(1000);
    window.Refresh();
    frameCount++;
  }


//====[TEMPORARY]============================================================//
  // Print out average fps
  double tEnd = window.GetTime();
  std::cout << "Average FPS: " << frameCount / (tEnd - tStart) << "\n";
//====[TEMPORARY]============================================================//


  // All done
  return 0;
}
