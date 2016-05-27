#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 inputColor;
in layout(location=2) float offset;
in layout(location=3) mat4 tranformationMatrix;

out vec3 outColor;
void main()
{
vec4 v = vec4(position,1.0);
gl_Position =tranformationMatrix * v;
outColor = inputColor;
}