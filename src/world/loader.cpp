#include "loader.hpp"

#include <cstdlib>
#include <string>
#include <istream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <glm/glm.hpp>

#include "cell.hpp"
#include "cell-types.hpp"
#include "rcm-spec.hpp"
#include "../util/log.hpp"

using namespace rc3::world;

bool loader::find_section(const std::string &name) {
	source.seekg(std::ios_base::beg);

	std::string buffer;
	while (std::getline(source, buffer)) {
		if (buffer == name) {
			return true;
		}
	}

	return false;
}

level_meta loader::parse_meta() {
	if (!find_section(rcm::meta::header)) {
		log::error << "Invalid RCM format: 'meta' section not found" << std::endl;
		throw std::logic_error("Bad map file");
	}

	level_meta meta = {
		.name = "Unnamed map",
		.size = glm::vec<2, uint32_t>(0, 0),
		.spawn_pt = glm::vec2(0, 0)
	};

	std::string buffer;
	while (std::getline(source, buffer)) {
		std::istringstream splitter(buffer);
		std::getline(splitter, buffer, rcm::separator);

		if (buffer == rcm::meta::name) {
			std::getline(splitter, buffer, rcm::separator);
			meta.name = buffer;
		} else if (buffer == rcm::meta::size) {
			std::getline(splitter, buffer, rcm::separator);
			meta.size.x = std::stoi(buffer);

			std::getline(splitter, buffer, rcm::separator);
			meta.size.y = std::stoi(buffer);
		} else if (buffer == rcm::meta::spawn) {
			std::getline(splitter, buffer, rcm::separator);
			meta.spawn_pt.x = std::stof(buffer);

			std::getline(splitter, buffer, rcm::separator);
			meta.spawn_pt.y = std::stof(buffer);
		} else {
			// All done
			break;
		}
	}

	log::info << "Loading map '" << meta.name << "'" << std::endl;
	log::info << "Dimensions: (" << meta.size.x << ", " << meta.size.y << ")" << std::endl;
	log::info << "Spawn point: (" << meta.spawn_pt.x << ", " << meta.spawn_pt.y << ")" << std::endl;

	return meta;
}

cell **loader::load_map(glm::vec<2, uint32_t> dim) {
	// Allocate memory
	cell **map = (cell **)std::malloc(dim.x * sizeof(cell *));
	for (uint32_t i = 0; i < dim.x; i++) {
		map[i] = (cell *)std::malloc(dim.y * sizeof(cell));
		
		// Set all to void
		for (uint32_t j = 0; j < dim.y; j++) {
			map[i][j] = cells::VOID;
		}
	}

	// Load walls
	if (find_section(rcm::walls::header)) {
		std::string buffer;
		while (std::getline(source, buffer)) {
			std::istringstream splitter(buffer);
			std::getline(splitter, buffer, rcm::separator);

			if (buffer == rcm::walls::hwall) {
				std::getline(splitter, buffer, rcm::separator);
				uint32_t start_x = std::stoi(buffer);

				std::getline(splitter, buffer, rcm::separator);
				uint32_t y = std::stoi(buffer);

				std::getline(splitter, buffer, rcm::separator);
				uint32_t length = std::stoi(buffer);

				for (uint32_t i = start_x; i < start_x + length; i++) {
					map[i][y] = cells::WALL;
				}
			} else if (buffer == rcm::walls::vwall) {
				std::getline(splitter, buffer, rcm::separator);
				uint32_t x = std::stoi(buffer);

				std::getline(splitter, buffer, rcm::separator);
				uint32_t start_y = std::stoi(buffer);

				std::getline(splitter, buffer, rcm::separator);
				uint32_t length = std::stoi(buffer);

				for (uint32_t i = start_y; i < start_y + length; i++) {
					map[x][i] = cells::WALL;
				}
			} else {
				// All done
				break;
			}
		}
	}

	log::info << "Load complete!" << std::endl;

	return map;
}
