#version 330 core

layout (location = 0) in vec3 vPosWs;

uniform mat4 pMx;
uniform mat4 vMx;

out VS_OUT {
  vec3 cubeMapUV;
} vsOut;

void main() {
  vsOut.cubeMapUV = vPosWs;
  vec4 pos = pMx * vMx * vec4(vPosWs, 1.0);
  gl_Position = pos.xyww;
}
