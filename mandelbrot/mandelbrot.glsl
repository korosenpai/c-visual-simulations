#version 400

precision highp float;

uniform vec2 resolution;
uniform vec2 location;
uniform float zoom;
uniform int maxIter;
uniform int colorScheme;

out vec4 color;


vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    vec2 c = gl_FragCoord.xy / resolution.y * 4.0 - 2.0;
    c /= zoom;
    c += location;

    vec2 z = c;
    float i;
    for (i = 0; i < maxIter; i++) {
        z = vec2(
            pow(z.x, 2) - pow(z.y, 2),
            2 * z.x * z.y
        ) + c;

        if (length(z) > 2.0) break;

    }

    if (i == maxIter) {
        color = vec4(0, 0, 0, 1);
    } else {
        float val = i / float(maxIter);

        if (colorScheme == 0)
            color = vec4(val, val, val, 1); // grayscale
        else if (colorScheme == 1)
            color = vec4(hsv2rgb(vec3(val, 1.0, 1.0)), 1.0); // colorize

    }
}
