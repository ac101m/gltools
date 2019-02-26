#include <GLT/Mesh.hpp>
using namespace GLT;


// Sets up the mesh opengl buffers
void VertexBuffer::GenBuffers(std::vector<vertex_t>& vertices,
                              std::vector<unsigned>& indices,
                              Context& context) {

  // Create vertex array object buffer
  this->vao = context.NewVertexArrayHandle();
  glBindVertexArray(this->vao);

  // Set up vertex buffer
  this->vbo = context.NewBufferHandle();
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(vertex_t),
               &vertices[0],
               GL_STATIC_DRAW);

  // Set up index buffer
  this->ebo = context.NewBufferHandle();
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(unsigned),
               &indices[0],
               GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)0);

  // Vertex uvs
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, uv));

  // Vertex normals
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, normal));

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
VertexBuffer::VertexBuffer(std::vector<vertex_t>& vertices, std::vector<unsigned>& indices) {
  this->GenBuffers(vertices, indices, GLT::defaultContext);
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
