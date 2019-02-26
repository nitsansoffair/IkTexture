#ifndef cubeLink_h_
#define cubeLink_h_

#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;
using namespace std;


class cubeLink {

public:
	// static fields
	static float K;
	static mat4 scaleMat;

	// fields
	cubeLink* father = NULL;
	mat4 mat, trans, transOp,
		rotX, rotY, rot;
	int idx;

	// Constructors
	cubeLink(cubeLink* father, int idx);
	cubeLink(int idx, mat4 mat);

	// Operators
	cubeLink& operator=(const cubeLink& other);
	cubeLink(cubeLink& other);
	~cubeLink() {};

	// Get matrix
	mat4 getMat();

	// Rotates
	void prepRotate(float theta, char axis);
	void prepRotateSolver(vec3 vec, float thetaX);

	// Move scene
	void moveScene(vec3 direction, float theta);

};

#endif 
