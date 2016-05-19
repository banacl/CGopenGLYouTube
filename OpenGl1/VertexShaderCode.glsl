#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 inputColor;
in layout(location=2) float offset;
uniform mat4 fullTranformMatrix;

out vec3 outColor;
void main()
{
gl_Position = vec4(position.x+offset,position.y,0.0,1.0);
outColor = inputColor;
}