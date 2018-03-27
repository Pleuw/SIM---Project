#version 330

in vec2 pos;

out vec4 outBuffer;

vec2 hash(vec2 p) {
  p = vec2( dot(p,vec2(127.1,311.7)),
        dot(p,vec2(269.5,183.3)) );
 
  return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

float gnoise(in vec2 p) {
  vec2 i = floor( p );
  vec2 f = fract( p );
   
  vec2 u = f*f*(3.0-2.0*f);
 
  return mix( mix( dot( hash( i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
           dot( hash( i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
          mix( dot( hash( i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
           dot( hash( i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

float pnoise(in vec2 p,in float amplitude,in float frequency,in float persistence, in int nboctaves) {
  float a = amplitude;
  float f = frequency;
  float n = 0.0;
 
  for(int i=0;i<nboctaves;++i) {
    n = n+a*gnoise(p*f);
    f = f*2.;
    a = a*persistence;
  }
 
  return n;
}


void main() {
  vec3 motion = vec3(0.); // could be controlled via a global uniform variable
  float p = pnoise(pos+motion.xy,2.0,4.0,0.5,10)+motion.z;

  outBuffer = vec4(p*0.5+0.5);
}
