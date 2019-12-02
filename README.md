# gltools
A simple opengl framework for quickly chucking 3D things on the screen.

It can:
- Make your windows
- Compile your shaders
- Cache your shader program uniform assignments
- Load your texture files (and cache them)
- Compute your tangent space basis vectors
- Manage your view and projection matrices
- Render to your textures

It cannot:
- Cook your dinner

Planned future features:
- Defaults for missing textures
- Updatable vertex buffers
- Better context creation and management
- Model loading
- Built in camera control schemes

Note:
Uniform set methods are declared, see include/GLT/Uniform.hpp. Only a few currently have implementations though; fvec3, fmat3, fmat4 & float. Implementations can be found in src/shader/Uniform.cpp.

# Build instructions:
This is not a complete library, lots of bits are missing. Only bother with it if it is required by something else. You have been warned.

You will need:
- GNU make
- A working installation of GCC (you'll need to modify the makefile to use another compiler)
- A Linux OS, you probably _may_ be able to build it under windows using MinGW, but I haven't tried. Best of luck to you.
- OpenGL framework 3 (Package name: libglfw3-dev)
- OpenGL extension wrangler (Package name: libglew2.0)

Once all that is done, start the build by navigating to the root of the source tree and running `make lib` your libraries and headers will appear in bin/install.
