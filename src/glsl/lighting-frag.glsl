#version 330 core

// Textures
uniform sampler2D texture0;   // colour
uniform sampler2D texture1;   // Normal

// Inputs from vertex shader
in VS_OUT {
  vec3 fragPosWs;
  vec2 fragUV;
  vec3 nmlWs;
  mat3 tbnMx;
} fsIn;

// Lighting inputs
uniform vec3 aLightPow;
uniform vec3 pLightPow;
uniform vec3 pLightPosWs;

// Outputs
out vec4 gl_FragColor;

void main() {

  // Texture sampling
  vec3 colour = vec3(texture(texture0, fsIn.fragUV)).rgb;
  vec3 normal = vec3(texture(texture1, fsIn.fragUV)).rgb;

  // Do normal mapping stuff TODO
  normal = normalize((normal * 2.0) - 1.0);
  normal = normalize(fsIn.tbnMx * normal);

  // Lighting vector and distance
  vec3 pLightVec = pLightPosWs - fsIn.fragPosWs;
  float dist = length(pLightVec);

  // Diffuse point light with inverse square
  float diff = max(dot(normal, normalize(pLightVec)), 0.0) / (dist * dist);
  vec3 pLightDiffuse = colour * pLightPow * diff;

  // Ambient light
  vec3 aLight = colour * aLightPow;

  // Add up all the lighting terms
  vec3 lTotal = aLight + pLightDiffuse;
  gl_FragColor = vec4(lTotal, 1.0);
}
