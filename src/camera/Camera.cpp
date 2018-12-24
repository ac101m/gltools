#include <GLT/Camera.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Method for common initialisation
void Camera::Init(void) {

  // Default view type is perspective
  this->mode = GLT::CAMERA_MODE_PERSPECTIVE;

  // Initial position, origin
  this->pos = glm::vec3(0.0f);
  this->up = glm::vec3(0.0f, 1.0f, 0.0f);
  this->fwd = glm::vec3(0.0f, 0.0f, 1.0f);
  this->right = glm::vec3(1.0f, 0.0f, 0.0f);

  // Initial view characteristics
  this->fov = glm::radians(45.0f);
  this->zMin = 0.1f;
  this->zMax = 100.0f;
  this->viewRatio = 1;

  // Matrices not calculated yet
  this->viewMatValid = false;
  this->projMatValid = false;
}


// Compute view matrix
glm::mat4 Camera::ComputeProjMat(void) {
  switch(this->mode) {
    case CAMERA_MODE_PERSPECTIVE:
      return glm::perspective(
        this->fov, this->viewRatio,
        this->zMin, this->zMax);
      break;
    default:
      std::cerr << "GLT - Camera: Invalid projection mode.\n";
      exit(1);
  }
}


// Compute view matrix
glm::mat4 Camera::ComputeViewMat(void) {

}


// Default constructor
Camera::Camera(void) {
  this->Init();
}


// Set camera position
void Camera::SetPos(const glm::vec3 pos) {
  this->pos = pos;
}


// Set camera position with individual arguments
void Camera::SetPos(const float x, const float y, const float z) {
  this->SetPos(glm::vec3(x, y, z));
}


// Move camera position
void Camera::Move(const glm::vec3 dPos) {
  this->pos += dPos;
}


// Set camera position with individual arguments
void Camera::Move(const float x, const float y, const float z) {
  this->Move(glm::vec3(x, y, z));
}


// Get the projection matrix
glm::mat4* Camera::GetProjMat(void) {
  if(!this->projMatValid) {
    this->projMat = this->ComputeProjMat();
    projMatValid = true;
  }
  return &this->projMat;
}


// Get the view matrix
glm::mat4* Camera::GetViewMat(void) {
  if(!this->viewMatValid) {
    this->viewMat = this->ComputeViewMat();
    projMatValid = true;
  }
  return &this->viewMat;
}
