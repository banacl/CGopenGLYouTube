#version 430

in layout(location=0) vec3 vertexPositionModel;//model position not projected
in layout(location=1) vec3 vertexColor;
in layout(location=2) vec3 normalModel;

uniform mat4 modelToWorldToProjectionMatrix;//this maps coords from model to world to projected space and cant be used for lighting
uniform mat4 modelToWorldMatrix;
uniform vec3 ambientLight;

out vec3 vertexPositionWorld;
out vec3 normalWorld;

void main()
{
vec4 v = vec4(vertexPositionModel,1.0);
gl_Position =modelToWorldToProjectionMatrix * v;//projected space

//vertexPositionWorld = vertexPositionModel;//thePosition is assuming world space when it is model space
//our light position uniform used in fragment shader is in the world space so we need to be consistent.
//normalWorld = normalModel;

vertexPositionWorld = vec3(modelToWorldMatrix * v);
normalWorld = vec3(modelToWorldMatrix *vec4(normalModel,0));
}