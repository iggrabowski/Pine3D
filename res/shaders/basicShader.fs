#version 130

in vec2 texCoord0;
in vec3 normal0;

uniform sampler2D sampler;

void main()
{
	gl_FragColor = texture2D(sampler, texCoord0);
}
