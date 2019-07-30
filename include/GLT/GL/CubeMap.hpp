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

    // Opengl name
    GLuint glName;

    // Vertex array
    VertexArray vertexBuffer;

  public:

    // Constructor, void
    CubeMap() {glGenTextures(1, &this->glName);}

    // Constructor, direct from name
    CubeMap(GLuint const glName) : glName(glName) {}

    // Constructor, from paths
    CubeMap(std::vector<std::string> const texPaths);

    // Load sides of cubemap from files
    void FromFiles(std::vector<std::string> const& texPaths);

    // Overridden mesh draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);

    // Reference counted destructor
    ~CubeMap();
  };

}


#endif // GLT_CUBE_MAP_INCLUDED
