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
    bool UpdateBuffer(void const * const data, unsigned const n);
    static unsigned GetTypeSize(GLenum const type);
    static std::string GetTypeName(GLenum const type);

    // Assert that we have the right type
    inline void AssertType(GLenum const type);
    inline void AssertElementSize(unsigned const size);
    inline void AssertMatch(GLenum const type, unsigned const size);

  public:

    // Constructors
    Uniform(void);
    Uniform(std::string const name,
            GLuint const handle,
            GLenum const type,
            GLint const elemCount);

    // Texture samplers                                   IMPLEMENTED?
    void SetTex2D(int const value);                       //    Y
    void SetTexCube(int const value);                     //    Y

    // Single 4/8
    void SetF1(float const value);                        //    Y
    void SetI1(int const value);                          //
    void SetU1(unsigned const value);                     //
    void SetD1(double const value);                       //

    // 2 element vector 8/16
    void SetFVec2(glm::fvec2* data, unsigned n = 1);      //
    void SetIVec2(glm::ivec2* data, unsigned n = 1);      //
    void SetUVec2(glm::uvec2* data, unsigned n = 1);      //
    void SetDVec2(glm::dvec2* data, unsigned n = 1);      //

    // 3 element vector 12/24
    void SetFVec3(glm::fvec3* data, unsigned n = 1);      //    Y
    void SetIVec3(glm::ivec3* data, unsigned n = 1);      //
    void SetUVec3(glm::uvec3* data, unsigned n = 1);      //
    void SetDVec3(glm::dvec3* data, unsigned n = 1);      //

    // 4 element vector 16/32
    void SetFVec4(glm::fvec4* data, unsigned n = 1);      //
    void SetIVec4(glm::ivec4* data, unsigned n = 1);      //
    void SetUVec4(glm::uvec4* data, unsigned n = 1);      //
    void SetDVec4(glm::dvec4* data, unsigned n = 1);      //

    // 2 by 2 matrix 16/32
    void SetFMat2(glm::fmat2* data, unsigned n = 1);      //
    void SetDMat2(glm::dmat2* data, unsigned n = 1);      //

    // 3 by 3 matrix 36/72
    void SetFMat3(glm::fmat3* data, unsigned n = 1);      //    Y
    void SetDMat3(glm::dmat3* data, unsigned n = 1);      //

    // 4 by 4 matrix 64/128
    void SetFMat4(glm::fmat4* data, unsigned n = 1);      //    Y
    void SetDMat4(glm::dmat4* data, unsigned n = 1);      //

    // 2 by 4 matrix
    void SetFMat4x2(glm::fmat4x2* data, unsigned n = 1);  //
    void SetDMat4x2(glm::dmat4x2* data, unsigned n = 1);  //

    // 4 by 2 matrix
    void SetFMat2x4(glm::fmat2x4* data, unsigned n = 1);  //
    void SetDMat2x4(glm::dmat2x4* data, unsigned n = 1);  //

    // 2 by 3 matrix 24/48
    void SetFMat2x3(glm::fmat2x3* data, unsigned n = 1);  //
    void SetDMat2x3(glm::dmat2x3* data, unsigned n = 1);  //

    // 3 by 2 matrix 24/48
    void SetFMat3x2(glm::fmat3x2* data, unsigned n = 1);  //
    void SetDMat3x2(glm::dmat3x2* data, unsigned n = 1);  //

    // 3 by 4 matrix 48/96
    void SetFMat3x4(glm::fmat3x4* data, unsigned n = 1);  //
    void SetDMat3x4(glm::dmat3x4* data, unsigned n = 1);  //

    // 4 by 3 matrix 48/96
    void SetFMat4x3(glm::fmat4x3* data, unsigned n = 1);  //
    void SetDMat4x3(glm::dmat4x3* data, unsigned n = 1);  //

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
