#include "ShapeGenerator.h"
#include <glm\glm.hpp>
#include "Vertex.h"
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)
using glm::vec3;
ShapeData ShapeGenerator::makeTriangle()
{
	ShapeData ret;

	Vertex myTri[] =
	{
		glm::vec3(-1.0f, 0.0f, +0.0f),
		glm::vec3(+1.0f, 0.0f, 0.0f),

		glm::vec3(-1.0f, +1.0f, +0.0f),
		glm::vec3(+1.0f, 0.0f, 0.0f),

		glm::vec3(-0.9f, 0.0f, +0.0f),
		glm::vec3(+1.0f, 0.0f, 0.0f),
	};
	ret.numVertices = NUM_ARRAY_ELEMENTS(myTri);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, myTri, sizeof(myTri));

	GLushort indices[] = { 0, 1, 2 };
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}
ShapeData ShapeGenerator::makeCube() {
	ShapeData ret;

	Vertex stackVerts[] = {
		vec3(-1.0f, +1.0f, +1.0f), // 0
		vec3(+1.0f, +0.0f, +0.0f), // Color
		vec3(+1.0f, +1.0f, +1.0f), // 1
		vec3(+0.0f, +1.0f, +0.0f), // Color
		vec3(+1.0f, +1.0f, -1.0f), // 2
		vec3(+0.0f, +0.0f, +1.0f), // Color
		vec3(-1.0f, +1.0f, -1.0f), // 3
		vec3(+1.0f, +1.0f, +1.0f), // Color

		vec3(-1.0f, -1.0f, +1.0f), // 4
		vec3(+0.0f, +0.0f, +0.0f), // Color
		vec3(+1.0f, -1.0f, +1.0f), // 5
		vec3(+1.0f, +1.0f, +0.0f), // Color
		vec3(+1.0f, -1.0f, -1.0f), // 6
		vec3(+0.0f, +1.0f, +1.0f), // Color
		vec3(-1.0f, -1.0f, -1.0f), // 7
		vec3(+1.0f, +0.0f, +1.0f), // Color

		
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	unsigned short stackIndices[] = {
		0, 1, 2, 0, 2, 3, // Top
		0, 1, 4, 1, 4, 5, // Front
		1, 2, 5, 2, 5, 6, // Right
		0, 3, 4, 3, 4, 7, // Left
		3, 2, 7, 2, 7, 6, // Back
		4, 5, 7, 5, 7, 6, // Bottom
	};
	ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));

	return ret;
}