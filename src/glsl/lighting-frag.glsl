#version 330 core

// Textures
uniform sampler2D texture0;   // colour
uniform sampler2D texture1;   // Normal
uniform sampler2D texture2;   // Height

// Inputs from vertex shader
in VS_OUT {
  vec2 fragUV;
  vec3 fragPosWs;
  vec3 fragPosTs;
  vec3 viewPosCs;
  vec3 viewPosTs;
  vec3 pLightPosCs;
  vec3 pLightPosTs;
} fsIn;

// Lighting inputs
uniform vec3 aLightPow;
uniform vec3 pLightPow;
uniform vec3 pLightPosWs;

// Parallax mapping inputs
uniform float parallaxCoeff;

// Outputs
out vec4 gl_FragColor;


vec2 ParallaxMapping1(vec2 texCoords, vec3 viewDir) {
  float height = -vec3(texture(texture2, fsIn.fragUV)).r;
  vec2 p = viewDir.xy / viewDir.z * (height * parallaxCoeff);
  return texCoords - p;
}


vec2 ParallaxMapping2(vec2 texCoords, vec3 viewDir) {
  const float numLayers = 10;
  float layerDepth = 1.0 / numLayers;
  float currentLayerDepth = 0.0;
  vec2 P = viewDir.xy * parallaxCoeff;
  vec2 deltaTexCoords = P / numLayers;
  vec2  currentTexCoords     = texCoords;
  float currentDepthMapValue = texture(texture2, currentTexCoords).r;
  while(currentLayerDepth < currentDepthMapValue) {
      currentTexCoords -= deltaTexCoords;
      currentDepthMapValue = texture(texture2, currentTexCoords).r;
      currentLayerDepth += layerDepth;
  }
  vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
  float afterDepth  = currentDepthMapValue - currentLayerDepth;
  float beforeDepth = texture(texture2, prevTexCoords).r - currentLayerDepth + layerDepth;
  float weight = afterDepth / (afterDepth - beforeDepth);
  vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);
  return finalTexCoords;
}

/*
// My novel recursive parallax algorithm
vec2 ParallaxMapping3(vec2 texCoords, vec3 viewDir) {
  const float iterationCount = 6;

}
*/

void main() {

  // Parallax coordinate computation
  vec3 viewDir = normalize(fsIn.viewPosTs - fsIn.fragPosTs);
  vec2 fragParallaxUV = ParallaxMapping2(fsIn.fragUV, viewDir);

  // Rest of the texture sampling
  vec3 texColour = vec3(texture(texture0, fragParallaxUV)).rgb;
  vec3 texNormal = vec3(texture(texture1, fragParallaxUV)).rgb;

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

  // Ambient lighting
  vec3 fragAmbientLight = texColour * aLightPow;

  // Diffuse lighting
  vec3 fragDiffuselight = (texColour * pLightPow * cosTheta) / (dist * dist);

  // Add up all the lighting terms
  vec3 fragColour = fragAmbientLight + fragDiffuselight;
  gl_FragColor = vec4(fragColour, 1.0);
}
