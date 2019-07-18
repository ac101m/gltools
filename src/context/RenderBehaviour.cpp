#include <GLT/RenderBehaviour.hpp>
using namespace GLT;


// Constructor with default context
RenderBehaviour::RenderBehaviour(void) {

  // Default polygon modes
  this->polyFaceMode = GL_FRONT_AND_BACK;
  this->polyDrawMode = GL_FILL;

  // Depth testing
  this->depthTestFunction = GL_LESS;
}


// Apply method for normal usage
void RenderBehaviour::Apply(void) {
  this->ApplyDifference(Context::GetCurrentRenderBehaviour());
  Context::SetCurrentRenderBehaviour(*this);
}


// Apply everything indiscriminately
void RenderBehaviour::ApplyAll(void) {
  glPolygonMode(this->polyFaceMode, this->polyDrawMode);
  glDepthFunc(this->depthTestFunction);
}


// Apply only the parts that have changed
void RenderBehaviour::ApplyDifference(RenderBehaviour& other) {

  // Polygon draw behaviour
  if((other.GetPolyFaceMode() != this->polyFaceMode) ||
     (other.GetPolyDrawMode() != this->polyDrawMode)) {
     glPolygonMode(this->polyFaceMode, this->polyDrawMode);
  }

  // Dept test behaviour
  if(other.GetDepthTestFunction() != this->depthTestFunction) {
    glDepthFunc(this->depthTestFunction);
  }
}
