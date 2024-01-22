#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "cell.hpp"

namespace rc3 {
	namespace world {
		 
		class world {

			private:
				glm::vec<2, uint32_t> dimensions;
				glm::vec2 spawn;
				cell **data;

			public:
				world();
				~world();

				glm::vec<2, uint32_t> size() const;
				glm::vec2 get_spawn() const;
				cell &get_cell(uint32_t x, uint32_t y) const;

		};

	}
}
