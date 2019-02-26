
#include "cubeLink.h"

cubeLink::cubeLink(cubeLink* father, int idx) {
	this->theta = 0;
	this->idx = idx;

	this->trans = glm::translate(mat4(1), vec3(0.0f, 2.0f * K, 0.0f));
	this->trans_op = glm::translate(mat4(1), vec3(0.0f, 2.0f * K, 0.0f));

	this->father = father;
	this->mat = this->rotX = this->rotY = mat4(1);
}

cubeLink::cubeLink(int idx, mat4 mat) {
	this->theta = 0;
	this->idx = idx;

	this->trans = glm::translate(mat, vec3(0.0f, -K * 2.0f, 0.0f));
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
			this->rotX = glm::rotate(this->rotX, theta, vec3(1.0f, 0.0f, 0.0f));
		} break;

		case 'y': {
			this->rotY = glm::rotate(this->rotY, theta, vec3(0.0f, 1.0f, 0.0f));
		} break;

		case 'z': {
			this->rot = glm::rotate(mat4(1), theta, vec3(0.0f, 0.0f, 1.0f));
		} break;
	}

	this->rot = this->rotY * this->rotX;
}

void cubeLink::upThetaSolver(vec3 vec, float thetaX){
	this->rot = glm::rotate(mat4(1), thetaX, -vec) * this->rot;
}


mat4 cubeLink::getMat() {
	if (!idx || !father) {
		return this->mat * this->trans * this->rot * this->trans_op;
	}
	return father->getMat() * this->trans * this->rot * this->trans_op;
}

void cubeLink::moveScene(vec3 direction, float theta) {
	this->mat = glm::rotate(mat4(1), theta, direction) * this->mat;
}