# gltools
A simple opengl framework for quickly chucking 3D things on the screen.

It can:
- Make your windows
- Compile your shaders
- Cache your shader program uniform assignments
- Load your texture files (and cache them)
- Compute your tangent space basis vectors
- Manage your view and projection matrices

It cannot:
- Cook your dinner

Planned future features:
- Defaults for missing textures
- Updatable vertex buffers
- Render to texture
- Better context creation and management
- Model loading
- Built in camera control schemes

Note:
Uniform set methods are declared, see include/GLT/Uniform.hpp. Only a few currently have implementations though; fvec3, fmat3, fmat4 & float. Implementations can be found in src/shader/Uniform.cpp.
