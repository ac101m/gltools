#include <GLT/Mesh.hpp>
using namespace GLT;


// Sets up the mesh opengl buffers
void Mesh::GenBuffers(Context *context) {

  // Create out vertex array object handle
  this->vao = context->NewVertexArrayHandle();
  glBindVertexArray(this->vao);

  // Set up vertex buffer
  this->vbo = context->NewBufferHandle();
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER,
               this->vertices.size() * sizeof(vertex_t),
               &this->vertices[0],
               GL_STATIC_DRAW);

  // Set up index buffer
  this->ebo = context->NewBufferHandle();
  glBindBuffer(GL_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ARRAY_BUFFER,
               this->indices.size() * sizeof(unsigned),
               &this->indices[0],
               GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)0);

  // Vertex normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, normal));

  // Vertex uvs
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, uv));

  // Unbind the vertex array
  glBindVertexArray(0);
}


// Initialise vertex positions
Mesh::Mesh(std::vector<vertex_t> vertices, std::vector<unsigned> indices) {
  this->vertices = vertices;
  this->indices = indices;
  this->GenBuffers(&GLT::defaultContext);
}


// Destructor with reference count
Mesh::~Mesh(void) {
  if(this->rc.GetCount() == 0) {
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
  }
}
