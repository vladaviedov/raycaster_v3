#pragma once

#include <glm/glm.hpp>

#include "abstract-entity.hpp"
#include "../input/abstract-input.hpp"

namespace rc3 {
	namespace entity {

		class player : public abstract_entity {
		
			private:
				input::abstract_input &ctrl;

			public:
				player(glm::vec2 spawn, input::abstract_input &ctrl_in);

				virtual glm::vec2 calc_update(float delta_time, float friction);

		};

	}
}
