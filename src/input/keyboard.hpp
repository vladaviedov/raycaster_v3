#pragma once

#include "abstract-input.hpp"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "bind.hpp"

namespace rc3 {
	namespace input {

		class keyboard : public abstract_input {
		
			private:
				GLFWwindow *window;

				keybind move_f = { .name = "Move forward", .key = GLFW_KEY_W };
				keybind move_b = { .name = "Move backward", .key = GLFW_KEY_S };
				keybind move_l = { .name = "Move left", .key = GLFW_KEY_A };
				keybind move_r = { .name = "Move right", .key = GLFW_KEY_D };

				keybind look_l = { .name = "Look left", .key = GLFW_KEY_Q };
				keybind look_r = { .name = "Look right", .key = GLFW_KEY_E };

			public:
				virtual glm::vec2 move_vec();
				virtual float azimuth_rot();

				inline void enable(GLFWwindow *win) {
					window = win;
				}

				inline void disable() {
					window = nullptr;
				}

		};

	}
}
