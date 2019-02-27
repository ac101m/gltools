#version 330 core

// Vertex attribute inputs
layout (location = 0) in vec3 vertPosMs;
layout (location = 1) in vec2 vertUV;
layout (location = 2) in vec3 vertNmlMs;
layout (location = 3) in vec3 vertTanMs;
layout (location = 4) in vec3 vertBitanMs;

// Uniforms
uniform mat4 mMx;
//uniform mat4 vMx;
//uniform mat3 mv3Mx;
uniform mat4 mvpMx;

// Outputs from the vertex shader
out VS_OUT {
  vec3 fragPosWs;
  vec2 fragUV;
  vec3 nmlWs;
  mat3 tbnMx;
} vsOut;

void main() {
  gl_Position = mvpMx * vec4(vertPosMs, 1.0);

  // Generate TBN matrix
  vec3 T = normalize(vec3(mMx * vec4(vertTanMs, 0.0)));
  vec3 B = normalize(vec3(mMx * vec4(vertBitanMs, 0.0)));
  vec3 N = normalize(vec3(mMx * vec4(vertNmlMs, 0.0)));
  vsOut.tbnMx = mat3(T, B, N);

  // Legacy normals
  vsOut.nmlWs = vec3(mMx * vec4(vertNmlMs, 1.0));

  // Fragment position in world space, for lighting
  vsOut.fragPosWs = vec3(mMx * vec4(vertPosMs, 1.0));

  // Pass through UVs
  vsOut.fragUV = vertUV;
}
