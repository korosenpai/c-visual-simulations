#version 400

precision highp float;

uniform vec2 resolution;
uniform float time;

out vec4 fragColor;

// graph functinos: https://graphtoy.com/

// generate palette with trygonometry
// https://iquilezles.org/articles/palettes/
vec3 palette(float t) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b * cos(6.28318 * (c * t + d));
}

void main() {
    // gl_FragCoord range: 0...resolution
    // clip space: -1...1

    vec2 uv = gl_FragCoord.xy / resolution; // range 0...1
    uv -= 0.5; // -0.5...0.5
    uv *= 2.0; // -1...1 so 0,0 is center of canves
    // fragColor = vec4(uv, 0, 1); // mango

    // fix aspect ratio, so it doesnt steetch on x
    // if canvas wasnt square with this the sketch is not stretched
    uv.x *= resolution.x / resolution.y;

    // will be not changed to maintain knowledge of
    // real center of screen
    vec2 uv0 = uv;

    vec3 finalColor = vec3(0.0);
    // create more subspaces and increase fractal pattern
    // (iterations = 1 causes no effect)
    float iterations = 4.0;
    for (float i = 0.0; i < iterations; i++) {

        // scale clip space to center mini screens created
        // by fract function
        // 2 to get symmetric,
        // 1.5 to get asymmetric
        uv *= 1.5;

        // extract only digits after decimal point
        // (used to divide screen in subparts)
        uv = fract(uv);
        // as done before to put range -0.5...0.5
        uv -= 0.5;

        // sdf of circle of radius 0.5
        // sdf: function that gives distance from input (vec2) and given shape
        // https://iquilezles.org/articles/distfunctions2d/
        float d = length(uv); // distance from uv to center of screen (of each repetition)
                              // d -= 0.5; // positive outside circle and negative inside (0 on border)

        // exp(-x) is a smooth way to shift
        d *= exp(-length(uv0)); // to break symmetry

        // get color of palette based on distance
        // time is to offset palette and color to make it to add 
        // more dynamism and color shift
        // length to break palette from all miniscreens and make them coordinate
        // in one same palette
        // i is to introduce light color offsets
        vec3 col = palette(length(uv0) + i * 0.4  + time * 0.4);

        // create repetition of circle
        // divide by same amount to remove stretched color
        d = sin(d * 8. + time) / 8.;

        // make center of circle white
        d = abs(d);

        // step(float val, float x): return 0(black) if x < val; else 1(white)
        // everything less than 0.1 is black, else white
        // very cutty circle
        // d = step(0.1, d);


        // smothstep (float val, float val2, float x)
        // black when x < val, white when x > val2, and smooths the jump
        // more smooth circle
        // d = smoothstep(0.0, 0.1, d);

        // neon effect is easy with inverse function
        // scale inverse function down to be seen in clip space
        // smaller the less glow
        // d = 0.01 / d;

        // same as inverse function
        // 0..1 -> darker colors go closer to 0 (lesser effects on light colors)
        d = pow(0.01 / d, 1.2);

        // add colors
        // col *= d;
        finalColor += col * d;
    }


    fragColor = vec4(finalColor, 1.0);

}

