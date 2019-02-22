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
Mesh::Mesh(std::vector<vertex_t> vertices, std::vector<unsigned> indices) /*: vertexBuffer(VertexBuffer(vertices, indices))*/ {
  this->vertices = vertices;
  this->indices = indices;
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Override the draw method
void Mesh::Draw(Window& window, ShaderProgram& shader, glm::mat4& mmx) {
  window.MakeCurrent();

  // Shader uniform setup
  shader.Use();
  uniform_t uniform = shader.GetUniform("mvp");
  glUniformMatrix4fv(uniform.handle, 1, GL_FALSE, &mmx[0][0]);

  // Draw the things
  this->vertexBuffer.Bind();
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  this->vertexBuffer.Unbind();
}
