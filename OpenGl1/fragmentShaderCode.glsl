#version 430
out vec4 daColor;
in vec3 outColor;
void main()
{
daColor = vec4(outColor,1.0);
}