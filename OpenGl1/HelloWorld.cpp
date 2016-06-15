//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include<fstream>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"Primitives\Vertex.h"
#include"Primitives\ShapeGenerator.h"
#include"Camera.h"

const float X_DELTA = 0.1;
GLuint numTris = 0;
const GLuint NUM_OF_VERTICES = 3;
const GLuint NUM_FLOATS_PER_VERTEX = 6;
const GLuint TRIANGLE_BYTE_SIZE = NUM_OF_VERTICES *NUM_FLOATS_PER_VERTEX*sizeof(GLfloat);
const GLuint MAX_TRIS = 20;
GLuint programId;
GLuint cubeNumIndicies;
GLuint arrowNumIndicies;
GLuint planeNumIndices;
using namespace std;
using glm::mat4;
using glm::vec3;
int windowWidth = 1000; int windowHeight = 500;
extern const char*vertexShaderCode;
extern const char*fragmentShaderCode;
Camera camera;
GLuint theBufferId;

GLuint cubeVertexArrayObjectId;
GLuint arrowVertexArrayObjectId;
GLuint planeVertexArrayObjectID;

GLuint cubeIndexBufferOffsetInBytes;
GLuint arrowIndexBufferOffsetInBytes;
GLuint planeIndexByteOffset;

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, w / (GLdouble)h, 1.0, 10.0);
}
void mouse(int x, int y)
{
	glm::vec2 mousePos(x, y);
	camera.mouseUpdate(mousePos);
	glutPostRedisplay();

}
void keyboard(unsigned char key, int x, int y)
{
	switch (key){
	case 27:
		exit(0);
		break;
	case 'w':
		camera.moveForward();
			break;
	case 's':
		camera.moveBackward();
			break;
	case 'a':
		camera.strafeLeft();
			break;
	case 'd':
		camera.strafeRight();
			break;
	case 'r':
		camera.moveUp();
			break;
	case 'f':
		camera.moveDown();
			break;
	default:
		break;
	}
	glutPostRedisplay();
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
	
	GLint ambientLightUniformLocation = glGetUniformLocation(programId, "ambientLight");
	vec3 ambientLight(0.9f, 0.9f, 0.9f);
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);

	//cube1

	glBindVertexArray(cubeVertexArrayObjectId);
	mat4 rotationMatrix = glm::rotate(mat4(), 45.0f, vec3(1.0f, 0.0f, 0.0f));
	mat4 translationMatrix = glm::translate(mat4(), vec3(-3.0f, 0.0f, -6.0f));
	mat4 projectionMatrix = glm::perspective(60.0f, ((float)windowWidth / windowHeight), 0.1f, 15.0f);

	mat4 fullTransformMatrix = projectionMatrix*camera.getWorldToViewMatrix()*translationMatrix*rotationMatrix;
	GLint fullTranformMatrixUniformLocation = glGetUniformLocation(programId, "fullTranformMatrix");

	glUniformMatrix4fv(fullTranformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, cubeNumIndicies, GL_UNSIGNED_SHORT, (void*)cubeIndexBufferOffsetInBytes);
	//cube 2
	rotationMatrix = glm::rotate(mat4(), 45.0f, vec3(1.0f, 0.0f, 0.0f));
	translationMatrix = glm::translate(mat4(), vec3(3.0f, 0.0f, -6.0f));
	projectionMatrix = glm::perspective(60.0f, ((float)windowWidth / windowHeight), 0.1f, 15.0f);

	fullTransformMatrix = projectionMatrix*camera.getWorldToViewMatrix() *translationMatrix*rotationMatrix;

	glUniformMatrix4fv(fullTranformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, cubeNumIndicies, GL_UNSIGNED_SHORT, (void*)cubeIndexBufferOffsetInBytes);
	//arrow
	glBindVertexArray(arrowVertexArrayObjectId);

	rotationMatrix = glm::rotate(mat4(), 45.0f, vec3(1.0f, 0.0f, 0.0f));
	translationMatrix = glm::translate(mat4(), vec3(0.0f, 0.0f, -6.0f));
	projectionMatrix = glm::perspective(60.0f, ((float)windowWidth / windowHeight), 0.1f, 15.0f);

	fullTransformMatrix = projectionMatrix*camera.getWorldToViewMatrix() *translationMatrix*rotationMatrix;

	glUniformMatrix4fv(fullTranformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, arrowNumIndicies, GL_UNSIGNED_SHORT, (void*)arrowIndexBufferOffsetInBytes);

	// Plane
	glBindVertexArray(planeVertexArrayObjectID);

	rotationMatrix = glm::rotate(mat4(), 45.0f, vec3(1.0f, 0.0f, 0.0f));
	translationMatrix = glm::translate(mat4(), vec3(0.0f, 0.0f, -10.0f));
	projectionMatrix = glm::perspective(60.0f, ((float)windowWidth / windowHeight), 0.1f, 20.0f);
	fullTransformMatrix = projectionMatrix*camera.getWorldToViewMatrix() *translationMatrix*rotationMatrix;
	
	

	glUniformMatrix4fv(fullTranformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, planeNumIndices, GL_UNSIGNED_SHORT, (void*)planeIndexByteOffset);

	glutSwapBuffers();
}

void sendDataToOpenGL()
{
	
	ShapeData cube = ShapeGenerator::makeCube();
	ShapeData arrow = ShapeGenerator::makeArrow();
	ShapeData plane = ShapeGenerator::makePlane(20);

	glGenBuffers(1, &theBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferId);
	glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize()+cube.indexBufferSize()+ 
								arrow.vertexBufferSize()+arrow.indexBufferSize()+
								plane.vertexBufferSize() + plane.indexBufferSize()
								,0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, cube.vertexBufferSize(), cube.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.indexBufferSize(), cube.indices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + cube.indexBufferSize(), arrow.vertexBufferSize(), arrow.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + cube.indexBufferSize() + arrow.vertexBufferSize(), arrow.indexBufferSize(), arrow.indices);
	
	glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + cube.indexBufferSize() + 
		arrow.vertexBufferSize() + arrow.indexBufferSize(), plane.vertexBufferSize(), plane.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, cube.vertexBufferSize() + cube.indexBufferSize() +
		arrow.vertexBufferSize() + arrow.indexBufferSize() + plane.vertexBufferSize(),
		plane.indexBufferSize(), plane.indices);

	cubeNumIndicies = cube.numIndices;
	arrowNumIndicies = arrow.numIndices;
	planeNumIndices = plane.numIndices;

	glGenVertexArrays(1,&cubeVertexArrayObjectId);
	glGenVertexArrays(1,&arrowVertexArrayObjectId);
	glGenVertexArrays(1, &planeVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferId);

	glBindVertexArray(arrowVertexArrayObjectId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferId);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(cube.vertexBufferSize()+cube.indexBufferSize()));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(cube.vertexBufferSize() + cube.indexBufferSize() + sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferId);

	
	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferId);
	GLuint planeByteOffset = cube.vertexBufferSize() + cube.indexBufferSize() + arrow.vertexBufferSize() + arrow.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)planeByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (void*)(planeByteOffset + sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferId);
	
	cubeIndexBufferOffsetInBytes = cube.vertexBufferSize();
	arrowIndexBufferOffsetInBytes = cube.vertexBufferSize()+ cube.indexBufferSize()+arrow.vertexBufferSize();
	planeIndexByteOffset = cube.vertexBufferSize() + cube.indexBufferSize() + arrow.vertexBufferSize()+arrow.indexBufferSize() + plane.vertexBufferSize();
	
	cube.cleanup();
	arrow.cleanup();
	plane.cleanup();

}

void init()
{
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		exit(0);

	}
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
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
	glutMotionFunc(mouse);

	glutMainLoop();
	
	return 0;
}