#include <GLT/Context.hpp>
using namespace GLT;


// Standard
#include <iostream>
#include <string>


// Track the number of GLFW contexts
int Context::contextCount = 0;
std::mutex Context::contextCountMx;


// Default global context
Context GLT::defaultContext;


// GLFW error callback
void Context::Error(int error, const char* description) {
  std::cerr << "GLFW: " << description << "\n";
}


// Initialise GLEW
void Context::InitGlew(GLFWwindow* window) {
  if(!this->glewInitialised) {

    // Make one of the windows from this context active
    glfwMakeContextCurrent(window);

    // Do the initialisation
    if(glewInit() != GLEW_OK) {
      std::cerr << "Failed to initialise GLEW\n";
      exit(1);
    } else {
      std::cout << "Initialised GLEW\n";
      this->glewInitialised = true;
    }
  }
}


// Common initialisation
Context::Context(void) {

  // Lock the context count static variable
  contextCountMx.lock();

  // If we are the first context, do GLFW setup
  if(contextCount == 0) {

    // Initialise GLFW
    if(!glfwInit()) {
      std::cerr << "Failed to initialise GLFW\n";
      exit(1);
    } else {
      std::cout << "Initialised GLFW\n";
    }

    // Add glfw error callback
    glfwSetErrorCallback(Context::Error);
  }

  // Increment the context count
  contextCount++;
  contextCountMx.unlock();

  // Last window handle, NULL means glfwCreateWindow will
  // kick off a new opengl context.
  this->prevGlfwWindow = NULL;

  // Glew hasn't been intialised yet (we can't until we have a context)
  this->glewInitialised = false;
}


// Make this context current
void Context::MakeCurrent(void) {
  if(this->prevGlfwWindow != NULL) {
    glfwMakeContextCurrent(this->prevGlfwWindow);
  }
}


// Create a window that is attached to this context
GLFWwindow* Context::NewGlfwWindow(glm::vec2 size, std::string name, GLFWmonitor* mon) {

  // Create a GLFW window
  GLFWwindow* glfwWindow = glfwCreateWindow(
    size.x, size.y, name.c_str(), mon, this->prevGlfwWindow);

  // Initialise GLEW
  if(this->prevGlfwWindow == NULL) {
    this->InitGlew(glfwWindow);
  }

  // The next window will share this ones context
  this->prevGlfwWindow = glfwWindow;
  this->MakeCurrent();

  // Return the window handle
  return glfwWindow;
}


// Make a new shader handle within the current context
GLuint Context::NewShaderHandle(ShaderType type) {
  this->MakeCurrent();
  return glCreateShader(type);
}


// Make a new shader handle within the current context
GLuint Context::NewShaderProgramHandle(void) {
  this->MakeCurrent();
  return glCreateProgram();
}


// Make a new vertex buffer object within the current context
GLuint Context::NewVertexArrayHandle(void) {
  this->MakeCurrent();
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return vao;
}


// Make a new vertex buffer object within the current context
GLuint Context::NewBufferHandle(void) {
  this->MakeCurrent();
  GLuint buf;
  glGenBuffers(1, &buf);
  return buf;
}


// Make a new vertex buffer object within the current context
GLuint Context::NewTextureHandle(void) {
  this->MakeCurrent();
  GLuint id;
  glGenTextures(1, &id);
  return id;
}


// Check if a texture has been previously loaded
bool Context::TextureLoaded(std::string& path) {
  auto iterator = this->textures.find(path);
  return (iterator != this->textures.end());
}


// Get a loaded texture, segfaults if it doesn't exist
Texture Context::GetLoadedTexture(std::string& path) {
  return this->textures.find(path)->second;
}


// Add a loaded texture to the
void Context::AddTexture(std::string& path, Texture& texture) {
  this->textures.insert(std::pair<std::string, Texture>(path, texture));
}


// Context going out of scope
Context::~Context(void) {

  // Decrement reference count
  contextCountMx.lock();
  contextCount--;

  // Last one out, turn out the lights
  if(contextCount == 0) {
    glfwTerminate();
  }

  // Unlock mutex
  contextCountMx.unlock();

  // Context has no attached windows at the moment
  this->glewInitialised = false;

  // Print cleanup messages
  std::cout << "Context cleaned up\n";
  if(!contextCount) {
    std::cout << "All contexts destroyed, GLFW terminated\n";
  }
}
