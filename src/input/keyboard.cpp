#include "keyboard.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "bind.hpp"

using namespace rc3::input;

glm::vec2 keyboard::move_vec() {
	if (window == nullptr) {
		return glm::vec2(0, 0);
	}

	bool f = glfwGetKey(window, move_f.key) == GLFW_PRESS;
	bool b = glfwGetKey(window, move_b.key) == GLFW_PRESS;
	bool l = glfwGetKey(window, move_l.key) == GLFW_PRESS;
	bool r = glfwGetKey(window, move_r.key) == GLFW_PRESS;

	// Both 0, Front +x, Back -x, Nothing 0
	int x = (f && b) ? 0 : (f ? 1 : (b ? -1 : 0));
	// Both 0, Left -y, Back +y, Nothing 0
	int y = (l && r) ? 0 : r ? 1 : (l ? -1 : 0);

	return glm::vec2(x, y);
}

float keyboard::azimuth_rot() {
	bool l = glfwGetKey(window, look_l.key) == GLFW_PRESS;
	bool r = glfwGetKey(window, look_r.key) == GLFW_PRESS;

	// Handles both pressed or neither
	if (l == r) {
		return 0;
	}

	return l ? 0.1 : -0.1;
}
