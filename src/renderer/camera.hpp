#pragma once

#include "../world/world.hpp"

namespace rc3 {
	namespace renderer {

		class camera {
			
			public:
				virtual void render(world::world &world) const = 0;

		};

	}
}
