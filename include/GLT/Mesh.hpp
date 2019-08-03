#ifndef GLT_MESH_INCLUDED
#define GLT_MESH_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/RefCount.hpp"
#include "GLT/GL/ShaderProgram.hpp"
#include "GLT/Util/Drawable.hpp"
#include "GLT/GL/Texture.hpp"
#include "GLT/GL/Buffer.hpp"
#include "GLT/Util/Vertex.hpp"
#include "GLT/GL/VertexArray.hpp"


// Standard
#include <vector>
#include <iostream>


namespace GLT {

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
