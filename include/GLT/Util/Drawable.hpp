#ifndef GLT_DRAWABLE_INCLUDED
#define GLT_DRAWABLE_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif
#include "GLT/Camera.hpp"
#include "GLT/GL/ShaderProgram.hpp"


namespace GLT {

  // Class defines common methods for drawable objects
  class Drawable {
  public:

    // Template draw function
    virtual void Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m);
  };

} // namespace GLT


#endif // GLT_DRAWABLE_INCLUDED
