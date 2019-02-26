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


// Auto generate normals
void Mesh::AutoGenerateNormals(void) {

  // Reset vertex normals
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].normal = glm::vec3(0, 0, 0);
  }

  // Add up face normals
  vertex_t *v[3];
  for(unsigned i = 0; i < this->indices.size(); i += 3) {
    for(unsigned j = 0; j < 3; j++) v[j] = &this->vertices[this->indices[i + j]];
    glm::vec3 faceNormal = glm::cross(
      v[2]->position - v[0]->position,
      v[0]->position - v[1]->position);
    for(unsigned j = 0; j < 3; j++) v[j]->normal += faceNormal;
  }

  // Normalise vertex normals
  for(unsigned i = 0; i < this->vertices.size(); i++) {
    this->vertices[i].normal = glm::normalize(this->vertices[i].normal);
  }

  // Regenerate the vertex buffer
  this->vertexBuffer = VertexBuffer(this->vertices, this->indices);
}


// Draw routine
void Mesh::Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m) {

  // Multiply out the matrices IN THE RIGHT FUCKING ORDER THIS TIME
  // GOD DMAN NON-COMMUTATIVE BASTARDS FKN 4 HOURS RIGHT THERE
  glm::mat4 mvp = camera.GetProjMat() * camera.GetViewMat() * m;

  // Shader uniform setup
  shader.SetMat4("mMx", m);
  shader.SetMat4("mvpMx", mvp);

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
