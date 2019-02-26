#version 330 core

// Textures
uniform sampler2D texture0;

// Inputs
in vec2 fUV;
in vec3 fPos;
in vec3 fNormal;

// Lighting inputs
uniform vec3 ambientLightPow;
uniform vec3 pointLightPow;
uniform vec3 pointLightPos;

// Outputs
out vec4 gl_FragColor;

void main() {

  // Colour from the texture
  vec3 fColour = vec3(texture(texture0, fUV));

  // Direct lighting component
  vec3 norm = normalize(fNormal);
  vec3 pointLightDirection = normalize(pointLightPos - fPos);
  float diff = max(dot(norm, pointLightDirection), 0.0);
  vec3 lPointDiffuse = fColour * pointLightPow * diff;

  // Ambient lighting component
  vec3 lAmbient = fColour * ambientLightPow;

  // Add up all the lighting terms
  vec3 lTotal = lAmbient + lPointDiffuse;
  gl_FragColor = vec4(lTotal, 1.0);
}
