#version 330 core

// Textures
uniform sampler2D texture0;   // colour
uniform sampler2D texture1;   // Normal

// Inputs from vertex shader
in VS_OUT {
  vec2 fragUV;
  vec3 fragPosWs;
  vec3 viewPosCs;
  vec3 viewPosTs;
  vec3 pLightPosCs;
  vec3 pLightPosTs;
} fsIn;

// Lighting inputs
uniform vec3 aLightPow;
uniform vec3 pLightPow;
uniform vec3 pLightPosWs;

// Outputs
out vec4 gl_FragColor;

void main() {

  // Texture sampling
  vec3 texColour = vec3(texture(texture0, fsIn.fragUV)).rgb;
  vec3 texNormal = vec3(texture(texture1, fsIn.fragUV)).rgb;

  // Compute normal from texture normal
  vec3 fragNmlTs = normalize((texNormal * 2.0) - 1.0);

  // Distance from light to fragment
  float dist = length(pLightPosWs - fsIn.fragPosWs);

  // CosTheta? Not sure what this means. Further research required.
  vec3 n = fragNmlTs;
  vec3 l = normalize(fsIn.pLightPosTs);
  float cosTheta = clamp(dot(n, l), 0.0, 1.0);

  // CosAlpha? Also need to read more. Urgh 3d gfx math is complicated
  vec3 E = normalize(fsIn.viewPosTs);
  vec3 R = reflect(-l, n);
  float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

  // Ambient light
  vec3 fragAmbientLight =
    texColour * aLightPow;

  // Diffuse lighting
  vec3 fragDiffuselight =
    (texColour * pLightPow * cosTheta) / (dist * dist);

  // Add up all the lighting terms
  vec3 fragColour = fragAmbientLight + fragDiffuselight;
  gl_FragColor = vec4(fragColour, 1.0);
}
