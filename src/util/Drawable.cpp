#include <GLT/Drawable.hpp>
using namespace GLT;


// Standard
#include <iostream>


// Template draw routine
void Drawable::Draw(Camera& camera, ShaderProgram& shader, glm::mat4& m) {
  std::cout << "Pure virtual function call: Drawable.Draw\n";
  exit(1);
}
