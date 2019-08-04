#ifndef GLT_CUBE_MAP_INCLUDED
#define GLT_CUBE_MAP_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/Drawable.hpp"
#include "GLT/Mesh.hpp"
#include "GLT/Util/RefCount.hpp"
#include "GLT/Util/ElementStack.hpp"
#include "GLT/GL/Texture.hpp"


// Standard
#include <vector>
#include <string>


namespace GLT {

  class CubeMap : public Texture, public Drawable {
  private:

    // Vertex array
    VertexArray vertexBuffer;

    // Cube map bind stack
    static ElementStack<Texture> bindStack;

  public:

    // Initialise cube map bind stack
    static void Init();

    // Constructor, from paths
    CubeMap(std::vector<std::string> const texPaths);

    // Load sides of cubemap from files
    void FromFiles(std::vector<std::string> const& texPaths);

    // Overridden mesh draw method
    void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);

    // Set texture integer parameter
    void Parameteri(GLenum const pname, GLint const param);

    // Bind and unbind this
    void Bind() const {this->BindAny(GL_TEXTURE_CUBE_MAP, bindStack);}
    void Unbind() const {this->UnbindAny(GL_TEXTURE_CUBE_MAP, bindStack);}
  };

} // namespace GLT

#endif // GLT_CUBE_MAP_INCLUDED
