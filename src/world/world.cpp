#include "world.hpp"

#include <vector>
#include <memory>
#include <fstream>
#include <filesystem>

#include "level.hpp"
#include "loader.hpp"
#include "../entity/abstract-entity.hpp"
#include "../entity/player.hpp"

using namespace rc3::world;

world::world(std::filesystem::path file) {
	std::ifstream map_file(file);
	loader file_loader(map_file);
	map = std::make_shared<level>(file_loader);
}

std::shared_ptr<rc3::entity::player> world::spawn_player(input::abstract_input &control) {
	auto player = std::make_shared<entity::player>(map->get_spawn(), control);
	entities.push_back(player);
	return player;
}
