#include <GLT/Drawable.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Constructor, just set up an identity matrix
Drawable::Drawable(void) {
  this->modelMatrix = glm::mat4(1.0f);
}


// Template draw routine
void Drawable::Draw(Camera& camera, ShaderProgram& shader) {
  std::cout << "Pure virtual function call: Drawable.Draw\n";
  exit(1);
}
