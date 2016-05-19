#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 inputColor;
uniform mat4 fullTranformMatrix;

out vec3 outColor;
void main()
{
vec4 v = vec4(position,1.0);
gl_Position = fullTranformMatrix*v;
outColor = inputColor;
}