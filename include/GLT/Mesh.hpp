#ifndef _GLT_VERTEX_ARRAY_OBJECT_INCLUDED
#define _GLT_VERTEX_ARRAY_OBJECT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/Context.hpp>


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


  // Class for containing mesh data
  class Mesh {
  private:

    // Mesh data
    std::vector<vertex_t> vertices;
    std::vector<unsigned> indices;

    // OpenGL handles
    GLuint vao, vbo, ebo;

    // Reference counter, for handling deallocation of gl stuff
    RefCount rc;

    // Sets up the mesh opengl buffers
    void GenBuffers(Context *context);

  public:

    // Initialise vertex positions
    Mesh(std::vector<vertex_t> vertices, std::vector<unsigned> indices);

    // Get the number of vertices in the mesh
    unsigned GetSize(void) {return this->vertices.size();}

    // Destructor
    ~Mesh(void);
  };

} // namespace GLT

#endif // _GLT_VERTEX_ARRAY_OBJECT_HPP
