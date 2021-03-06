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

// Camera
const float K = 2.05f,
	Far = 100.0f,
	Near = 0.1f,
	CAM_ANGLE = 60.0f,
	relation = DISPLAY_HEIGHT / DISPLAY_WIDTH;

const int chainLength = 4;

// Solver
int chosenObjIdx = -1,
	prevChosenObjIdx = -1,
	backgroundPick = 0,
	idxCurrCubeSolver = 0;

// Mouse
float xPrev,
	yPrev,
	xLoc = 0,
	yLoc = 0,
	depth[4],
	maxDist = 2.0f * K * (int)chainLength - K * 1.2f,
	cubeLink::K = 1.025f;

// Mouse
bool mouseRightClick = false,
	firstTimeKeyRight = true,
	isSolverShouldRun = false,
	isSpacePressed = false;

Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

Vertex vertices[] = {	
	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),  /* Red & Green Wall */
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),

	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),  /* Green & Blue Wall */
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),  /* Blue Wall */
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 0, 1)),

	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),  /* Green Wall */
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),  /* Red Wall */
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),  /* Red & Blue Wall */
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1))
};

unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3,		// 1st Square

	6, 5, 4,
	7, 6, 4,

	10, 9, 8,
	11, 10, 8,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	22, 21, 20,		// 6rd Square
	23, 22, 20
};

Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

// Shaders
Shader shader("./res/shaders/basicShader"),
colorPickShader("./res/shaders/colorPickShader");

GLint viewport[4];

// Cubes
cubeLink* cubes[10];

// Vecs
vec3 location = vec3(0.0f, 0.0f, 0.0f),
	pos = vec3(0.0f, 0.0f, -35.0f),
	forwardVec = glm::vec3(0.0f, 0.0f, 1.0f),
	up = glm::vec3(0.0f, 1.0f, 0.0f);

// Matrices
mat4 matrices[10],
	targetCube,
	mulMatTarget = glm::translate(mat4(1), vec3(4 * K, 0.0f, 0.0f)),
	P1 = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f),
	M = glm::mat4(1),
	P = P1 * glm::lookAt(pos, pos + forwardVec, up),
	MVP = P * M,
	cubeLink::scaleMat = glm::scale(vec3(1.0f, 2.0f, 1.0f));


// Axises
void buildGenAxises() {
	glLineWidth(2.0f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_LINES);

	glVertex3f(-K * 6.0f, K * 0.0f, 0.0f);	// X axis, General
	glVertex3f(K * 6.0f, K * 0.0f, 0.0f);

	glVertex3f(K * 0.0f, K * 6.0f, 0.0f);  // Y axis, General
	glVertex3f(K * 0.0f, K * -6.0f, 0.0f);

	glEnd();
}

void buildAxises() {
	glLineWidth(1.5);
	glColor3f(0.5f, 0.5f, 0.5f);
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

	for (int i = 1; i < chainLength; i++) {
		cubes[i] = new cubeLink(cubes[i - 1], i);
		matrices[i] = cubes[i]->mat;
	}

	targetCube = (mat4(1) * mulMatTarget);
	cubes[chainLength] = new cubeLink(4, targetCube);
	cubes[chainLength + 1] = new cubeLink(0, mat4(1));
}

void rotateChosenObj(char direction, float theta) {
	setLocation(xPrev, yPrev);
	vec3 rotVec, transVec;
	
	char axis = 'x';
	int dir = -1;

	if (direction == 'R' || direction == 'L') {
		rotVec = vec3(0.0f, 1.0f, 0.0f);
		transVec = vec3(dir, 0.0f, 0.0f);
		axis = 'y';
		if (direction == 'L') {
			theta *= -1;
			dir *= -1;
		}
	} else {
		rotVec = vec3(1.0f, 0.0f, 0.0f);
		if (direction == 'D') {
			theta *= -1;
			dir *= -1;
		}
	}

	if (chosenObjIdx >= 0 && chosenObjIdx < chainLength) {
		// ChainCubes
		cubes[chosenObjIdx]->prepRotate(theta, axis);
	} else if (chosenObjIdx == chainLength) {
		// targetCube
		targetCube = glm::rotate(targetCube, theta, rotVec);
	} else if (chosenObjIdx == chainLength + 1) {
		// Scene
		mat4 rot = glm::rotate(mat4(1), theta, rotVec);
		cubes[0]->moveScene(rotVec, theta);
		targetCube = rot * targetCube;
		cubes[chainLength + 1]->mat = rot * cubes[chainLength + 1]->mat;  // Rotate general axis
	}
}

void moveChosenObj(char direction, float newXpos, float newYpos, bool mouse) {
	vec2 currLoc = getLoction();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels((GLint)newXpos, (GLint)(DISPLAY_HEIGHT - newYpos - 1.0f), (GLsizei)1.0f, (GLsizei)1.0f, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

	float z = Far + depth[0] * (Near - Far), 
		yRel = newYpos - currLoc[1],
		xRel = newXpos - currLoc[0],
		transX = 1.0f,
		transY = 1.0f;

	int dir = -1;

	if (mouse) {
		transX = 1.0f * relation * xRel / (float)(DISPLAY_WIDTH) * Near * 2.0f * (float)tan(CAM_ANGLE * PI / 360.0f) * (Far / z);
		transY = 1.0f * yRel / (float)(DISPLAY_HEIGHT) * Near * 2.0f * tan(CAM_ANGLE * (float)PI / 360.0f) * (Far / z);
	} else if (direction == 'L' || direction == 'U') {
		dir *= -1;
	}

	if (abs(transX) > 1.5) {
		transX /= 2;
	}
	if (abs(transY) > 1.5) {
		transY /= 2;
	}
	if (isSpacePressed) {
		isSolverShouldRun = true;
	}

	vec3 transVec;

	if (direction == 'R' || direction == 'L') {
		transVec = vec3(dir * transX, 0.0f, 0.0f);
	} else if (direction == 'D' || direction == 'U') {
		dir *= -1;
		transVec = vec3(0.0f, dir * transY, 0.0f) * (-1.0f);
	} else {
		if (direction == 'F') {
			dir *= -1;
		}
		transVec = vec3(0.0f, 0.0f, dir);
	}

	mat4 trans = glm::translate(mat4(1), transVec);
	if (chosenObjIdx >= 0 && chosenObjIdx < chainLength) {
		if (direction == 'F' || direction == 'B') {
			cubes[0]->mat = trans * cubes[0]->mat;
		} else if (mouse) {
			if (abs(newXpos - currLoc[0]) > 0.1 || abs(newYpos - currLoc[1]) > 0.1) {
				// chainOfCubes
				cubes[0]->mat = trans * cubes[0]->mat;
				if (direction == 'D' || direction == 'U') {
					setLocation(currLoc[0], newYpos);
				} else {
					setLocation(newXpos, currLoc[1]);
				}
			}
		} else {
			// chainOfCubes
			setLocation(newXpos, newYpos);
			cubes[0]->mat = trans * cubes[0]->mat;
		}
	} else if (chosenObjIdx == chainLength) {
		if (direction == 'F' || direction == 'B') {
			targetCube = trans * targetCube;
		} else if (mouse) {
			if (abs(newXpos - currLoc[0]) > 0.1 || abs(newYpos - currLoc[1]) > 0.1) {
				// targetCube
				targetCube = trans * targetCube;
				if (direction == 'D' || direction == 'U') {
					setLocation(currLoc[0], newYpos);
				} else {
					setLocation(newXpos, currLoc[1]);
				}
			}
		} else {
			// targetCube
			setLocation(newXpos, newYpos);
			targetCube = trans * targetCube;
		}
	}
}

float calcDistTipFrom(int cubeIdx) {
	// Calculate distance between two cubes (# <cubeIdx> CubeOfChain, Destination)
	mat4 tipCubeMat = cubes[cubeIdx]->getMat();
	mat4 tipCube = glm::translate(tipCubeMat, vec3(0.0f, K, 0.0f));
	
	// 3rd rate of Matrices => Calc distance 2 Points
	vec3 tipLoc = vec3(tipCube[3][0], tipCube[3][1], tipCube[3][2]);
	vec3 destLoc = vec3(targetCube[3][0], targetCube[3][1], targetCube[3][2]);

	return sqrt(pow(tipLoc[0] - destLoc[0], 2) + pow(tipLoc[1] - destLoc[1], 2) + pow(tipLoc[2] - destLoc[2], 2));
}


// Pick
void pick() {
	vec3 color;
	unsigned char data[4];
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < chainLength; i++) {
		color = vec3(1.0f / (i + 3), 0.0f, 0.0f);
		matrices[i] = cubes[i]->getMat() * cubeLink::scaleMat;
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
	int pickColor = data[0];

	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);

	if (pickColor == 255) {
		chosenObjIdx = chainLength + 1;
		backgroundPick++;
	} else if (pickColor == 128) {
		chosenObjIdx = prevChosenObjIdx = chainLength;
		backgroundPick = 0;
	} else {
		for (int i = 0; i < chainLength; i++) {
			float objColor = float(255.0) / float(i + 3.0);
			int roundedObjColor = (int)rint(objColor - 0.0000000001);
			if (pickColor == roundedObjColor) {
				chosenObjIdx = prevChosenObjIdx = i;
				backgroundPick = 0;
				break;
			}
		}
	}

	if ((chosenObjIdx == chainLength + 1 && prevChosenObjIdx != chainLength + 1 && prevChosenObjIdx != -1) || backgroundPick >= 2) {
		chosenObjIdx = chainLength + 2;
		prevChosenObjIdx = chainLength + 1;
		backgroundPick = 0;
	}
}


// Solver
void IKsolver() {
	// cubes[3] ::= <tipOfChain>, cubes[4] ::= <destCube>
	float distFromTail = calcDistTipFrom(0);
	float distFromTip = calcDistTipFrom(chainLength - 1);
	std::cout << "Distance: " << (distFromTip) << std::endl;
	if (distFromTip < 0.3 || distFromTail >= maxDist) {
		isSolverShouldRun = false;
		if (distFromTail >= maxDist) {
			std::cout << "Cannot reach" << std::endl;
		} else {
			std::cout << "Distance: " << (distFromTip) << std::endl;
		}
		idxCurrCubeSolver = 0;
	} else {
		int currMatIdx = chainLength - idxCurrCubeSolver - 1;
		mat4 topChainMat = cubes[chainLength - 1]->getMat();
		mat4 topChain = glm::translate(topChainMat, vec3(0.0f, K, 0.0f));

		mat4 currChainMat = cubes[currMatIdx]->getMat();
		mat4 currChain = glm::translate(currChainMat, vec3(0.0f, -K, 0.0f));

		vec3 v1 = normalize(vec3(topChain[3][0] - currChain[3][0], topChain[3][1] - currChain[3][1], topChain[3][2] - currChain[3][2]));
		vec3 v2 = normalize(vec3(targetCube[3][0] - currChain[3][0], targetCube[3][1] - currChain[3][1], targetCube[3][2] - currChain[3][2]));

		float cosA = glm::clamp(dot(v1, v2), -0.99f, 0.99f);
		float thetaX = acos(cosA);
		vec3 plane = cross(v1, v2);
		cubes[currMatIdx]->prepRotateSolver(plane, (-thetaX * 180.0f / (5.0f * (float)PI)));
	}
}


// Callbacks
void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods){
	switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
			break;

		case GLFW_KEY_SPACE:
			if (action == GLFW_PRESS) {
				isSolverShouldRun = !isSolverShouldRun;
				isSpacePressed = !isSpacePressed;
				idxCurrCubeSolver = 0;
			} 
			break;

		case GLFW_KEY_RIGHT:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (mouseRightClick) {
					moveChosenObj('R', 0.0f, 0.0f, false);
				} else {
					rotateChosenObj('R', 5.0f);
				}
			firstTimeKeyRight = true;
			break;

		case GLFW_KEY_LEFT:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (mouseRightClick) {
					moveChosenObj('L', 0.0f, 0.0f, false);
				} else {
					rotateChosenObj('L', 5.0f);
				} 
			break;

		case GLFW_KEY_UP:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (mouseRightClick) {
					moveChosenObj('U', 0.0f, 0.0f, false);
				} else {
					rotateChosenObj('U', 5.0f);
				} 
			break;

		case GLFW_KEY_DOWN:
			if (action == GLFW_REPEAT || action == GLFW_PRESS)
				if (mouseRightClick) {
					moveChosenObj('D', 0.0f, 0.0f, false);
				} else {
					rotateChosenObj('D', 5.0f);
				} 
			break;

		case GLFW_MOUSE_BUTTON_LEFT:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;

		default: 
			break;
		}
}

void cursorPositionCallback(GLFWwindow* window, double newXpos, double newYpos) {
	xPrev = (float)newXpos;
	yPrev = (float)newYpos;

	if (firstTimeKeyRight) {
		setLocation((float)newXpos, (float)newYpos);
		firstTimeKeyRight = false;
	}

	vec2 currLoc = getLoction();
	if (newXpos > currLoc[0]) {
		if (mouseRightClick) {
			moveChosenObj('R', (float)newXpos, (float)newYpos, true);
		} else {
			rotateChosenObj('R', 1.0f);
		}
	} else if (newXpos < currLoc[0]) {
		if (mouseRightClick) {
			moveChosenObj('L', (float)newXpos, (float)newYpos, true);
		} else {
			rotateChosenObj('L', 1.0f);
		}
	}

	if (newYpos > currLoc[1]) {
		if (mouseRightClick) {
			moveChosenObj('D', (float)newXpos, (float)newYpos, true);
		} else {
			rotateChosenObj('D', 1.0f);
		}
	} else if (newYpos < currLoc[1]) {
		if (mouseRightClick) {
			moveChosenObj('U', (float)newXpos, (float)newYpos, true);
		} else {
			rotateChosenObj('U', 1.0f);
		}
	}
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			mouseRightClick = false;
			pick();
		} else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
			mouseRightClick = true;
			pick();
		}
	}
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	if (yOffset == 1) {
		moveChosenObj('F', 0.0f, 0.0f, false);
	} else {
		moveChosenObj('B', 0.0f, 0.0f, false);
	}
};

#endif