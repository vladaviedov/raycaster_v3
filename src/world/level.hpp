#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "cell.hpp"

namespace rc3 {
	namespace world {
		 
		class level {

			private:
				glm::vec<2, uint32_t> dimensions;
				glm::vec2 spawn;
				cell **data;

			public:
				level();
				~level();

				inline glm::vec<2, uint32_t> size() const {
					return dimensions;
				}

				inline glm::vec2 get_spawn() const {
					return spawn;
				}

				cell &get_cell(glm::vec<2, uint32_t> coords) const;

		};

	}
}
