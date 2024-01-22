#pragma once

#include "abstract-input.hpp"

#include <glm/glm.hpp>

namespace rc3 {
	namespace input {

		class keyboard : public abstract_input {
		
			public:
				virtual glm::vec2 move_vec();

		};

	}
}
