#include <GLT/RenderBehaviour.hpp>
using namespace GLT;


// Initialisation, set some reasonable defaults
void RenderBehaviour::Init(void) {

  // Default behaviours
  this->polyFaceMode = GL_FRONT_AND_BACK;
  this->polyDrawMode = GL_FILL;

  // Depth testing
  this->depthTestFunction = GL_LESS;
}


// Constructor with default context
RenderBehaviour::RenderBehaviour(void) {
  this->Init();
}


// Apply everything
void RenderBehaviour::Apply(void) {
  glPolygonMode(this->polyFaceMode, this->polyDrawMode);
  glDepthFunc(this->depthTestFunction);
}
