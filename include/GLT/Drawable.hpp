#ifndef _GLT_DRAWABLE_INCLUDED
#define _GLT_DRAWABLE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Camera.hpp>
#include <GLT/ShaderProgram.hpp>


namespace GLT {

  // Class defines common methods for drawable objects
  class Drawable {
  protected:

    // Model matrix, can't draw without one!
    glm::mat4 modelMatrix;

  public:

    // Constructor, just use an identity matrix
    Drawable(void);

    // Rotation and scale change methods
    void Scale(glm::vec3 scale);
    void Rotate(float angle, glm::vec3 axis);

    // Template draw function
    virtual void Draw(Camera& camera, ShaderProgram& shader);
  };

} // namespace GLT


#endif // _GLT_DRAWABLE_INCLUDED
