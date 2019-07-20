#ifndef _GLT_MESH_INCLUDED
#define _GLT_MESH_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/ShaderProgram.hpp>
#include <GLT/Drawable.hpp>
#include <GLT/Texture.hpp>


// Standard
#include <vector>
#include <iostream>


namespace GLT {

  // Vertex structure
  typedef struct {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    void Print(void) {
      std::cout << position.x << "," << position.y << "," << position.z << "\t";
      std::cout << normal.x << "," << normal.y << "," << normal.z << "\t";
      std::cout << tangent.x << "," << tangent.y << "," << tangent.z << "\t";
      std::cout << bitangent.x << "," << bitangent.y << "," << bitangent.z << "\t";
      std::cout << "\n";
    }
  } vertex_t;


  // Container class for vertex buffer
  class VertexBuffer : public RefCount {
  private:

    // OpenGL handles
    GLuint vao, vbo, ebo;

    // Buffer lengths
    GLsizei* vBufLen;
    GLsizei* iBufLen;

//====[METHODS]==============================================================//

    // Sets up the mesh opengl buffers
    void GenBuffers(const std::vector<vertex_t>& vertices,
                    const std::vector<unsigned>& indices);

  public:

    // Constructors with context initialisation
    VertexBuffer();
    VertexBuffer(const std::vector<vertex_t>& vertices,
                 const std::vector<unsigned>& indices);

    // Bind this vertex buffer
    void Bind(void) {glBindVertexArray(this->vao);}
    void Unbind(void) {glBindVertexArray(0);}

    // Get index and vertex counts
    GLsizei GetIndexBufferLength(void) {return *(this->iBufLen);}
    GLsizei GetVertexBufferLength(void) {return *(this->vBufLen);}

    // Destructor
    ~VertexBuffer();
  };


  // Container class for meshes
  class Mesh : public Drawable {
  protected:

    // Mesh data
    std::vector<vertex_t> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture> textures;

    // Vertex buffer
    VertexBuffer vertexBuffer;

//====[METHODS]==============================================================//

    // Common initialisation
    void Init();

    // Generate tangent basis, assumes valid normals
    void GenTangentSpaceBasis();

    // Bind textures
    void BindTextureArray();

  public:

    // Initialise geometry and indices
    Mesh(std::vector<vertex_t> vertices);
    Mesh(std::vector<vertex_t> vertices,
         std::vector<unsigned> indices,
         std::vector<Texture> textures);

    // Generate normals
    void AutoGenerateNormals();

    // Yes, really
    void Print();

    // Overridden draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& transform);
  };

} // namespace GLT

#endif // _GLT_MESH_HPP
