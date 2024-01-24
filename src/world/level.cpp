#include "level.hpp"

#include <exception>
#include <stdexcept>
#include <cstdint>
#include <glm/glm.hpp>
 
#include "cell.hpp"
#include "loader.hpp"
#include "../util/log.hpp"

using namespace rc3::world;

level::level(loader &loader) : data(nullptr) {
	meta = loader.parse_meta();
	data = loader.load_map(meta.size);
}

level::~level() {
	for (uint32_t i = 0; i < meta.size.x; i++) {
		std::free(data[i]);
	}

	std::free(data);
}

cell &level::get_cell(glm::vec<2, uint32_t> coords) const {
	if (coords.x >= meta.size.x || coords.y >= meta.size.y) {
		log::error << "Tried accessing cell out range at (" << coords.x << ", " << coords.y << ")" << std::endl;
		log::error << "World dimensions: (" << meta.size.x << ", " << meta.size.y << ")" << std::endl;
		throw std::domain_error("Cell out of range");
	}

	return data[coords.x][coords.y];
}
