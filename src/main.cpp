#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "util/log.hpp"

#define SCREEN_HEIGHT 1920
#define SCREEN_WIDTH 1080

int main() {
	glfwInit();

	// Create window & context
	GLFWwindow *win = glfwCreateWindow(
		SCREEN_HEIGHT,
		SCREEN_WIDTH,
		"rc3",
		nullptr,
		nullptr
	);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);

	// Configure input
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(win, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	// Setup screen
	glClearColor(0.3, 0.3, 0.3, 0);
	gluOrtho2D(0, SCREEN_HEIGHT, SCREEN_WIDTH, 0);

	rc3::log::debug << "Hello!" << std::endl;

	// Main loop
	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// Clean up
	rc3::log::debug << "Goodbye!" << std::endl;
	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}
