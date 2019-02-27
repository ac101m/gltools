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

    // Parent context pointer
    Context* parentContext;

    // OpenGL handle
    GLuint glHandle;

    // Uniform locations in shader, raw pointer for shallow copy
    std::map<std::string, uniform_t> *uniformMap;

//====[METHODS]==============================================================//

    // Links an array of shaders into this program
    void LinkShaders(const std::vector<Shader>& shaders);

    // Uniform map stuff
    void BuildUniformMap(void);
    uniform_t GetUniform(const std::string& name);

  public:

    // Constructor
    ShaderProgram(const std::vector<Shader> shaders);

    // Use this shader program
    void Use(void);

    // Set uniforms
    void SetTexture(const unsigned texUnit,
                    const std::string name,
                    const Texture tex);
                    
    void SetVec3(const std::string name, const glm::vec3 value);
    void SetMat3(const std::string name, const glm::mat3 value);
    void SetMat4(const std::string name, const glm::mat4 value);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
