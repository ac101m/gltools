#ifndef GLT_CUBE_MAP_INCLUDED
#define GLT_CUBE_MAP_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/Drawable.hpp"
#include "GLT/Mesh.hpp"
#include "GLT/Util/RefCount.hpp"


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

    // Constructor, void
    CubeMap() {glGenTextures(1, &this->glHandle);}

    // Constructor, direct from name
    CubeMap(GLuint const glHandle) : glHandle(glHandle) {}

    // Constructor, from paths
    CubeMap(std::vector<std::string> const texPaths);

    // Overridden draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);

    // Required to handle reference counting
    ~CubeMap(void);
  };

}


#endif // GLT_CUBE_MAP_INCLUDED
