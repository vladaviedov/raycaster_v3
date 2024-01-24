#pragma once

#include "camera.hpp"
#include "../world/world.hpp"

namespace rc3 {
	namespace renderer {

		class camera2d : public camera {

			private:
				uint32_t scale;

			public:
				camera2d(uint32_t scale_in);

				void render(world::world &world) const;

		};

	}
}
