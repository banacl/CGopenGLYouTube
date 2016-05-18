#version 430

in layout(location=0) vec3 position;
in layout(location=1) vec3 inputColor;
uniform vec3 dominatingColor;
uniform float yFlip;
out vec3 outColor;
void main()
{
gl_Position = vec4(position,1.0);
gl_Position.y = gl_position.y *yFlip;
outColor = dominatingColor;
}