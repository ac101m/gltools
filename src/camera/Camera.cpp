#include <GLT/Camera.hpp>
using namespace GLT;


// Experimental
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


// Standard
#include <iostream>


// Method for common initialisation
void Camera::Init(void) {

  // Default view type is perspective
  this->mode = GLT::CAMERA_MODE_PERSPECTIVE;

  // Initial position, origin
  this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
  this->up = glm::vec3(0.0f, 1.0f, 0.0f);
  this->fwd = glm::vec3(0.0f, 0.0f, 1.0f);
  this->right = glm::vec3(1.0f, 0.0f, 0.0f);

  // Initial view characteristics
  this->fov = glm::radians(45.0f);
  this->zMin = 0.1f;
  this->zMax = 100.0f;
  this->viewRatio = 1.0f;

  // Matrices not calculated yet
  this->viewMatValid = false;
  this->projMatValid = false;
}


// Compute view matrix
void Camera::ComputeProjMat(void) {
  switch(this->mode) {
    case CAMERA_MODE_PERSPECTIVE:
      this->projMat = glm::perspective(
        this->fov, this->viewRatio,
        this->zMin, this->zMax);
      break;
    default:
      std::cerr << "GLT - Camera: Invalid projection mode.\n";
      exit(1);
  }
  this->projMatValid = true;
}


// Compute view matrix
void Camera::ComputeViewMat(void) {
  this->viewMat = glm::lookAt(
    this->pos,
    this->pos + this->fwd,
    this->up);
  this->viewMatValid = true;
}


// Default constructor
Camera::Camera(void) {
  this->Init();
}


// Set view ratio directly
void Camera::SetViewRatio(const float ratio) {
  this->viewRatio = ratio;
  this->projMatValid = false;
}


// Set view ratio from glm vector
void Camera::SetViewRatio(const glm::vec2 size) {
  this->SetViewRatio(size.x / size.y);
}


// Set view ratio from x/y
void Camera::SetViewRatio(const float x, const float y) {
  this->SetViewRatio(x / y);
}


// Set camera position
void Camera::SetPos(const glm::vec3 pos) {
  this->pos = pos;
  this->viewMatValid = false;
}


// Set camera position with individual arguments
void Camera::SetPos(const float x, const float y, const float z) {
  this->SetPos(glm::vec3(x, y, z));
}


// Move camera position
void Camera::Move(const glm::vec3 dPos) {
  this->Move(dPos.x, dPos.y, dPos.z);
}


// Set camera position with individual arguments
void Camera::Move(const float dRight, const float dUp, const float dFwd) {
  this->pos += this->right * dRight;
  this->pos += this->up * dUp;
  this->pos += this->fwd * dFwd;
  this->viewMatValid = false;
}


// member function changes direction camera is looking
void Camera::MoveLook(const float dx, const float dy, const float dr) {

    // rotate cam.fwd & cam.right around cam.up by dx
    this->fwd = glm::rotate(this->fwd, dx, this->up);
    this->right = glm::rotate(this->right, dx, this->up);

    // rotate cam.up & cam.fwd around cam.right by dy
    this->up = glm::rotate(this->up, dy, this->right);
    this->fwd = glm::rotate(this->fwd, dy, this->right);

    // rotate cam.up & cam.right around cam.fwd by dr
    this->up = glm::rotate(this->up, dr, this->fwd);
    this->right = glm::rotate(this->right, dr, this->fwd);

    // indicate that view matrix needs recalculating
    this->viewMatValid = false;
}


// Get the projection matrix
glm::mat4& Camera::GetProjMat(void) {
  if(!this->projMatValid) this->ComputeProjMat();
  return this->projMat;
}


// Get the view matrix
glm::mat4& Camera::GetViewMat(void) {
  if(!this->viewMatValid) this->ComputeViewMat();
  return this->viewMat;
}
