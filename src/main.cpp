#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "util/log.hpp"
#include "world/world.hpp"
#include "renderer/camera2d.hpp"
#include "input/keyboard.hpp"

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

	rc3::world::world game_world("maps/walls.rcm");
	glfwSetWindowTitle(win, ("rc3 | " + game_world.map->name()).c_str());
	rc3::renderer::camera2d view(32);

	rc3::input::keyboard kb;
	kb.enable(win);
	auto player = game_world.spawn_player(kb);

	// Main loop
	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view.render(game_world);
		player->calc_update(0.1f, 1.0f);
		player->commit_update();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// Clean up
	rc3::log::debug << "Goodbye!" << std::endl;
	glfwDestroyWindow(win);
	glfwTerminate();

	return 0;
}
