#version 330 core
out vec4 FragColor;

in vec3 TexCoords;
uniform samplerCube u_Skybox;
// simple exposure + Reinhard tone mapping + gamma correction

// TODO: maybe adjustable?
uniform float u_Exposure = 1.2;
uniform float u_Gamma = 2.2;

void main()
{
    vec3 hdrColor = texture(u_Skybox, TexCoords).rgb;

    // Exposure
    vec3 mapped = hdrColor * u_Exposure;

    // Reinhard tone mapping
    mapped = mapped / (mapped + vec3(1.0));

    // Gamma correction (linear -> sRGB)
    mapped = pow(mapped, vec3(1.0 / u_Gamma));

    FragColor = vec4(mapped, 1.0);
}
