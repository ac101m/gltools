#ifndef GLT_CAMERA_INCLUDED
#define GLT_CAMERA_INCLUDED


// Matrix math
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


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

    // Matrices and matrix flags
    glm::mat4 projMat;
    glm::mat4 viewMat;
    bool viewMatValid;
    bool projMatValid;

    // Camera vectors
    glm::vec3 pos;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 fwd;

    // View characteristics
    float fov;
    float zMin;
    float zMax;
    float viewRatio;

//====[METHODS]==============================================================//

    // Initialisation
    void Init(void);

    // Matrix calculations
    void ComputeProjMat(void);
    void ComputeViewMat(void);

  public:

    // Initialisation
    Camera(void);

    // Set view ratio
    void SetViewRatio(const float ratio);
    void SetViewRatio(const glm::vec2 size);
    void SetViewRatio(const float x, const float y);

    // Set camera position
    void SetPos(const glm::vec3 pos);
    void SetPos(const float x, const float y, const float z);

    // Move camera (position delta)
    void Move(const glm::vec3 pos);
    void Move(const float x, const float y, const float z);

    // Change the camera look direction
    void MoveLook(const float dx, const float dy, const float dr);

    // Matrix gets for rendering
    glm::mat4& GetProjMat(void);
    glm::mat4& GetViewMat(void);
  };

} // namespace GLT

#endif // GLT_CAMERA_INCLUDED
