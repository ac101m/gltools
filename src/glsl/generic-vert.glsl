#version 330 core

// Layout of vertex attributes
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

// Uniforms
uniform mat4 mvp;

// Outputs from the vertex shader
out vec4 colour;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  colour = vec4(normal, 1.0);
}
