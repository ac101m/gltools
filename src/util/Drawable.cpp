#include <GLT/Drawable.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Constructor, just set up an identity matrix
Drawable::Drawable(void) {
  this->modelMatrix = glm::mat4(1.0f);
}


// Scale the instance
void Drawable::Scale(glm::vec3 scale) {
  this->modelMatrix = glm::scale(this->modelMatrix, scale);
}


// Rotate the instance
void Drawable::Rotate(float angle, glm::vec3 axis) {
  this->modelMatrix = glm::rotate(this->modelMatrix, angle, axis);
}


// Template draw routine
void Drawable::Draw(Camera& camera, ShaderProgram& shader) {
  std::cout << "Pure virtual function call: Drawable.Draw\n";
  exit(1);
}
