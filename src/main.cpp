#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdexcept>

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
		
		glm::vec<2, uint32_t> old_pos = player->get_pos();
		glm::vec<2, uint32_t> new_pos = player->calc_update(0.1f, 1.0f);
		
		try {
			if (game_world.map->get_cell(new_pos).is_solid()) {
				if (new_pos.y > old_pos.y) {
					player->apply_force(glm::vec2(0, -1), 1);
				}
				if (new_pos.y < old_pos.y) {
					player->apply_force(glm::vec2(0, 1), 1);
				}
				if (new_pos.x > old_pos.x) {
					player->apply_force(glm::vec2(-1, 0), 1);
				}
				if (new_pos.x < old_pos.x) {
					player->apply_force(glm::vec2(1, 0), 1);
				}

				player->calc_update(0.1f, 1.0f);
			}
		} catch (std::domain_error &ex) {
			rc3::log::debug << "Out of bounds!" << std::endl;
		}

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
