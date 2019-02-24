#include <GLT/Mesh.hpp>
using namespace GLT;


// Constructor, initialise the vertex buffer
MeshInstance::MeshInstance(Mesh& mesh) :
  vertexBuffer(mesh.GetVertexBuffer()) {
}


// Override draw routine
void MeshInstance::Draw(Camera& camera, ShaderProgram& shader) {

  // Multiply out the matrices IN THE RIGHT FUCKING ORDER THIS TIME
  // GOD DMAN NON-COMMUTATIVE BASTARDS FKN 4 HOURS RIGHT THERE
  glm::mat4 mvp = camera.GetProjMat() *
                  camera.GetViewMat() *
                  this->modelMatrix;

  // Shader uniform setup
  shader.Use();
  uniform_t uniform = shader.GetUniform("mvp");
  glUniformMatrix4fv(uniform.handle, 1, GL_FALSE, &mvp[0][0]);

  // Draw the things
  this->vertexBuffer.Bind();
  glDrawElements(
    GL_TRIANGLES,
    this->vertexBuffer.GetIndexBufferLength(),
    GL_UNSIGNED_INT, 0);
  this->vertexBuffer.Unbind();
}
