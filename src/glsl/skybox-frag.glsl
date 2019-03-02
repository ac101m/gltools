#version 330 core

uniform samplerCube skyBox;

in VS_OUT {
  vec3 cubeMapUV;
} fsIn;

out vec4 gl_FragColor;

void main() {
    gl_FragColor = texture(skyBox, fsIn.cubeMapUV);
}
