#version 330 core

// Vertex attribute inputs
layout (location = 0) in vec3 vertPosMs;
layout (location = 1) in vec2 vertUV;
layout (location = 2) in vec3 vertNmlMs;
layout (location = 3) in vec3 vertTanMs;
layout (location = 4) in vec3 vertBitanMs;

// Uniform matrices
uniform mat4 mMx;
uniform mat4 vMx;
uniform mat3 mv3Mx;
uniform mat4 mvpMx;

// Uniform light position
uniform vec3 pLightPosWs;

// Outputs from the vertex shader
out VS_OUT {
  vec2 fragUV;
  vec3 fragPosWs;
  vec3 fragPosTs;
  vec3 viewPosCs;
  vec3 viewPosTs;
  vec3 pLightPosCs;
  vec3 pLightPosTs;
} vsOut;

void main() {
  gl_Position = mvpMx * vec4(vertPosMs, 1.0);

  // Pass through UVs
  vsOut.fragUV = vertUV;

  // Compute transpose TBN matrix
  vec3 vertNmlCs = mv3Mx * normalize(vertNmlMs);
  vec3 vertTanCs = mv3Mx * normalize(vertTanMs);
  vec3 vertBitanCs = mv3Mx * normalize(vertBitanMs);
  mat3 tbnMx = transpose(mat3(vertTanCs, vertBitanCs, vertNmlCs));

  // Fragment position in world space, for lighting
  vsOut.fragPosWs = vec3(mMx * vec4(vertPosMs, 1.0));
  vsOut.fragPosTs = tbnMx * vec3(vMx * vec4(vsOut.fragPosWs, 1.0));

  // Vector from vertex to camera
  vec3 vertPosCs = vec3(vMx * mMx * vec4(vertPosMs, 1.0));
  vsOut.viewPosCs = vec3(0.0, 0.0, 0.0) - vertPosCs;
  vsOut.viewPosTs = tbnMx * vsOut.viewPosCs;

  // Vector from vertex to light
  vec3 pLightPosCs = vec3(vMx * vec4(pLightPosWs, 1.0));
  vsOut.pLightPosCs = pLightPosCs + vsOut.viewPosCs;
  vsOut.pLightPosTs = tbnMx * vsOut.pLightPosCs;
}
