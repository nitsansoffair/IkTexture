
#include "cubeLink.h"

cubeLink::cubeLink(cubeLink* father, int idx) {
	this->theta = 0;
	this->idx = idx;

	this->trans = glm::translate(mat4(1), vec3(0.0, 2.0 * K, 0.0));
	this->trans_op = glm::translate(mat4(1), vec3(0.0, 2.0 * K, 0.0));

	this->father = father;
	this->mat = this->rotX = this->rotY = mat4(1);
}

cubeLink::cubeLink(int idx, mat4 mat) {
	this->idx = idx;

	this->trans = glm::translate(mat, vec3(0.0, -K * 2.0, 0.0));
	this->trans_op = glm::inverse(trans);
	
	this->mat = mat;

	this->rotX = this->rotY = mat4(1);
}

cubeLink::cubeLink(cubeLink& other) {
	this->idx = other.idx;
	this->K = other.K;
	this->mat = other.mat;
	this->trans = other.trans;
	this->trans_op = other.trans_op;
	this->father = other.father;
	this->axis = other.axis;
}

cubeLink& cubeLink::operator=(const cubeLink& other) {
	this->idx = other.idx;
	this->K = other.K;
	this->mat = other.mat;
	this->trans = other.trans;
	this->trans_op = other.trans_op;
	this->father = other.father;
	this->axis = other.axis;

	return *this;
}


void cubeLink::upTheta(float theta, char axis){
	this->theta = theta;

	switch (axis) {
		case 'x': {
			this->rotX = glm::rotate(this->rotX, theta, vec3(1.0, 0.0, 0.0));
		} break;

		case 'y': {
			this->rotY = glm::rotate(this->rotY, theta, vec3(0.0, 1.0, 0.0));;
		} break;

		case 'z': {
			this->rot = glm::rotate(mat4(1), theta, vec3(0.0, 0.0, 1.0));;
		} break;
	}

	this->rot = this->rotY * this->rotX;
}

void cubeLink::upThetaSolver(vec3 vec, float thetaX){
	mat4 rotHelper;
	rotHelper = glm::rotate(mat4(1), thetaX, -vec);;
	this->rot = rotHelper * this->rot;
}


mat4 cubeLink::getMat() {
	if (idx == 0 || father == NULL) {
		return this->mat * this->trans * this->rot  * this->trans_op;
	}
	else {
		return father->getMat() * this->trans * this->rot * this->trans_op;
	}
}

void cubeLink::moveScene(vec3 direction, float theta) {
	mat4 rotHelper = glm::rotate(mat4(1), theta, direction);
	this->mat = rotHelper * this->mat;
}