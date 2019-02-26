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
	static float K;
	static mat4 scaleMat;

	cubeLink* father = NULL;
	mat4 mat, trans, transOp,
		rotX, rotY, rot;
	int idx;

	cubeLink(cubeLink* father, int idx);
	cubeLink(int idx, mat4 mat);

	cubeLink& operator=(const cubeLink& other);
	cubeLink(cubeLink& other);
	~cubeLink() {};

	void prepRotate(float theta, char axis);
	void prepRotateSolver(vec3 vec, float thetaX);

	mat4 getMat();
	void moveScene(vec3 direction, float theta);

};

#endif 
