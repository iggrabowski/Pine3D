#version 330
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_scene;
uniform sampler2D u_bloomBlur;
uniform float u_exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(u_scene, TexCoords).rgb;
    vec3 bloomColor = texture(u_bloomBlur, TexCoords).rgb;
    bloomColor = pow(bloomColor, vec3(1.0 / gamma));
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec3 result = vec3(1.0) - exp(-hdrColor * u_exposure);
    // also gamma correct while we're at it
    FragColor = vec4(result, 1.0);
}
