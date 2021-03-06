
#include "cubeLink.h"

// Constructors & Opeartors
cubeLink::cubeLink(cubeLink* father, int idx) {
	this->idx = idx;
	this->father = father;

	this->trans = glm::translate(mat4(1), vec3(0.0f, 2.0f * cubeLink::K, 0.0f));
	this->transOp = glm::translate(mat4(1), vec3(0.0f, 2.0f * cubeLink::K, 0.0f));
	this->mat = this->rotX = this->rotY = mat4(1);
}

cubeLink::cubeLink(int idx, mat4 mat) {
	this->idx = idx;

	this->trans = glm::translate(mat, vec3(0.0f, (-1) * cubeLink::K * 2.0f, 0.0f));
	this->transOp = glm::inverse(trans);
	this->mat = mat;
	this->rotX = this->rotY = mat4(1);
}

cubeLink::cubeLink(cubeLink& other) {
	this->idx = other.idx;
	this->father = other.father;
	this->mat = other.mat;
	this->trans = other.trans;
	this->transOp = other.transOp;
}

cubeLink& cubeLink::operator=(const cubeLink& other) {
	this->idx = other.idx;
	this->father = other.father;
	this->mat = other.mat;
	this->trans = other.trans;
	this->transOp = other.transOp;

	return *this;
}


// Get matrix
mat4 cubeLink::getMat() {
	if (!idx || !father) {
		return this->mat * this->trans * this->rot * this->transOp;
	}
	return father->getMat() * this->trans * this->rot * this->transOp;
}


// Move scene
void cubeLink::moveScene(vec3 direction, float theta) {
	this->mat = glm::rotate(mat4(1), theta, direction) * this->mat;
}


// Rotates
void cubeLink::prepRotate(float theta, char axis){
	switch (axis) {
		case 'x': {
			this->rotX = glm::rotate(this->rotX, theta, vec3(1.0f, 0.0f, 0.0f));
		} break;

		case 'y': {
			this->rotY = glm::rotate(this->rotY, theta, vec3(0.0f, 1.0f, 0.0f));
		} break;
	}

	this->rot = this->rotY * this->rotX;
}

void cubeLink::prepRotateSolver(vec3 vec, float thetaX){
	this->rot = glm::rotate(mat4(1), thetaX, -vec) * this->rot;
}

