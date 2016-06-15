#version 430

in layout(location=0) vec3 position;//model position not projected
in layout(location=1) vec3 inputColor;
in layout(location=2) vec3 normal;

uniform mat4 fullTranformMatrix;
uniform vec3 ambientLight;

out vec3 outColor;
void main()
{
vec4 v = vec4(position,1.0);
gl_Position =fullTranformMatrix * v;//projected space
outColor = normal;
}