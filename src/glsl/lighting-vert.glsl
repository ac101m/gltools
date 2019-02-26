#version 330 core

// Vertex attribute inputs
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec3 vNormal;

// Uniforms
uniform mat4 mvpMx;
uniform mat4 mMx;

// Outputs from the vertex shader
out vec2 fUV;
out vec3 fPos;
out vec3 fNormal;

void main() {
  fUV = vUV;
  gl_Position = mvpMx * vec4(vPosition, 1.0);
  fPos = vec3(mMx * vec4(vPosition, 1.0));
  fNormal = vec3(mMx * vec4(vNormal, 1.0));
}
