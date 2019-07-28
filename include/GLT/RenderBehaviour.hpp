#ifndef GLT_RENDER_BEHAVIOUR_INCLUDED
#define GLT_RENDER_BEHAVIOUR_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Context.hpp"


namespace GLT {

  // Class contains render mode
  class RenderBehaviour {
  private:

    // Polygon mode
    GLenum polyFaceMode;
    GLenum polyDrawMode;

    // Depth testing
    GLenum depthTestFunction;

  public:

//====[METHODS]==============================================================//

    // Constructor, sets reasonable defaults
    RenderBehaviour(void);

    // Sets
    void SetPolyFaceMode(const GLenum fm) {this->polyFaceMode = fm;}
    void SetPolyDrawMode(const GLenum dm) {this->polyDrawMode = dm;}
    void SetDepthTestFunction(const GLenum dt) {this->depthTestFunction = dt;}

    // Gets
    GLenum GetPolyFaceMode(void) {return this->polyFaceMode;}
    GLenum GetPolyDrawMode(void) {return this->polyDrawMode;}
    GLenum GetDepthTestFunction(void) {return this->depthTestFunction;}

    // Apply methods
    void Apply(void);
    void ApplyDifference(RenderBehaviour& other);
  };

} // namespace GLT


#endif // GLT_RENDER_BEHAVIOUR_INCLUDED
