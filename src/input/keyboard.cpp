#include "keyboard.hpp"

#include <glm/glm.hpp>

using namespace rc3::input;

glm::vec2 keyboard::move_vec() {
	return glm::vec2(2, 0);
}

float keyboard::azimuth_rot() {
	return 0.05;
}
