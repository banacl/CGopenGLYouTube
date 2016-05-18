//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include<fstream>
#include<glm\glm.hpp>
#include"Primitives\Vertex.h"
#include"Primitives\ShapeGenerator.h"


const float X_DELTA = 0.1;
GLuint numTris = 0;
const GLuint NUM_OF_VERTICES = 3;
const GLuint NUM_FLOATS_PER_VERTEX = 6;
const GLuint TRIANGLE_BYTE_SIZE = NUM_OF_VERTICES *NUM_FLOATS_PER_VERTEX*sizeof(GLfloat);
const GLuint MAX_TRIS = 20;
GLuint programId;
using namespace std;
int windowWidth = 500; int windowHeight = 500;
extern const char*vertexShaderCode;
extern const char*fragmentShaderCode;

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, w / (GLdouble)h, 1.0, 10.0);
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 27:
		exit(0);
		break;
	default:
		break;
	}

}
bool checkStatus(
	GLint objectId,
	PFNGLGETSHADERIVPROC objectPropGetterFunc,
	PFNGLGETSHADERINFOLOGPROC objectInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropGetterFunc(objectId, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropGetterFunc(objectId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar*buffer = new GLchar[infoLogLength];
		GLsizei bufferSize;
		objectInfoLogFunc(objectId, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}
bool checkShaderStatus(GLint shaderId)
{
	return checkStatus(shaderId, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
bool checkProgramStatus(GLint programId)
{
	return checkStatus(programId, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}
string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "Failed to read file" << fileName << std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());

	//clean meInpiut . here it is done by destructor

}
void installShaders()
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	const char*adapter[1];
	string temp = readShaderCode("vertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderId, 1, adapter, 0);

	temp = readShaderCode("fragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderId, 1, adapter, 0);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentShaderId);

	if (!checkShaderStatus(vertexShaderId) || !checkShaderStatus(fragmentShaderId))
		return;
	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);
	if (!checkProgramStatus(programId))
		return;

	glUseProgram(programId);
}
void sendAnotherTriToOpengl()
{
	if (numTris > MAX_TRIS)
		return;
	const GLfloat THIS_TRI_X = -1 + numTris * X_DELTA;

	GLfloat thisTri[] =
	{
		THIS_TRI_X, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		THIS_TRI_X + X_DELTA, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		THIS_TRI_X, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};
	glBufferSubData(GL_ARRAY_BUFFER, numTris*TRIANGLE_BYTE_SIZE, TRIANGLE_BYTE_SIZE, thisTri);
	numTris++;
}
void display()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	//sendAnotherTriToOpengl();
	//glDrawArrays(GL_TRIANGLES, (numTris-1)*NUM_OF_VERTICES, NUM_OF_VERTICES);//
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	
	GLint dominatingColorUniformLocation = glGetUniformLocation(programId, "dominatingColor");
	GLint yFlipUniformLocation = glGetUniformLocation(programId, "yFlip");

	glm::vec3 dominatingColor(1.0f, 0.0f, 0.0f);
	glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
	glUniform1f(yFlipUniformLocation, 1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	dominatingColor.r = 0.0f;
	dominatingColor.g = 1.0f;
	glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
	glUniform1f(yFlipUniformLocation, -1.0f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	
	glutSwapBuffers();
}



void sendDataToOpenGL()
{
	
	ShapeData tri = ShapeGenerator::makeTriangle();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, tri.vertexBufferSize(), tri.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLuint indexArrayBufferID;
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tri.indexBufferSize(), tri.indices, GL_STATIC_DRAW);
	//tri.cleanup();
}


void init()
{
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		exit(0);

	}
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	
	installShaders();//helper function
	
}



int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);

	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	// Set the window size
	glutInitWindowSize(windowWidth, windowHeight);

	// Create the window with the title "Hello,GL"
	glutCreateWindow("Hello, GL");

	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	
	return 0;
}