#version 330 core

// Textures
uniform sampler2D texture0;   // Colour
uniform sampler2D texture1;   // Normal
uniform sampler2D texture2;   // Height
uniform sampler2D texture3;   // Ambient occlusion

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


// My novel recursive parallax algorithm
vec2 ParallaxMapping3(vec2 texCoords, vec3 viewDir) {

  // View parallax coefficient
  vec2 viewParallaxCoeff = viewDir.xy * parallaxCoeff;

  // Initial depth
  float layerDepthLast = 0.0;
  float layerDepthCurrent = 1.0;

  // UV Deltas
  vec2 uvDeltaLast = vec2(0.0, 0.0);
  vec2 uvDeltaCurrent = viewParallaxCoeff * layerDepthCurrent;

  // Initial samples
  float sampleLast = texture(texture2, texCoords).r;
  float sampleCurrent = texture(texture2, texCoords - uvDeltaCurrent).r;

  // Layer sample depths
  float layerDepthDeltaLast = sampleLast;
  float layerDepthDeltaCurrent = sampleCurrent - layerDepthCurrent;

  // Iterate in towards result
  const float iterationCount = 8;
  for(int i = 0; i < iterationCount; i++) {

    // Compute new depth delta
    float layerDepthDelta = (layerDepthLast - layerDepthCurrent) / 2;
    layerDepthDelta *= -(sign(layerDepthDeltaLast) * sign(layerDepthDeltaCurrent));

    // Compute new layer depth
    layerDepthLast = layerDepthCurrent;
    layerDepthCurrent += layerDepthDelta;

    // Compute new uv delta
    uvDeltaLast = uvDeltaCurrent;
    uvDeltaCurrent = viewParallaxCoeff * layerDepthCurrent;

    // Get new sample
    sampleLast = sampleCurrent;
    sampleCurrent = texture(texture2, texCoords - uvDeltaCurrent).r;

    // Get new layer depth delta
    layerDepthDeltaLast = layerDepthDeltaCurrent;
    layerDepthDeltaCurrent = sampleCurrent - layerDepthCurrent;
  }

  // May be able to use a bit of linear algebra here to make it even cleaner
  // Until then we'll just output the current uv delta, it's close enough
  return texCoords - uvDeltaCurrent;
}


void main() {

  // Parallax coordinate computation
  vec3 viewDir = normalize(fsIn.viewPosTs - fsIn.fragPosTs);
  vec2 fragParallaxUV = ParallaxMapping3(fsIn.fragUV, viewDir);

  // Rest of the texture sampling
  vec3 texColour = vec3(texture(texture0, fragParallaxUV)).rgb;
  vec3 texNormal = vec3(texture(texture1, fragParallaxUV)).rgb;
  float texAO = vec3(texture(texture3, fragParallaxUV)).r;

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
  vec3 fragAmbientLight = texColour * aLightPow * texAO;

  // Diffuse lighting
  vec3 fragDiffuselight = (texColour * pLightPow * cosTheta) / (dist * dist);

  // Add up all the lighting terms
  vec3 fragColour = fragAmbientLight + fragDiffuselight;
  gl_FragColor = vec4(fragColour, 1.0);
}
