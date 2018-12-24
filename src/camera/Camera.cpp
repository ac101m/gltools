#include <GLT/Camera.hpp>
using namespace GLT;


// Method for common initialisation
void Camera::Init(void) {
  this->viewMatValid = false;
  this->projMatValid = false;
}


// Constructor with mode set
Camera::Camera(CameraMode_t mode) {
  this->Init();
  this->mode = mode;
}
