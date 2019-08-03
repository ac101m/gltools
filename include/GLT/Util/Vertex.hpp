#ifndef GLT_VERTEX_INCLUDED
#define GLT_VERTEX_INCLUDED


// External
#include "glm/glm.hpp"


// Standard
#include <iostream>


namespace GLT {

  // Vertex structure
  typedef struct {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec3 bitangent;
    void Print(void) {
      std::cout << position.x << "," << position.y << "," << position.z << "\t";
      std::cout << normal.x << "," << normal.y << "," << normal.z << "\t";
      std::cout << tangent.x << "," << tangent.y << "," << tangent.z << "\t";
      std::cout << bitangent.x << "," << bitangent.y << "," << bitangent.z << "\t";
      std::cout << "\n";
    }
  } vertex_t;

} // namespace GLT

#endif // GLT_VERTEX_INCLUDED
