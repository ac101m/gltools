#ifndef _GLT_MESH_INCLUDED
#define _GLT_MESH_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/Context.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/Drawable.hpp>


// Standard
#include <vector>


namespace GLT {

  // Vertex structure
  typedef struct {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 uv;
  } vertex_t;


  // Container class for vertex buffer
  class VertexBuffer {
  private:

    // Reference counter, for handling destruction of gl buffers
    RefCount rc;

    // OpenGL handles
    GLuint vao, vbo, ebo;

    // Buffer lengths
    GLsizei *vBufLen;
    GLsizei *iBufLen;

//====[METHODS]==============================================================//

    // Sets up the mesh opengl buffers
    void GenBuffers(std::vector<vertex_t>& vertices,
                    std::vector<unsigned>& indices,
                    Context& context);

  public:

    // Constructors with context initialisation
    VertexBuffer(void);
    VertexBuffer(std::vector<vertex_t>& vertices, std::vector<unsigned>& indices);

    // Bind this vertex buffer
    void Bind(void) {glBindVertexArray(this->vao);}
    void Unbind(void) {glBindVertexArray(0);}

    // Get index and vertex counts
    GLsizei GetIndexBufferLength(void) {return *(this->iBufLen);}
    GLsizei GetVertexBufferLength(void) {return *(this->vBufLen);}

    // Destructor
    ~VertexBuffer(void);
  };


  // Container class for meshes
  class Mesh {
  private:

    // Mesh data
    std::vector<vertex_t> vertices;
    std::vector<unsigned> indices;

    // Vertex buffer
    VertexBuffer vertexBuffer;

  public:

    // Initialise geometry and indices
    Mesh(std::vector<vertex_t> vertices);
    Mesh(std::vector<vertex_t> vertices, std::vector<unsigned> indices);

    // Get a copy of the vertex buffer
    VertexBuffer GetVertexBuffer(void) {return this->vertexBuffer;}
  };


  // Container for mesh instance
  class MeshInstance : public Drawable {
  private:

    // Reference to the buffer
    VertexBuffer vertexBuffer;

  public:

    // Initialise from a mesh
    MeshInstance(Mesh& mesh);

    // Override draw routine
    void Draw(Camera& camera, ShaderProgram& shader);
  };

} // namespace GLT

#endif // _GLT_MESH_HPP
