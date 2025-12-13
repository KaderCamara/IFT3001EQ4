#version 150

uniform sampler2D tex0;
uniform bool uEnableToneMapping;
uniform bool uUseACES;

in vec2 vTexCoord;
out vec4 fragColor;

// ACES tone mapping curve
vec3 ACESFilm(vec3 x) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x*(a*x+b))/(x*(c*x+d)+e), 0.0, 1.0);
}

void main() {
    vec3 color = texture(tex0, vTexCoord).rgb;
    if (uEnableToneMapping) {
        if (uUseACES) {
            color = ACESFilm(color);
        } else {
            // simple gamma tone mapping
            color = pow(color, vec3(1.0/2.2));
        }
    }
    fragColor = vec4(color, 1.0);
}
