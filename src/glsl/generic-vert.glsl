#version 330 core

// Vertex attribute inputs
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUV;

// Uniforms
uniform mat4 mvp;

// Outputs from the vertex shader
out vec4 vertexColour;
out vec2 texturePos;

void main() {
  gl_Position = mvp * vec4(vertexPosition, 1.0);
  vertexColour = vec4(vertexNormal, 1.0);
  texturePos = vertexUV;
}
