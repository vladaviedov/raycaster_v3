#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "cell.hpp"
#include "loader.hpp"

namespace rc3 {
	namespace world {
		 
		class level {

			private:
				level_meta meta;
				cell **data;

			public:
				level(loader &loader);
				~level();

				inline std::string name() const {
					return meta.name;
				}

				inline glm::vec<2, uint32_t> size() const {
					return meta.size;
				}

				inline glm::vec2 spawn() const {
					return meta.spawn_pt;
				}

				cell &get_cell(glm::vec<2, uint32_t> coords) const;

		};

	}
}
