#include <GLT/Mesh.hpp>
using namespace GLT;


// Sets up the mesh opengl buffers
void VertexBuffer::GenBuffers(const std::vector<vertex_t>& vertices,
                              const std::vector<unsigned>& indices) {

  // Create vertex array object buffer
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  // Set up vertex buffer
  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(vertex_t),
               &vertices[0],
               GL_STATIC_DRAW);

  // Set up index buffer
  glGenBuffers(1, &this->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(unsigned),
               &indices[0],
               GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertex_t), (void*)0);

  // Vertex uvs
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                        sizeof(vertex_t), (void*)offsetof(vertex_t, uv));

  // Vertex normals
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertex_t), (void*)offsetof(vertex_t, normal));

  // Vertex tangents
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertex_t), (void*)offsetof(vertex_t, tangent));

  // Vertex bitangents
  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
                        sizeof(vertex_t), (void*)offsetof(vertex_t, bitangent));

  // Unbind the vertex array
  glBindVertexArray(0);
}


// Blank constructor, no data
VertexBuffer::VertexBuffer(void) {
  this->vao = this->vbo = this->ebo = 0;
  this->vBufLen = new GLsizei(0);
  this->iBufLen = new GLsizei(0);
}


// Initialise vertex positions
VertexBuffer::VertexBuffer(const std::vector<vertex_t>& vertices,
                           const std::vector<unsigned>& indices) {

  this->GenBuffers(vertices, indices);
  this->vBufLen = new GLsizei(vertices.size());
  this->iBufLen = new GLsizei(indices.size());
}


// Destructor with reference count
VertexBuffer::~VertexBuffer(void) {
  if(!this->ReferencedElsewhere()) {
    if(this->vao) glDeleteVertexArrays(1, &this->vao);
    if(this->vbo) glDeleteBuffers(1, &this->vbo);
    if(this->ebo) glDeleteBuffers(1, &this->ebo);
  }
}
