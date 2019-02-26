#ifndef _GLT_SHADER_PROGRAM_INCLUDED
#define _GLT_SHADER_PROGRAM_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Shader.hpp>
#include <GLT/RefCount.hpp>


// Standard
#include <string>
#include <vector>
#include <map>


namespace GLT {


  // Struct to contain uniform data
  typedef struct {
    GLint size;
    GLenum type;
    GLuint handle;
  } uniform_t;


  // Class wraps an opengl shader program handle
  class ShaderProgram : public RefCount {
  private:

    // OpenGL handle
    GLuint glHandle;

    // Uniform locations in shader, raw pointer for shallow copy
    std::map<std::string, uniform_t> *uniformMap;

//====[METHODS]==============================================================//

    // Links an array of shaders into this program
    void LinkShaders(std::vector<Shader>& shaders);

    // Uniform map stuff
    void LocateUniforms(void);
    uniform_t GetUniform(std::string& name);

    // Common initialisation
    void Init(std::vector<Shader>& shaders, Context& context);

  public:

    // Constructor
    ShaderProgram(std::vector<Shader> shaders);
    ShaderProgram(std::vector<Shader> shaders, Context& context);

    // Use this shader program
    void Use(void);

    // Set uniforms
    void SetVec3(std::string name, glm::vec3 value);
    void SetMat4(std::string name, glm::mat4 value);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
