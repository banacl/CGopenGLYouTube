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
ShapeData ShapeGenerator::makeArrow()
{
	ShapeData ret;
	Vertex stackVerts[] =
	{
		// Top side of arrow head
		vec3(+0.00f, +0.25f, -0.25f),         // 0
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.50f, +0.25f, -0.25f),         // 1
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.00f, +0.25f, -1.00f),         // 2
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(-0.50f, +0.25f, -0.25f),         // 3
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		// Bottom side of arrow head
		vec3(+0.00f, -0.25f, -0.25f),         // 4
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.50f, -0.25f, -0.25f),         // 5
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.00f, -0.25f, -1.00f),         // 6
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(-0.50f, -0.25f, -0.25f),         // 7
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		// Right side of arrow tip
		vec3(+0.50f, +0.25f, -0.25f),         // 8
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.00f, +0.25f, -1.00f),         // 9
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.00f, -0.25f, -1.00f),         // 10
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.50f, -0.25f, -0.25f),         // 11
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		// Left side of arrow tip
		vec3(+0.00f, +0.25f, -1.00f),         // 12
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.50f, +0.25f, -0.25f),         // 13
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(+0.00f, -0.25f, -1.00f),         // 14
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.50f, -0.25f, -0.25f),         // 15
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		// Back side of arrow tip
		vec3(-0.50f, +0.25f, -0.25f),         // 16
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.50f, +0.25f, -0.25f),         // 17
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(-0.50f, -0.25f, -0.25f),         // 18
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.50f, -0.25f, -0.25f),         // 19
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		// Top side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 20
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(+0.25f, +0.25f, +1.00f),         // 21
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(-0.25f, +0.25f, +1.00f),         // 22
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		vec3(-0.25f, +0.25f, -0.25f),         // 23
		vec3(+1.00f, +0.00f, +0.00f),		  // Color
		// Bottom side of back of arrow
		vec3(+0.25f, -0.25f, -0.25f),         // 24
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(+0.25f, -0.25f, +1.00f),         // 25
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(-0.25f, -0.25f, +1.00f),         // 26
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		vec3(-0.25f, -0.25f, -0.25f),         // 27
		vec3(+0.00f, +0.00f, +1.00f),		  // Color
		// Right side of back of arrow
		vec3(+0.25f, +0.25f, -0.25f),         // 28
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.25f, -0.25f, -0.25f),         // 29
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.25f, -0.25f, +1.00f),         // 30
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		vec3(+0.25f, +0.25f, +1.00f),         // 31
		vec3(+0.60f, +1.00f, +0.00f),		  // Color
		// Left side of back of arrow
		vec3(-0.25f, +0.25f, -0.25f),         // 32
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.25f, -0.25f, -0.25f),         // 33
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.25f, -0.25f, +1.00f),         // 34
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		vec3(-0.25f, +0.25f, +1.00f),         // 35
		vec3(+0.00f, +1.00f, +0.00f),		  // Color
		// Back side of back of arrow
		vec3(-0.25f, +0.25f, +1.00f),         // 36
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.25f, +0.25f, +1.00f),         // 37
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(-0.25f, -0.25f, +1.00f),         // 38
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
		vec3(+0.25f, -0.25f, +1.00f),         // 39
		vec3(+0.50f, +0.50f, +0.50f),		  // Color
	};

	GLushort stackIndices[] = {
		0, 1, 2, // Top
		0, 2, 3,
		4, 6, 5, // Bottom
		4, 7, 6,
		8, 10, 9, // Right side of arrow tip
		8, 11, 10,
		12, 15, 13, // Left side of arrow tip
		12, 14, 15,
		16, 19, 17, // Back side of arrow tip
		16, 18, 19,
		20, 22, 21, // Top side of back of arrow
		20, 23, 22,
		24, 25, 26, // Bottom side of back of arrow
		24, 26, 27,
		28, 30, 29, // Right side of back of arrow
		28, 31, 30,
		32, 33, 34, // Left side of back of arrow
		32, 34, 35,
		36, 39, 37, // Back side of back of arrow
		36, 38, 39,
	};

	ret.numVertices = sizeof(stackVerts) / sizeof(*stackVerts);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

	ret.numIndices = sizeof(stackIndices) / sizeof(*stackIndices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, stackIndices, sizeof(stackIndices));
	return ret;
}
