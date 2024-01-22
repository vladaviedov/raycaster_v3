#include "level.hpp"

#include <exception>
#include <stdexcept>
 
#include "../util/log.hpp"

using namespace rc3::world;

cell &level::get_cell(glm::vec<2, uint32_t> coords) const {
	if (coords.x >= dimensions.x || coords.y >= dimensions.y) {
		log::error << "Tried accessing cell out range at " << coords << std::endl;
		log::error << "World dimensions: " << dimensions << std::endl;
		throw std::domain_error("Cell out of range");
	}

	return data[coords.x][coords.y];
}
