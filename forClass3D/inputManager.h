#pragma once   //maybe should be static class
#ifndef inputManager_h_
#define inputManager_h_

/*#include <sddl.h>
#include <SDL\SDL_stdinc.h>
#include <SDL\SDL_opengl.h>
#include <SDL\SDL_system.h>*/


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

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

float relation = DISPLAY_HEIGHT / DISPLAY_WIDTH;

using namespace glm;
using namespace std;
#define PI 3.14159265



GLint viewport[4];
unsigned char Data[4];
float depth[4];

int blockChainNum = 4;
vec3 location = vec3(0, 0, 0);
vec3 saveLoc = location;
int n = -1, pervN = -1, backRoundPick = 0;
int k = 0;
mat4 Matrixes[10];
mat4 targetCube;
mat4 scene = mat4(1);
cubeLink* cubes[10];
float K = 1.025 * 2;
float mulAng = 23.15;
mat4 mulMat = glm::translate(mat4(1), vec3(4 * K, 0.0f, 0.0f));
float x = 0, y = 0;
float xp, yp;
int LastObj = -1;
bool rightClick = false;
bool firstTime = true;


float delta = 1;
float Far = 100.0f;
float Near = 0.1f;
float CAM_ANGLE = 60.0f;
float deltaMouse = 3;

int numOfAction = 0;
bool solver = false, space = false;
float maxDist = 2 * K*(blockChainNum);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

Vertex vertices[] =
{								// texture coordinates (vec2)
	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),  /*r r&g = y wall */
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(1, 1, 0)),

	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),  /* g&b wall */
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

	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),  /* r&b wall */
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
Shader shader("./res/shaders/basicShader");
Shader shader1("./res/shaders/colPicShader");


vec3 pos = vec3(0, 0, -35);
vec3 forwardd = glm::vec3(0.0f, 0.0f, 1.0f);
vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
vec3 side = glm::vec3(1.0f, 0.0f, 0.0f);
mat4 P1 = glm::perspective(60.0f, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 0.1f, 100.0f);

mat4 M = glm::mat4(1);
mat4 M1 = glm::translate(mat4(1), vec3(3, 0, 0));
mat4 M2 = glm::translate(mat4(1), vec3(-3, 0, 0));
mat4 P = P1 * glm::lookAt(pos, pos + forwardd, up);
mat4 MVP = P * M;

/*
const char* vertexShaderSource =
"#version 330 core"
"layout (location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = aTexCoord;\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D outTexture;\n"
"void main()\n"
"{\n"
//"	FragColor = texture(outTexture, TexCoord);\n"
"	FragColor = texture(outTexture, TexCoord) * vec4(ourColor, 1.0);\n"
"}\n\0";

float pixels[] = {
	0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
};

*/

/*
void LoadTex() {
	GLfloat *uvs;
	int width, height, nrChannels;
	unsigned char* data = stbi_load("..\res\textures\box0.bmp", &width, &height, &nrChannels, 0);
	unsigned int texture;
//	glGenTexture(1, &texture);
//	glBindTextures(GL_TEXTURE_2D, texture);
//	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);

	/*unsigned char* image =
		SOIL_load_image("img.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);*/

		//	GLunit tex;

		//}


void buildGenAxises() {

	glLineWidth(2);
	glColor3f(2, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex3f(-K * 6, K * 0, 0.0);	// x axis general
	glVertex3f(K * 6, K * 0, 0);

	glVertex3f(K * 0, K * 6, 0.0);		// y axis general
	glVertex3f(K * 0, K * -6, 0);


	glEnd();

}


void buildAxises() {

	// lines
	glLineWidth(1.5);
	glColor3f(2, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex3f(K * 0, K * 1, 0.0);		// y axis of high in chain
	glVertex3f(K * 0, K * 0, 0);

	glVertex3f(K * 0, K * 0.5, 0.0);		// y axis of high-2 in chain
	glVertex3f(K * 0, K * -0.5, 0);

	glVertex3f(K * 0, K * 0, 0.0);		// y axis of low-2 in chain
	glVertex3f(K * 0, K * -1, 0);

	glVertex3f(K * 0, K * -0.5, 0.0);		// y axis of low in chain
	glVertex3f(K * 0, K * -1.5, 0);



	glVertex3f(-K * 1.5, K * 0, 0.0);	// x axis of low left (high right, in chain)
	glVertex3f(K * 1.5, K * 0, 0);


	glEnd();

}


void initCubes() {
	cubes[0] = new cubeLink(0, mat4(1));
	Matrixes[0] = cubes[0]->mat;

	for (int i = 1; i < blockChainNum; i++) {
		cubes[i] = new cubeLink(cubes[i - 1], i);
		Matrixes[i] = cubes[i]->mat;
	}
	targetCube = (mat4(1) * mulMat);
	cubes[blockChainNum] = new cubeLink(4, targetCube);

	cubes[blockChainNum + 1] = new cubeLink(0, mat4(1));
}


void rotateTargetCube(vec3 rotateVec, float theta) {

	mat4 rot = glm::rotate(mat4(1), theta, rotateVec);
	vec3 V = vec3(1 * K, 0.0f, 0.0f);
	mat4 trans = glm::translate(mat4(1), -V);
	mat4 transOp = glm::inverse(trans);
	targetCube = trans * rot*transOp*targetCube;


}




// calculate the distance between two cubes, the tip and the destination
float calcDist(int cube) {
	mat4 tipCube = cubes[cube]->getMat();
	tipCube = glm::translate(tipCube, vec3(0, K, 0.0));
	// 'takes' 2 matrices, and from them the 3'rd row to calc distance between 2 points
	vec3 tipLoc = vec3(tipCube[3][0], tipCube[3][1], tipCube[3][2]);
	vec3 destLoc = vec3(targetCube[3][0], targetCube[3][1], targetCube[3][2]);


	float dist = sqrt(pow(tipLoc[0] - destLoc[0], 2) + pow(tipLoc[1] - destLoc[1], 2) + pow(tipLoc[2] - destLoc[2], 2));
	return dist;


}


void follow(float tx, float ty) {


}


void IKsolver() {
	int currMat;
	// if the distance is more than delta and less than a very 'big' number
	// cubes[3] = tip of chan, cubes[4] = destination cube
	float currDistance = calcDist(0);
	float dis = calcDist(blockChainNum - 1);
	std::cout << "distance is: " << (dis) << std::endl;
	if (dis < 0.3 || currDistance + K >= maxDist) {
		std::cout << "distance is: " << (dis) << std::endl;
		solver = false;
		if (currDistance + K >= maxDist) {
			std::cout << "cannot reach" << std::endl;
		}
		else
			std::cout << "distance is: " << (dis) << std::endl;
		numOfAction = 0;
	}


	else {
		currMat = blockChainNum - 1 - numOfAction;
		mat4 topChaine = cubes[blockChainNum - 1]->getMat();
		topChaine = glm::translate(topChaine, vec3(0, K, 0));
		mat4 CurrChaine = cubes[currMat]->getMat();
		CurrChaine = glm::translate(CurrChaine, vec3(0, -K, 0));
		vec3 v1 = normalize(vec3(topChaine[3][0] - CurrChaine[3][0], topChaine[3][1] - CurrChaine[3][1], topChaine[3][2] - CurrChaine[3][2]));
		vec3 v2 = normalize(vec3(targetCube[3][0] - CurrChaine[3][0], targetCube[3][1] - CurrChaine[3][1], targetCube[3][2] - CurrChaine[3][2]));
		float cosa = glm::clamp(dot(v1, v2), -0.99f, 0.99f);
		float thetaX = acos(cosa);
		vec3 plane = cross(v1, v2);
		cubes[currMat]->upThetaSolver(plane, (-thetaX * 180 / (5 * PI)));


	}

}



float calcDistCamObj(int objIdx) {

	vec3 objLoc = vec3(cubes[objIdx]->getMat()[3]);
	//vec3 pos is camLoc
	float dist = sqrt(pow(objLoc.x - pos.x, 2) + pow(objLoc.y - pos.y, 2) + pow(objLoc.z - pos.z, 2));
	return dist;

}


void setPosition(float xP, float yP) {
	x = xP;
	y = yP;
}
vec2 getLoction() {
	return vec2(x, y);
}

void move(char direction, float theta, float xpos, float ypos, bool mouse) {

	vec2 location = getLoction();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(xpos, DISPLAY_HEIGHT - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

	float z = Far + depth[0] * (Near - Far);
	float yrel = ypos - location[1];
	float xrel = xpos - location[0];
	float transX = 1.0f, transY = 1.0f;
	int dirc = -1;

	if (mouse) {
		transX = 1.0*relation * xrel / (float)(DISPLAY_WIDTH)*Near*2.0*tan(CAM_ANGLE*PI / 360.0f)*(Far / z);
		transY = 1.0*yrel / (float)(DISPLAY_HEIGHT)*Near*2.0*tan(CAM_ANGLE*PI / 360.0f)*(Far / z);
	}

	else if (direction == 'L' || direction == 'U')
		dirc = -1 * dirc;

	//cout << transX << " " << transY << endl;

	if (abs(transX) > 1.5)
		transX = transX / 2;

	if (abs(transY) > 1.5)
		transY = transY / 2;



	if (space)
		solver = true;


	vec3 translateDirc;

	if (direction == 'R' || direction == 'L') {
		translateDirc = vec3(dirc*transX, 0, 0);
		if (direction == 'L') {

			translateDirc = vec3(dirc*transX, 0, 0);
		}
	}
	else if (direction == 'D' || direction == 'U') {
		dirc = -dirc;
		translateDirc = vec3(0, dirc*transY, 0);
		if (direction == 'D') {

			translateDirc = vec3(0, dirc*transY, 0);
		}
		translateDirc = -translateDirc;
	}
	else {
		translateDirc = vec3(0, 0, dirc);
		if (direction == 'F') {
			dirc = -dirc;
			translateDirc = vec3(0, 0, dirc);
		}
	}
	mat4 t = glm::translate(mat4(1), translateDirc);
	if (n >= 0 && n < blockChainNum) {
		if (direction == 'F' || direction == 'B') {
			cubes[0]->mat = t * cubes[0]->mat;
		}
		else if (mouse) {
			if (abs(xpos - location[0]) > 0.1 || abs(ypos - location[1]) > 0.1) {
				cubes[0]->mat = t * cubes[0]->mat;
				if (direction == 'D' || direction == 'U')
					setPosition(location[0], ypos);
				else
					setPosition(xpos, location[1]);
			}
		}
		else
		{
			setPosition(xpos, ypos);
			cubes[0]->mat = t * cubes[0]->mat;
		}
	}
	else if (n == blockChainNum) {
		if (direction == 'F' || direction == 'B') {
			targetCube = t * targetCube;

		}
		else if (mouse) {
			if (abs(xpos - location[0]) > 0.1 || abs(ypos - location[1]) > 0.1) {
				targetCube = t * targetCube;
				if (direction == 'D' || direction == 'U')
					setPosition(location[0], ypos);
				else
					setPosition(xpos, location[1]);
			}
		}
		else
		{
			setPosition(xpos, ypos);
			targetCube = t * targetCube;
		}

	}

}

void rotate(char direction, float theta) {
	setPosition(xp, yp);
	vec3 rotateDirc;
	vec3 translateDirc;
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
	if (n >= 0 && n < blockChainNum) {
		cubes[n]->upTheta(theta, axis);

	}
	else if (n == blockChainNum) {
		targetCube = glm::rotate(targetCube, theta, rotateDirc);
	}
	else if (n == blockChainNum + 1) {
		mat4 rot1 = glm::rotate(mat4(1), theta, rotateDirc);
		cubes[0]->moveScene(rotateDirc, theta);
		targetCube = rot1 * targetCube;

		cubes[blockChainNum + 1]->mat = rot1 * cubes[blockChainNum + 1]->mat;  // 'rotate' the 'general axis'

	}
}

void pick() {



	Shader shader1("./res/shaders/colPicShader");
	GLint viewport[4];

	unsigned char data[4];

	//glClearColor(1.0f, 1.0f, 1.0f,1.0f);
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

	vec3 color;
	for (int i = 0; i < blockChainNum; i++) {
		color = vec3(1.0f / (i + 3), 0.0f, 0.0f);
		Matrixes[i] = cubes[i]->getMat() * cubes[0]->scaleMat;
		MVP = P * Matrixes[i];
		shader1.Bind();
		shader1.Update(MVP, Matrixes[i], color);
		mesh.Draw();
	}


	color = vec3(0.5f, 0.0f, 0.0f);
	MVP = P * targetCube;
	shader1.Bind();
	shader1.Update(MVP, targetCube, color);
	mesh.Draw();
	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadPixels(xp, viewport[3] - yp, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	int pickColor = data[0];
	if (pickColor == 255) {
		n = blockChainNum + 1;
		backRoundPick++;

	}
	else if (pickColor == 128) {
		n = blockChainNum;
		backRoundPick = 0;
		pervN = blockChainNum;
	}
	else
	{
		for (int i = 0; i < blockChainNum; i++) {
			float objColor = float(255.0 / (i + 3));
			int rintt = rint(objColor - 0.0000000001);
			if (pickColor == rintt)
			{
				n = i;
				pervN = i;
				backRoundPick = 0;
				break;

			}
		}
	}

	if ((n == blockChainNum + 1 && pervN != blockChainNum + 1 && pervN != -1) || backRoundPick >= 2)
	{
		n = blockChainNum + 2;
		pervN = blockChainNum + 1;
		backRoundPick = 0;
	}

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS) {
			solver = !solver;
			space = !space;
			numOfAction = 0;
		}
		break;

	case GLFW_KEY_RIGHT:
		if (action == GLFW_REPEAT || action == GLFW_PRESS)
			if (rightClick)
				move('R', 5.0, 0, 0, false);
			else {
				rotate('R', 5.0);
			}
		firstTime = true;
		break;

	case GLFW_KEY_LEFT:

		if (action == GLFW_REPEAT || action == GLFW_PRESS)
			if (rightClick) {
				move('L', 5.0, 0, 0, false);
			}
			else
			{
				rotate('L', 5.0);
			}
		break;
	case GLFW_KEY_UP:
		if (action == GLFW_REPEAT || action == GLFW_PRESS)
			if (rightClick) {
				move('U', 5.0, 0, 0, false);
			}
			else {
				rotate('U', 5.0);
			}
		break;

	case GLFW_KEY_DOWN:
		if (action == GLFW_REPEAT || action == GLFW_PRESS)
			if (rightClick) {
				move('D', 5.0, 0, 0, false);
			}
			else {
				rotate('D', 5.0);
			}

		break;

	case GLFW_MOUSE_BUTTON_LEFT:
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		break;

	default:
		break;
	}

}
void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
	xp = xpos;
	yp = ypos;
	if (firstTime) {
		setPosition(xpos, ypos);
		firstTime = false;
	}

	vec2 location = getLoction();
	if (xpos > location[0]) {
		if (rightClick)
			move('R', 1.0, xpos, ypos, true);
		else
			rotate('R', 1.0);
	}
	else if (xpos < location[0]) {
		if (rightClick)
			move('L', 1.0, xpos, ypos, true);
		else
			rotate('L', 1.0);
	}


	if (ypos > location[1]) {
		if (rightClick)
			move('D', 1.0, xpos, ypos, true);
		else
			rotate('D', 1.0);
	}
	else if (ypos < location[1])
	{
		if (rightClick)
			move('U', 1.0, xpos, ypos, true);
		else
			rotate('U', 1.0);
	}


}



void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		rightClick = false;

		pick();
	}
	else if ((button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)) {
		rightClick = true;
		pick();
	}
}
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (yoffset == 1)
		move('F', 1.0, 0, 0, false);
	else
		move('B', 1.0, 0, 0, false);


};

#endif



