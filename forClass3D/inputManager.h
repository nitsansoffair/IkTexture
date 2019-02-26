#pragma once
#ifndef inputManager_h_
#define inputManager_h_

#include "GLFW\glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "cubeLink.h"

using namespace glm;
using namespace std;


// Consts & Variables
static const int DISPLAY_WIDTH = 800, DISPLAY_HEIGHT = 800;

#define PI 3.14159265

const float K = 1.025f * 2.0f,
Far = 100.0f,
Near = 0.1f,
CAM_ANGLE = 60.0f,
relation = DISPLAY_HEIGHT / DISPLAY_WIDTH;

int n = -1,
pervN = -1,
backgroundPick = 0,
idxChain = 4,
numOfAction = 0;

float xPrev,
yPrev,
xLoc = 0,
yLoc = 0,
depth[4],
maxDist = 2 * K * (int)idxChain;

unsigned char Data[4];

bool rightClick = false,
firstTime = true,
solver = false,
space = false;

Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

Vertex vertices[] = {	
	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),  /* r & g wall */
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),

	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),  /* g & b wall */
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),  /* b wall */
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),

	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),  /* green wall */
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),  /* red wall */
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),  /* r & b wall */
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1))
};

unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3,		// 1st square

	6, 5, 4,
	7, 6, 4,

	10, 9, 8,
	11, 10, 8,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	22, 21, 20,		// 6rd square
	23, 22, 20
};

Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

Shader shader("./res/shaders/basicShader"),
colorPickShader("./res/shaders/colorPickShader");

GLint viewport[4];

cubeLink* cubes[10];

vec3 location = vec3(0, 0, 0),
saveLoc = location,
pos = vec3(0, 0, -35),
forwardVec = glm::vec3(0.0f, 0.0f, 1.0f),
up = glm::vec3(0.0f, 1.0f, 0.0f),
side = glm::vec3(1.0f, 0.0f, 0.0f);

mat4 matrices[10],
targetCube,
mulMat = glm::translate(mat4(1), vec3(4 * K, 0.0f, 0.0f)),
P1 = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f),
M = glm::mat4(1),
M1 = glm::translate(mat4(1), vec3(3, 0, 0)),
M2 = glm::translate(mat4(1), vec3(-3, 0, 0)),
P = P1 * glm::lookAt(pos, pos + forwardVec, up),
MVP = P * M;


// Axises
void buildGenAxises() {
	glLineWidth(2.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3f(-K * 6.0f, K * 0.0f, 0.0f);	// X axis, General
	glVertex3f(K * 6.0f, K * 0.0f, 0.0f);

	glVertex3f(K * 0.0f, K * 6.0f, 0.0f);  // Y axis, General
	glVertex3f(K * 0.0f, K * -6.0f, 0.0f);

	glEnd();
}

void buildAxises() {
	// Lines of Chain
	glLineWidth(1.5);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);

	glVertex3f(K * 0.0f, K * 1.0f, 0.0f);		// Y axis, High
	glVertex3f(K * 0.0f, K * 0.0f, 0.0f);

	glVertex3f(K * 0.0f, K * 0.5f, 0.0f);		// Y axis, High-2
	glVertex3f(K * 0.0f, K * -0.5f, 0.0f);

	glVertex3f(K * 0.0f, K * 0.0f, 0.0f);		// Y axis, low-2
	glVertex3f(K * 0.0f, K * -1.0f, 0.0f);

	glVertex3f(K * 0.0f, K * -0.5f, 0.0f);		// Y axis, low
	glVertex3f(K * 0.0f, K * -1.5f, 0.0f);

	glVertex3f(-K * 1.5f, K * 0.0f, 0.0f);		// X axis, low left
	glVertex3f(K * 1.5f, K * 0.0f, 0.0f);

	glEnd();
}


// Location
void setLocation(float xP, float yP) {
	xLoc = xP;
	yLoc = yP;
}

vec2 getLoction() {
	return vec2(xLoc, yLoc);
}


// Cubes
void initCubes() {
	cubes[0] = new cubeLink(0, mat4(1));
	matrices[0] = cubes[0]->mat;

	for (int i = 1; i < idxChain; i++) {
		cubes[i] = new cubeLink(cubes[i - 1], i);
		matrices[i] = cubes[i]->mat;
	}

	targetCube = (mat4(1) * mulMat);
	cubes[idxChain] = new cubeLink(4, targetCube);
	cubes[idxChain + 1] = new cubeLink(0, mat4(1));
}

void rotateTargetCube(vec3 rotateVec, float theta) {
	mat4 rot = glm::rotate(mat4(1), theta, rotateVec);
	vec3 V = vec3(1 * K, 0.0f, 0.0f);
	mat4 trans = glm::translate(mat4(1), -V);
	mat4 transOp = glm::inverse(trans);
	targetCube = trans * rot * transOp * targetCube;
}

void rotate(char direction, float theta) {
	setLocation(xPrev, yPrev);
	vec3 rotateDirc, translateDirc;
	char axis = 'x';
	int dirc = -1;
	if (direction == 'R' || direction == 'L') {
		rotateDirc = vec3(0, 1, 0);
		translateDirc = vec3(dirc, 0, 0);
		axis = 'y';
		if (direction == 'L') {
			theta = -theta;
			dirc = -dirc;
		}
	}
	else {
		rotateDirc = vec3(1, 0, 0);
		axis = 'x';
		if (direction == 'D') {
			theta = -theta;
			dirc = -dirc;
		}
	}
	if (n >= 0 && n < idxChain) {
		cubes[n]->upTheta(theta, axis);
	}
	else if (n == idxChain) {
		targetCube = glm::rotate(targetCube, theta, rotateDirc);
	}
	else if (n == idxChain + 1) {
		mat4 rot = glm::rotate(mat4(1), theta, rotateDirc);
		cubes[0]->moveScene(rotateDirc, theta);
		targetCube = rot * targetCube;
		cubes[idxChain + 1]->mat = rot * cubes[idxChain + 1]->mat;  // Rotate general axis
	}
}

void move(char direction, float theta, float xPos, float yPos, bool mouse) {
	vec2 location = getLoction();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels((GLint)xPos, (GLint)(DISPLAY_HEIGHT - yPos - 1.0f), (GLsizei)1.0f, (GLsizei)1.0f, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

	float z = Far + depth[0] * (Near - Far);
	float yRel = yPos - location[1];
	float xRel = xPos - location[0];
	float transX = 1.0f, transY = 1.0f;
	int dirc = -1;

	if (mouse) {
		transX = 1.0f * relation * xRel / (float)(DISPLAY_WIDTH)* Near * 2.0f * (float)tan(CAM_ANGLE * PI / 360.0f) * (Far / z);
		transY = 1.0f * yRel / (float)(DISPLAY_HEIGHT)* Near * 2.0f * tan(CAM_ANGLE * (float)PI / 360.0f) * (Far / z);
	}
	else if (direction == 'L' || direction == 'U') {
		dirc *= -1;
	}

	if (abs(transX) > 1.5) {
		transX /= 2;
	}
	if (abs(transY) > 1.5) {
		transY /= 2;
	}
	if (space) {
		solver = true;
	}
	vec3 translateDirc;

	if (direction == 'R' || direction == 'L') {
		translateDirc = vec3(dirc * transX, 0, 0);
		if (direction == 'L') {
			translateDirc = vec3(dirc * transX, 0, 0);
		}
	}
	else if (direction == 'D' || direction == 'U') {
		dirc *= -1;
		translateDirc = vec3(0, dirc * transY, 0);
		if (direction == 'D') {
			translateDirc = vec3(0, dirc * transY, 0);
		}
		translateDirc = -translateDirc;
	}
	else {
		translateDirc = vec3(0, 0, dirc);
		if (direction == 'F') {
			dirc *= -1;
			translateDirc = vec3(0, 0, dirc);
		}
	}

	mat4 trans = glm::translate(mat4(1), translateDirc);
	if (n >= 0 && n < idxChain) {
		if (direction == 'F' || direction == 'B') {
			cubes[0]->mat = trans * cubes[0]->mat;
		}
		else if (mouse) {
			if (abs(xPos - location[0]) > 0.1 || abs(yPos - location[1]) > 0.1) {
				cubes[0]->mat = trans * cubes[0]->mat;
				if (direction == 'D' || direction == 'U') {
					setLocation(location[0], yPos);
				}
				else {
					setLocation(xPos, location[1]);
				}
			}
		}
		else {
			setLocation(xPos, yPos);
			cubes[0]->mat = trans * cubes[0]->mat;
		}
	}
	else if (n == idxChain) {
		if (direction == 'F' || direction == 'B') {
			targetCube = trans * targetCube;
		}
		else if (mouse) {
			if (abs(xPos - location[0]) > 0.1 || abs(yPos - location[1]) > 0.1) {
				targetCube = trans * targetCube;
				if (direction == 'D' || direction == 'U') {
					setLocation(location[0], yPos);
				}
				else {
					setLocation(xPos, location[1]);
				}
			}
		}
		else {
			setLocation(xPos, yPos);
			targetCube = trans * targetCube;
		}
	}
}

float calcDist(int cubeIdx) {
	// Calculate distance between two cubes (Tip & Destination)
	mat4 tipCube = cubes[cubeIdx]->getMat();
	tipCube = glm::translate(tipCube, vec3(0.0, K, 0.0));
	// Takes 3rd row of 2 matrices, to Calc distance between 2 Points
	vec3 tipLoc = vec3(tipCube[3][0], tipCube[3][1], tipCube[3][2]);
	vec3 destLoc = vec3(targetCube[3][0], targetCube[3][1], targetCube[3][2]);
	float dist = sqrt(pow(tipLoc[0] - destLoc[0], 2) + pow(tipLoc[1] - destLoc[1], 2) + pow(tipLoc[2] - destLoc[2], 2));

	return dist;
}


// Pick
void pick() {
	Shader colorPickShader("./res/shaders/colorPickShader");
	GLint viewport[4];
	vec3 color;
	unsigned char data[4];
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < idxChain; i++) {
		color = vec3(1.0f / (i + 3), 0.0f, 0.0f);
		matrices[i] = cubes[i]->getMat() * cubes[0]->scaleMat;
		MVP = P * matrices[i];
		colorPickShader.Bind();
		colorPickShader.Update(MVP, matrices[i], color);
		mesh.Draw();
	}

	color = vec3(0.5f, 0.0f, 0.0f);
	MVP = P * targetCube;
	colorPickShader.Bind();
	colorPickShader.Update(MVP, targetCube, color);
	mesh.Draw();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels((GLint)xPrev, (GLint)(viewport[3] - yPrev), (GLsizei)1.0f, (GLsizei)1.0f, GL_RGBA, GL_UNSIGNED_BYTE, data);
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	int pickColor = data[0];

	if (pickColor == 255) {
		n = idxChain + 1;
		backgroundPick++;
	}
	else if (pickColor == 128) {
		n = idxChain;
		backgroundPick = 0;
		pervN = idxChain;
	}
	else {
		for (int i = 0; i < idxChain; i++) {
			float objColor = float(255.0) / float(i + 3.0);
			int rintt = (int)rint(objColor - 0.0000000001);
			if (pickColor == rintt) {
				n = i;
				pervN = i;
				backgroundPick = 0;
				break;
			}
		}
	}

	if ((n == idxChain + 1 && pervN != idxChain + 1 && pervN != -1) || backgroundPick >= 2) {
		n = idxChain + 2;
		pervN = idxChain + 1;
		backgroundPick = 0;
	}
}


// Solver
void IKsolver() {
	int currMat;
	// If Distance bigger than delta, and less than a "Very big number"
	// cubes[3] ::= <tipOfChain>, cubes[4] ::= <destCube>
	float currDistance = calcDist(0);
	float dist = calcDist(idxChain - 1);
	std::cout << "Distance: " << (dist) << std::endl;
	if (dist < 0.3 || currDistance + K >= maxDist) {
		solver = false;
		if (currDistance + K >= maxDist) {
			std::cout << "Cannot reach" << std::endl;
		} else {
			std::cout << "Distance: " << (dist) << std::endl;
		}
		numOfAction = 0;
	} else {
		currMat = idxChain - 1 - numOfAction;
		mat4 topChain = cubes[idxChain - 1]->getMat();
		topChain = glm::translate(topChain, vec3(0, K, 0));
		mat4 currChain = cubes[currMat]->getMat();
		currChain = glm::translate(currChain, vec3(0, -K, 0));
		vec3 v1 = normalize(vec3(topChain[3][0] - currChain[3][0], topChain[3][1] - currChain[3][1], topChain[3][2] - currChain[3][2]));
		vec3 v2 = normalize(vec3(targetCube[3][0] - currChain[3][0], targetCube[3][1] - currChain[3][1], targetCube[3][2] - currChain[3][2]));
		float cosA = glm::clamp(dot(v1, v2), -0.99f, 0.99f);
		float thetaX = acos(cosA);
		vec3 plane = cross(v1, v2);
		cubes[currMat]->upThetaSolver(plane, (-thetaX * 180.0f / (5.0f * (float)PI)));
	}
}


// Callbacks
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods){
	switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}

		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS) {
				solver = !solver;
				space = !space;
				numOfAction = 0;
			} break;

		case GLFW_KEY_RIGHT:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (rightClick) {
					move('R', 5.0, 0.0, 0.0, false);
				} else {
					rotate('R', 5.0);
				}
			firstTime = true;
			break;

		case GLFW_KEY_LEFT:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (rightClick) {
					move('L', 5.0, 0.0, 0.0, false);
				} else {
					rotate('L', 5.0);
				} break;

		case GLFW_KEY_UP:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (rightClick) {
					move('U', 5.0, 0.0, 0.0, false);
				} else {
					rotate('U', 5.0);
				} break;

		case GLFW_KEY_DOWN:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (rightClick) {
					move('D', 5.0, 0.0, 0.0, false);
				} else {
					rotate('D', 5.0);
				} break;

		case GLFW_MOUSE_BUTTON_LEFT:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		default: 
			break;
		}
}

void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
	xPrev = (float)xPos;
	yPrev = (float)yPos;

	if (firstTime) {
		setLocation((float)xPos, (float)yPos);
		firstTime = false;
	}

	vec2 location = getLoction();
	if (xPos > location[0]) {
		if (rightClick) {
			move('R', 1.0, (float)xPos, (float)yPos, true);
		} else {
			rotate('R', 1.0);
		}
	} else if (xPos < location[0]) {
		if (rightClick) {
			move('L', 1.0, (float)xPos, (float)yPos, true);
		}
		else {
			rotate('L', 1.0);
		}
	}

	if (yPos > location[1]) {
		if (rightClick) {
			move('D', 1.0, (float)xPos, (float)yPos, true);
		}
		else {
			rotate('D', 1.0);
		}
	} else if (yPos < location[1]) {
		if (rightClick) {
			move('U', 1.0, (float)xPos, (float)yPos, true);
		}
		else {
			rotate('U', 1.0);
		}
	}
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		rightClick = false;
		pick();
	} else if ((button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)) {
		rightClick = true;
		pick();
	}
}

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
	if (yOffset == 1) {
		move('F', 1.0, 0, 0, false);
	} else {
		move('B', 1.0, 0, 0, false);
	}
};

#endif



