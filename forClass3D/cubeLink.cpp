#include "cubeLink.h"


cubeLink::cubeLink(cubeLink *father, int idx) {

	mat4 mulMat;
	mulMat = glm::translate(mat4(1), vec3(0, 2.02 * K, 0));

	theta = 0;
	this->idx = idx;
	trans = glm::translate(mat4(1), vec3(0, 2 * K, 0));
	trans_op = glm::translate(mat4(1), vec3(0, 2 * K, 0));

	this->father = father;
	mat = mat4(1);
	rotX = mat4(1);
	rotY = mat4(1);



}

cubeLink::cubeLink(int idx, mat4 mat) {

	this->father = NULL;
	this->mat = mat;
	trans = glm::translate(mat, vec3(0, -K * 2, 0));

	this->idx = idx;
	trans_op = glm::inverse(trans);


	rotX = mat4(1);
	rotY = mat4(1);


}



mat4 cubeLink::getMat()
{

	if (idx == 0 || father == NULL) {
		return mat * trans * rot  * trans_op;
	}
	else
		return father->getMat() * trans * rot* trans_op;
}


void cubeLink::upTheta(float theta, char axis)
{
	this->theta = theta;


	switch (axis) {

	case 'x': {
		rotX = glm::rotate(rotX, theta, vec3(1, 0, 0));
		//rotX = rot*rotX;
	}break;

	case 'y': {
		rotY = glm::rotate(rotY, theta, vec3(0, 1, 0));;
		//rotY = rot*rotY;
	}break;

	case 'z': {
		rot = glm::rotate(mat4(1), theta, vec3(0, 0, 1));;
	}break;

	}
	rot = rotY * rotX;

}


void cubeLink::upThetaSolver(vec3 V, float thetaX)
{


	mat4 rot1, rot2;

	rot1 = glm::rotate(mat4(1), thetaX, -V);;

	rot = rot1 * rot;

}


void cubeLink::moveScene(vec3 direction, float theta) {

	mat4 rot1 = glm::rotate(mat4(1), theta, direction);
	vec3 V = vec3(1 * K, 0.0f, 0.0f);
	mat4 trans = glm::translate(mat4(1), -V);
	mat4 transOp = glm::inverse(trans);
	mat = rot1 * mat;
}



float cubeLink::calcRootsAngle()
{

	if (idx == 0 || this->father == NULL) {
		return this->theta;

		return this->father->calcRootsAngle() + this->theta;

	}

}





cubeLink & cubeLink::operator=(const cubeLink & other)
{

	this->idx = other.idx;
	this->K = other.K;
	this->mat = other.mat;
	this->trans = other.trans;
	this->trans_op = other.trans_op;
	this->father = other.father;
	this->axis = other.axis;

	return *this;

}


cubeLink::cubeLink(cubeLink & other)
{
	this->idx = other.idx;
	this->K = other.K;
	this->mat = other.mat;
	this->trans = other.trans;
	this->trans_op = other.trans_op;
	this->father = other.father;
	this->axis = other.axis;

}




cubeLink::~cubeLink()
{
}
