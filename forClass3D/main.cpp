#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "stb_image.h"
#include "SOIL\SOIL2.h"
#include "shader.h"
#include "inputManager.h"
#include "cubeLink.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

using namespace glm;

GLuint EBO, EBO2;
GLuint textureCube, textureChain;
int width, height, width2, height2;
vec3 color;
const char *result_string_pointer = "SOIL initialized";

void drawCube(mat4 toDraw) {
	MVP = P * toDraw;
	shader.Bind();
	color = vec3(1.0f, 1.0f, 1.0f);
	shader.Update(MVP, toDraw, color);
}

unsigned char* SOIL_load_image(const char *filename, int *width, int *height, int *channels, int force_channels) {
	unsigned char *result = stbi_load(filename, width, height, channels, force_channels);
	if (result == NULL) {
		result_string_pointer = stbi_failure_reason();
	} else {
		result_string_pointer = "Image loaded";
	}
	return result;
}


void SOIL_free_image_data(unsigned char *img_data) {
	if (img_data) {
		free((void*)img_data);
	}
}


GLuint addTex(int width, int height, char *path) {
	GLuint texture;

	// add texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SOURCE0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenBuffers(1, &EBO);

	// bind the vertex array and vertes buffer(s) and attribute pointer(s)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// texture coordinates attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 24 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	
	// load the texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return texture;
}

void putTex(GLuint texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(shader.m_program, "ourTexture"), 0);	// check shader.m_program
}

int main(int argc, char** argv){
	textureCube = addTex(width, height, "res/textures/grass.bmp");
	glfwSetKeyCallback(display.m_window, key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(display.m_window, cursorPositionCallback);
	glfwSetScrollCallback(display.m_window, scrollCallback);

	initCubes();
	vec3 color;
	while (!glfwWindowShouldClose(display.m_window)){
		glGetIntegerv(GL_VIEWPORT, viewport);
		glReadPixels(location[0], DISPLAY_HEIGHT - location[1] - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depth);

		Sleep(3);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// add texture
		putTex(textureCube);

		drawCube(cubes[blockChainNum + 1]->getMat());  // for general axises
		buildGenAxises();
		drawCube(targetCube);
		mesh.Draw();

		mat4 matrix;
		textureChain = addTex(width, height, "res/textures/box0.bmp");

		for (int i = 0; i < blockChainNum; i++) {
			matrix = cubes[i]->getMat() * cubes[0]->scaleMat;
			MVP = P * matrix;
			shader.Bind();
			shader.Update(MVP, matrix, color);
			buildAxises();
			putTex(textureChain);
			mesh.Draw();
		}

		display.SwapBuffers();
		glfwPollEvents();
		if (solver) {
			IKsolver();
			numOfAction = (numOfAction + 1) % (blockChainNum);
			Sleep(3);
		}
	}

	glDeleteBuffers(1, &EBO);

	return 0;
}





