#pragma once

#include <memory>

#include "camera.hpp"
#include "../world/world.hpp"
#include "../world/cell.hpp"
#include "../entity/abstract-entity.hpp"

namespace rc3 {
	namespace renderer {

		enum rc_hit_type {
			HORIZONTAL,
			VERTICAL
		};

		struct raycast {
			bool success;
			rc_hit_type dir;
			const world::cell *cell;
			float distance;
		};

		class camera3d : public camera {

			private:
				float fov;
				float rpd;
				float max_dist;
				std::shared_ptr<entity::abstract_entity> entity_bind;

				raycast cast(world::world &world, float azimuth) const;
				raycast h_cast(world::world &world, float azimuth) const;
				raycast v_cast(world::world &world, float azimuth) const;
				void draw_line(float width, float height, float start) const;

			public:
				camera3d(float fov_in, float rpd_in, float max_dist_in);

				void render(world::world &world) const;

				inline void bind(std::shared_ptr<entity::abstract_entity> ent) {
					entity_bind = ent;
				}

				inline void unbind() {
					entity_bind = nullptr;
				}

		};

	}
}
