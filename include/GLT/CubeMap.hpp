#ifndef GLT_CUBE_MAP_INCLUDED
#define GLT_CUBE_MAP_INCLUDED


// This project
#ifndef GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Drawable.hpp>
#include <GLT/Mesh.hpp>
#include <GLT/RefCount.hpp>


// Standard
#include <vector>
#include <string>


namespace GLT {

  class CubeMap : public Drawable, public RefCount {
  private:

    // Vertex and cubemap handles
    VertexArray vertexBuffer;
    GLuint glHandle;

//====[METHODS]==============================================================//

    // Load all texture files
    void LoadTextures(std::vector<std::string> const& texPaths);

  public:

    // Constructor
    CubeMap(std::vector<std::string> const texPaths);

    // Overridden draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);

    // Required to handle reference counting
    ~CubeMap(void);
  };

}


#endif // GLT_CUBE_MAP_INCLUDED
