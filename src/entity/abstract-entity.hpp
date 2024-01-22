#pragma once

#include <glm/glm.hpp>

namespace rc3 {
	namespace entity {

		class abstract_entity {
			
			protected:
				float inertia = 1.0f;

				// Current frame
				glm::vec2 pos;
				glm::vec2 vel;

				// Next frame
				glm::vec2 pos_next;
				glm::vec2 vel_next;

			public:
				abstract_entity(glm::vec2 spawn);

				void apply_force(glm::vec2 force, float delta_time);
				glm::vec2 calc_update(float delta_time, float friction);
				void commit_update();

		};

	}
}
