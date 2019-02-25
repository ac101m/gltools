#include <GLT/Mesh.hpp>
using namespace GLT;


// Constructor, with automatic indices
Mesh::Mesh(std::vector<vertex_t> vertices) {
  this->vertices = vertices;
  this->indices.reserve(vertices.size());
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->indices.push_back(i);
  }
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Construct the mesh
Mesh::Mesh(std::vector<vertex_t> vertices,
           std::vector<unsigned> indices,
           std::vector<Texture> textures) :
           vertices(vertices), indices(indices), textures(textures) {
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Draw routine
void Mesh::Draw(Camera& camera, ShaderProgram& shader, glm::mat4& transform) {

  // Multiply out the matrices IN THE RIGHT FUCKING ORDER THIS TIME
  // GOD DMAN NON-COMMUTATIVE BASTARDS FKN 4 HOURS RIGHT THERE
  glm::mat4 mvp = camera.GetProjMat() * camera.GetViewMat() * transform;

  // Shader uniform setup
  shader.Use();
  uniform_t uniform = shader.GetUniform("mvp");
  glUniformMatrix4fv(uniform.handle, 1, GL_FALSE, &mvp[0][0]);

  // Bind textures to texture units
  for(unsigned i = 0; i < this->textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    this->textures[i].Bind();
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
