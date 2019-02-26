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

	cubeLink *father = NULL;
	mat4 mat;
	mat4 trans;
	mat4 trans_op;
	mat4 rotX;
	mat4 rotY;
	mat4 rot;
	mat4 scaleMat = glm::scale(vec3(1.0f, 2.0f, 1.0f));
	char axis;
	float theta;
	float K = 1.025;
	int idx;
	void upTheta(float theta, char axis);
	mat4 getMat();
	void moveScene(vec3 direction, float theta);
	void upThetaSolver(vec3 V, float thetaX);
	cubeLink(cubeLink * father, int idx);
	cubeLink(int idx, mat4 mat);
	cubeLink& operator=(const cubeLink& other);
	cubeLink(cubeLink& other);
	float calcRootsAngle();
	~cubeLink();


};

#endif 
