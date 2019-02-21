#ifndef _GLT_DRAWABLE_INCLUDED
#define _GLT_DRAWABLE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif
#include <GLT/ShaderProgram.hpp>


// Standard
#include <iostream>


namespace GLT {

  // Class defines common methods for drawable
  class Drawable {
  public:

    // Template draw function
    virtual void Draw(ShaderProgram& shader) {
      std::cout << "Pure virtual function call: Drawable.Draw\n";
      exit(1);
    }
  };

} // namespace GLT


#endif // _GLT_DRAWABLE_INCLUDED
