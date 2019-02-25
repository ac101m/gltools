#version 330 core

// Inputs
in vec4 vertexColour;
in vec2 texturePos;

// Uniforms
uniform sampler2D texture0;

// Outputs
out vec4 gl_FragColor;

void main() {
  gl_FragColor = texture(texture0, texturePos);
}
