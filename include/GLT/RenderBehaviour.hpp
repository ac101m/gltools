#ifndef _GLT_RENDER_BEHAVIOUR_INCLUDED
#define _GLT_RENDER_BEHAVIOUR_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Context.hpp>


namespace GLT {

  // Context class forward declaration
  class Context;


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
    void ApplyAll(void);
    void ApplyDifference(RenderBehaviour& other);
  };

} // namespace GLT


#endif // _GLT_RENDER_BEHAVIOUR_INCLUDED
