#include "GLT/Util/Drawable.hpp"
using namespace GLT;


// Standard
#include <iostream>


// Template draw routine
void Drawable::Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m) {
  std::cout << "Error: pure virtual function call: Drawable::Draw\n";
  std::cout << "Please override the draw method for any class inheriting from GLT::Drawable.\n";
  exit(1);
}
