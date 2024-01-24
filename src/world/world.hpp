#pragma once

#include <vector>
#include <memory>
#include <filesystem>

#include "level.hpp"
#include "../entity/abstract-entity.hpp"
#include "../entity/player.hpp"

namespace rc3 {
	namespace world {

		class world {

			private:
				std::vector<std::shared_ptr<entity::abstract_entity>> entities;

			public:
				world(std::filesystem::path file);

				std::shared_ptr<level> map;

				inline void add_entity(std::shared_ptr<entity::abstract_entity> ent) {
					entities.push_back(ent);
				}

				inline const std::vector<std::shared_ptr<entity::abstract_entity>> get_entities() const {
					return entities;
				}

				std::shared_ptr<entity::player> spawn_player(input::abstract_input &control);
		};

	}
}
