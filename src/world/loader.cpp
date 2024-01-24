#include "loader.hpp"

#include <istream>
#include <glm/glm.hpp>

#include "cell.hpp"
#include "rcm-spec.hpp"

using namespace rc3::world;

level_meta loader::parse_meta() const {

}

cell **loader::load_map(glm::vec<2, uint32_t> dim) const {
	// Allocate memory
	cell **map = new cell *[dim.x];
	for (uint32_t i = 0; i < dim.x; i++) {
		map[i] = new cell[dim.y];
	}

	return map;
}
