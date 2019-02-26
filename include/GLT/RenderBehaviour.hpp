#ifndef _GLT_RENDER_BEHAVIOUR_INCLUDED
#define _GLT_RENDER_BEHAVIOUR_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


namespace GLT {

  // Class contains render mode
  class RenderBehaviour {
  private:

    // Polygon mode
    GLenum polyFaceMode;
    GLenum polyDrawMode;

    // Depth testing
    GLenum depthTestFunction;

//====[METHODS]==============================================================//

    // Common initialisation
    void Init(void);

  public:

    // Constructor, sets reasonable defaults
    RenderBehaviour(void);

    // Polygon mode sets
    void SetPolyFaceMode(GLenum fm) {this->polyFaceMode = fm;}
    void SetPolyDrawMode(GLenum dm) {this->polyDrawMode = dm;}

    // Depth testing sets
    void SetDepthTestFunction(GLenum dt) {this->depthTestFunction = dt;}

    // Apply method, applies everything contained within
    void Apply(void);
  };

} // namespace GLT


#endif // _GLT_RENDER_BEHAVIOUR_INCLUDED
