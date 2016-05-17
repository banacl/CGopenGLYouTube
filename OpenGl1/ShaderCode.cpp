const char* vertexShaderCode =
"#version 430\r\n"
""
"in layout(location=0) vec2 position;"
"in layout(location=1) vec3 inputColor;"
"out vec3 outColor;"
"void main()"
"{"
"gl_Position = vec4(position,0.0,1.0);"
"outColor = inputColor;"
"}";

const char* fragmentShaderCode =
"#version 430\r\n"
"out vec4 daColor;"
"in vec3 outColor;"
"void main()"
"{"
"daColor = vec4(outColor,1.0);"
"}";