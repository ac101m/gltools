#include <GLT/Mesh.hpp>
using namespace GLT;


// Vertex array bind stack
ElementStack<VertexBuffer> VertexBuffer::bindStack;


// Vertex array bind stack initialisation
void VertexBuffer::Init() {
  bindStack.Clear();
  bindStack.Push(GLT::VertexBuffer());
  glBindVertexArray(0);
}


// Sets up the mesh opengl buffers
void VertexBuffer::GenBuffers(
  std::vector<vertex_t> const& vertices,
  std::vector<unsigned> const& indices) {

  // Create vertex array object buffer
  glGenVertexArrays(1, &this->glHandle);
  this->Bind();

  // Create vertex buffer object
  this->vertexBuffer = Buffer(vertices, GL_STATIC_DRAW);
  this->vertexBuffer.Bind(GL_ARRAY_BUFFER);

  // Create index buffer object
  this->indexBuffer = Buffer(indices, GL_STATIC_DRAW);
  this->indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);

  // Enable vertex attribute arrays
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);

  // Vertex positions
  glVertexAttribPointer(
    0, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), (void*)0);

  // Vertex uvs
  glVertexAttribPointer(
    1, 2, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), (void*)offsetof(vertex_t, uv));

  // Vertex normals
  glVertexAttribPointer(
    2, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), (void*)offsetof(vertex_t, normal));

  // Vertex tangents
  glVertexAttribPointer(
    3, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), (void*)offsetof(vertex_t, tangent));

  // Vertex bitangents
  glVertexAttribPointer(
    4, 3, GL_FLOAT, GL_FALSE,
    sizeof(vertex_t), (void*)offsetof(vertex_t, bitangent));

  // Unbind the vertex array object handle
  this->Unbind();

  // Unbind vertex and index buffers
  this->vertexBuffer.Unbind(GL_ARRAY_BUFFER);
  this->indexBuffer.Unbind(GL_ELEMENT_ARRAY_BUFFER);

  // Update vertex buffer element counts
  *(this->vBufLen) = vertices.size();
  *(this->iBufLen) = vertices.size();
}


// Blank constructor, no data
VertexBuffer::VertexBuffer() {
  this->glHandle = 0;
  this->vBufLen = new GLsizei(0);
  this->iBufLen = new GLsizei(0);
}


// Initialise vertex positions
VertexBuffer::VertexBuffer(
  std::vector<vertex_t> const& vertices,
  std::vector<unsigned> const& indices) {

  this->vBufLen = new GLsizei(0);
  this->iBufLen = new GLsizei(0);
  this->GenBuffers(vertices, indices);
}


// Bind and remember state of current binding
void VertexBuffer::Bind() {

  // If the currently bound object is not this one, bind this texture
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    glBindVertexArray(this->glHandle);
  }

  // Push this object onto the bind stack
  bindStack.Push(*this);
}


// Restore the bind target to its previous state
void VertexBuffer::Unbind() {

  // Can't unbind object that isn't currently bound without breaking stuff
  if(this->glHandle != bindStack.Top().GetGlHandle()) {
    std::cerr << "ERROR: Attempt to unbind already unbound vertex buffer\n";
    std::cerr << "Did you forget to call unbind?\n";
    exit(1);
  }

  // Pop this object off the bind stack
  bindStack.Pop();

  // Restore the previous binding
  if(bindStack.Top().GetGlHandle() != this->glHandle) {
    glBindVertexArray(bindStack.Top().GetGlHandle());
  }
}


// Destructor with reference count
VertexBuffer::~VertexBuffer() {
  if(!this->ReferencedElsewhere()) {
    glDeleteVertexArrays(1, &this->glHandle);
    delete this->vBufLen;
    delete this->iBufLen;
  }
}
