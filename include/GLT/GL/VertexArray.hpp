#ifndef GLT_VERTEXARRAY_INCLUDED
#define GLT_VERTEXARRAY_INCLUDED


// Internal
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Util/Vertex.hpp"
#include "GLT/GL/Buffer.hpp"
#include "GLT/Util/GlObject.hpp"


// Standard
#include <vector>


namespace GLT {

  // Container class for vertex array object
  class VertexArray : public GlObject {
  private:

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

    // Bind this vertex buffer
    void Bind() const;
    void Unbind() const;

    // Get index and vertex counts
    GLsizei GetIndexBufferLength() {return *(this->iBufLen);}
    GLsizei GetVertexBufferLength() {return *(this->vBufLen);}

    // Destructor
    ~VertexArray();
  };

} // namespace GLT

#endif // GLT_VERTEXARRAY_INCLUDED
