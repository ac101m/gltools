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


// Other
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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

    // Sets up the mesh opengl buffers
    void GenBuffers(std::vector<vertex_t>& vertices,
                    std::vector<unsigned>& indices,
                    Context *context);

  public:

    // Constructors with context initialisation
    VertexBuffer(void);
    VertexBuffer(std::vector<vertex_t>& vertices, std::vector<unsigned>& indices);

    // Bind this vertex buffer
    void Bind(void) {glBindVertexArray(this->vao);}
    void Unbind(void) {glBindVertexArray(0);}

    // Destructor
    ~VertexBuffer(void);
  };


  // Container class for meshes
  class Mesh: public Drawable {
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

    // Draw routine
    void Draw(Window& window, ShaderProgram& shader, glm::mat4& mmx);
  };

} // namespace GLT

#endif // _GLT_MESH_HPP
