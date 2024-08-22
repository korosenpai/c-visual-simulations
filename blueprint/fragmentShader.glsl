#version 400

precision highp float;

uniform vec2 resolution;
// uniform vec2 location;
// uniform float zoom;
uniform int maxIter;

const float PI = 3.14159;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    // uv.x *= resolution.x / resolution.y;
    // uv -= vec2(0.7, 0.5);
    // // uv.x -= 0.5;
    // uv *= zoom;
    // uv -= location;
    // gl_FragColor = vec4(mandelbort(uv), 1.0);
    gl_FragColor = vec4(uv.x, uv.y, 0, 1.0);
}
