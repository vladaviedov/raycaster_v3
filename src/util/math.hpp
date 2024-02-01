#pragma once

#include <cmath>
#include <glm/glm.hpp>

namespace rc3 {
	namespace math {

		glm::vec2 vec2_rotate(glm::vec2 in, float angle);
		
		inline float wrap_angle(float input) {
			return input - 2 * M_PI * std::floor(input / (2 * M_PI));
		}

		inline bool near(float input, float value) {
			return std::abs(input - value) < 0.001;
		}

	}
}
