#ifndef GLT_MESH_INCLUDED
#define GLT_MESH_INCLUDED


// This project
#ifndef GLT_MASTER_INCLUDED
#include "GLT/Master.hpp"
#endif
#include "GLT/RefCount.hpp"
#include "GLT/ShaderProgram.hpp"
#include "GLT/Drawable.hpp"
#include "GLT/Texture.hpp"
#include "GLT/Buffer.hpp"


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
  class VertexArray : public RefCount {
  private:

    // Vertex array object handle
    GLuint glHandle;

    // Vertex and index buffers
    Buffer vertexBuffer;
    Buffer indexBuffer;

    // Buffer lengths
    GLsizei* vBufLen;
    GLsizei* iBufLen;

    // vertex array bind stack
    static ElementStack<VertexArray> bindStack;

//====[METHODS]==============================================================//

    // Sets up the mesh opengl buffers
    void GenBuffers(
      std::vector<vertex_t> const& vertices,
      std::vector<unsigned> const& indices);

  public:

    // Initialise bind stacks
    static void Init();

    // Constructors with context initialisation
    VertexArray();
    VertexArray(
      std::vector<vertex_t> const& vertices,
      std::vector<unsigned> const& indices);

    // Return
    GLuint GetGlHandle() {return glHandle;}

    // Bind this vertex buffer
    void Bind();
    void Unbind();

    // Get index and vertex counts
    GLsizei GetIndexBufferLength() {return *(this->iBufLen);}
    GLsizei GetVertexBufferLength() {return *(this->vBufLen);}

    // Destructor
    ~VertexArray();
  };


  // Container class for meshes
  class Mesh : public Drawable {
  protected:

    // Mesh data
    std::vector<vertex_t> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture> textures;

    // Vertex buffer
    VertexArray vertexBuffer;

//====[METHODS]==============================================================//

    // Generate tangent basis, assumes valid normals
    void GenTangentSpaceBasis();

    // Bind textures
    void BindTextureArray();

  public:

    // Initialise without indices
    Mesh(std::vector<vertex_t> vertices);

    // Initialise with indices and textures
    Mesh(std::vector<vertex_t> vertices,
         std::vector<unsigned> indices,
         std::vector<Texture> textures);

    // Generate normals and tangent space basis
    void AutoGenerateNormals();

    // Yes, really
    void Print();

    // Overridden draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& transform);
  };

} // namespace GLT

#endif // GLT_MESH_INCLUDED
