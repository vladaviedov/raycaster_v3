#pragma once

#include <string>
#include <istream>
#include <glm/glm.hpp>

#include "cell.hpp"

namespace rc3 {
	namespace world {

		struct level_meta {
			std::string name;
			glm::vec<2, uint32_t> size;
			glm::vec2 spawn_pt;
		};

		class loader {

			private:
				std::istream &source;

				bool find_section(const std::string &name);

			public:
				loader(std::istream &input) : source(input) {}

				level_meta parse_meta();
				cell **load_map(glm::vec<2, uint32_t> dim);

		};

	}
}
