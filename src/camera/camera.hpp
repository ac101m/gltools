#ifndef _GLT_CAMERA_INCLUDED
#define _GLT_CAMERA_INCLUDED


// Matrix math
#include <glm/glm.hpp>


// Begin GLT namespace
namespace GLT {

  // Camera modes
  typedef enum {
    CAMERA_MODE_ORTHOGRAPHIC,
    CAMERA_MODE_PERSPECTIVE
  } CameraMode_t;


  // Class contains camera data
  class Camera {
    private:
      // Camera metadata
      CameraMode_t mode;

      // Matrix calculation ready
      bool viewMatValid;
      bool projMatValid;

    public:
      // Constructors
      void Init(void);
      Camera(CameraMode_t mode);

      // Sets for various camera properties

      // Mutation methods

      // Gets for matrices
  };

} // namespace GLT

#endif // _GLT_CAMERA_INCLUDED
