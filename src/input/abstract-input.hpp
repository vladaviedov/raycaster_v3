#pragma once

#include <glm/glm.hpp>

namespace rc3 {
	namespace input {

		class abstract_input {

			public:
				virtual glm::vec2 move_vec() = 0;

		};

	}
}
