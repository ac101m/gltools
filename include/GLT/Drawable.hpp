#ifndef GLT_DRAWABLE_INCLUDED
#define GLT_DRAWABLE_INCLUDED


// This project
#ifndef GLT_MASTER_INCLUDED
#include "GLT/Master.hpp"
#endif
#include "GLT/Camera.hpp"
#include "GLT/ShaderProgram.hpp"


namespace GLT {

  // Class defines common methods for drawable objects
  class Drawable {
  public:

    // Template draw function
    virtual void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);
  };

} // namespace GLT


#endif // GLT_DRAWABLE_INCLUDED
