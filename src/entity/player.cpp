#include "player.hpp"

#include <glm/glm.hpp>

#include "abstract-entity.hpp"

using namespace rc3::entity;

player::player(glm::vec2 spawn, input::abstract_input &ctrl_in) :
	abstract_entity(spawn),
	ctrl(ctrl_in) {}

glm::vec2 player::calc_update(float delta_time, float friction) {
	return abstract_entity::calc_update(delta_time, friction);
}

