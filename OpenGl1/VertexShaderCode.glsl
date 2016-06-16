#version 430

in layout(location=0) vec3 position;//model position not projected
in layout(location=1) vec3 inputColor;
in layout(location=2) vec3 normal;

uniform mat4 fullTranformMatrix;//this maps coords from model to projected space and cant be used for lighting
uniform mat4 modelToWorldMatrix;
uniform vec3 ambientLight;

out vec3 thePosition;
out vec3 theNormal;

void main()
{
vec4 v = vec4(position,1.0);
gl_Position =fullTranformMatrix * v;//projected space

//thePosition = position;//thePosition is assuming world space when it is model space
//our light position uniform used in fragment shader is in the world space so we need to be consistent.
thePosition = vec3(modelToWorldMatrix * v);
//theNormal = normal;
theNormal = vec3(modelToWorldMatrix *vec4(normal,0));
}