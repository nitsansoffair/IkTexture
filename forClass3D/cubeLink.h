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
	cubeLink* father = NULL;
	mat4 mat, trans, trans_op,
		rotX, rotY, rot,
		scaleMat = glm::scale(vec3(1.0f, 2.0f, 1.0f));
	
	char axis = NULL;
	float theta = NULL,
		K = 1.025f;
	int idx;

	cubeLink(cubeLink* father, int idx);
	cubeLink(int idx, mat4 mat);

	cubeLink& operator=(const cubeLink& other);
	cubeLink(cubeLink& other);
	~cubeLink() {};

	void upTheta(float theta, char axis);
	void upThetaSolver(vec3 vec, float thetaX);

	mat4 getMat();
	void moveScene(vec3 direction, float theta);

};

#endif 
