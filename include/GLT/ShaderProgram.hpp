#ifndef _GLT_SHADER_PROGRAM_INCLUDED
#define _GLT_SHADER_PROGRAM_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/Shader.hpp>
#include <GLT/RefCount.hpp>
#include <GLT/ElementCache.hpp>


// Standard
#include <string>
#include <vector>
#include <map>


namespace GLT {


  // Class to contain uniform data
  class Uniform : public RefCount {
  private:

    // Allocate memory based on type and size
    void AllocateDataMemory(void);

  public:

    // Uniform data
    GLint size;
    GLenum type;
    GLuint handle;
    void* data;

//====[METHODS]==============================================================//

    // Constructors
    Uniform(void);
    Uniform(GLint const size,
            GLenum const type,
            GLuint const handle,
            void const * const data);

    // Destructor, cleans up data memory
    ~Uniform(void);
  };


  // Class wraps an opengl shader program handle
  class ShaderProgram : public RefCount {
  private:

    // Parent context pointer
    Context* parentContext;

    // OpenGL handle
    GLuint glHandle;

    // Uniform locations in shader, raw pointer for shallow copy
    ElementCache<std::string, Uniform>* uniformCache;

//====[METHODS]==============================================================//

    // Links an array of shaders into this program
    void LinkShaders(const std::vector<Shader>& shaders);

    // Uniform map stuff
    void FillUniformCache(void);
    Uniform GetUniform(const std::string& name);

  public:

    // Constructor
    ShaderProgram(const std::vector<Shader> shaders);

    // Use this shader program
    void Use(void);

    // Set texture uniform
    void SetTexture(unsigned const texUnit,
                    std::string const& name,
                    Texture const& tex);

    // Set other uniforms
    void SetVec3(std::string const name, glm::vec3 const value);
    void SetMat3(std::string const name, glm::mat3 const value);
    void SetMat4(std::string const name, glm::mat4 const value);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
