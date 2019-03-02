#ifndef _GLT_CUBE_MAP_INCLUDED
#define _GLT_CUBE_MAP_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Drawable.hpp>
#include <GLT/Mesh.hpp>
#include <GLT/Context.hpp>
#include <GLT/RefCount.hpp>


// Standard
#include <vector>
#include <string>


namespace GLT {

  class CubeMap : public Drawable, public RefCount {
  private:
    Context* parentContext;

    // Vertex and cubemap handles
    VertexBuffer vertexBuffer;
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


#endif // _GLT_CUBE_MAP_INCLUDED
