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

    // Uniform data
    GLuint handle;
    GLenum type;
    GLint elemCount;

    // Data and element count
    unsigned bufSize;
    void* buf;

    // Name string
    std::string* name;

//====[METHODS]==============================================================//

    // Allocate memory based on type and size
    void AllocateBuffer(void);
    static unsigned GetTypeSize(GLenum const type);
    static std::string GetTypeName(GLenum const type);

    // Assert that we have the right type
    inline void AssertType(GLenum const type);
    inline void AssertDataSize(unsigned const size);
    inline void AssertMatch(GLenum const type, unsigned const size);

  public:

    // Constructors
    Uniform(void);
    Uniform(std::string const name,
            GLuint const handle,
            GLenum const type,
            GLint const elemCount);

    // Texture samplers                       IMPLEMENTED?
    void SetTex2D(int const value);           //    Y

    // Single 4/8
    void SetF1(float const value);            //
    void SetI1(int const value);              //
    void SetU1(unsigned const value);         //
    void SetD1(double const value);           //

    // 2 element vector 8/16
    void SetFVec2(glm::fvec2 const value);    //
    void SetIVec2(glm::ivec2 const value);    //
    void SetUVec2(glm::uvec2 const value);    //
    void SetDVec2(glm::dvec2 const value);    //

    // 3 element vector 12/24
    void SetFVec3(glm::fvec3 const value);    //    Y
    void SetIVec3(glm::ivec3 const value);    //
    void SetUVec3(glm::uvec3 const value);    //
    void SetDVec3(glm::dvec3 const value);    //

    // 4 element vector 16/32
    void SetFVec4(glm::fvec4 const value);    //
    void SetIVec4(glm::ivec4 const value);    //
    void SetUVec4(glm::uvec4 const value);    //
    void SetDVec4(glm::dvec4 const value);    //

    // 2 by 2 matrix 16/32
    void SetFMat2(glm::fmat2 const value);    //
    void SetDMat2(glm::dmat2 const value);    //

    // 3 by 3 matrix 36/72
    void SetFMat3(glm::fmat3 const value);    //    Y
    void SetDMat3(glm::dmat3 const value);    //

    // 4 by 4 matrix 64/128
    void SetFMat4(glm::fmat4 const value);    //    Y
    void SetDMat4(glm::dmat4 const value);    //

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
    Uniform GetUniform(const std::string name);

    // Destructor, clean up GL handle
    ~ShaderProgram(void);
  };

} // namespace GLT


#endif // _GLT_SHADER_PROGRAM_INCLUDED
