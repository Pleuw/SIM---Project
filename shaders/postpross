#version 330;

uniform sampler2D depth;
uniform sampler2D color;

const float fogdensite;
const vec3 fogcolor;

void main(void)
{

    vec2 uv = gl_FragCoord.xy/resolution.xy;
    uv.x *= resolution.x/resolution.y;

const float LOG2 = 1.442695;
float z = texture2D(depth,uv);
//z = 2.0 * near * far / (far + near - (2.0 * depth -1.0) * (far - near)); // linear

float fogFactor = exp2( -fogdensite * 
                   fogdensite * 
                   z * 
                   z * 
                   LOG2 );
fogFactor = clamp(fogFactor, 0.0, 1.0);

gl_FragColor = mix(fogcolor, color, fogFactor );
}
