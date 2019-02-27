#ifndef _GLT_TEXTURE_INCLUDED
#define _GLT_TEXTURE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/RefCount.hpp>
#include <GLT/Context.hpp>


// Standard
#include <string>


namespace GLT {

  // Context will exist, promise
  class Context;


  // Class represents a texture handle
  class Texture : public RefCount {
  private:

    // Texture path, used as name
    GLuint glHandle;

//====[METHODS]==============================================================//

    // Common initialisation
    void Init(std::string& path, Context& context);
    void LoadFromFile(std::string& path, Context& context);

  public:

    // Constructor, from file
    Texture(std::string path);

    // Get the opengl handle
    GLuint GetGlHandle(void) {return this->glHandle;}

    // Bind and unbind the texture
    void Bind(void) {glBindTexture(GL_TEXTURE_2D, this->glHandle);}
    void Unbind(void) {glBindTexture(GL_TEXTURE_2D, 0);}

    // Destructor, uses reference count
    ~Texture(void);
  };

} // namespace GLT


#endif // _GLT_TEXTURE_INCLUDED
