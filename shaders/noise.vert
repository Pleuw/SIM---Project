#version 330

// input attributes
layout(location = 0) in vec3 position;

out vec2 pos;

void main() {
  // no need for any particular transformation (Identity matrices)
  pos = position.xy*0.5+0.5;
  gl_Position = vec4(position,1);
}