#include "player.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "abstract-entity.hpp"
#include "../util/math.hpp"

using namespace rc3;
using namespace rc3::entity;

player::player(glm::vec2 spawn, input::abstract_input &ctrl_in) :
	abstract_entity(spawn),
	ctrl(ctrl_in) {}

glm::vec2 player::calc_update(float delta_time, float friction) {
	azimuth += ctrl.azimuth_rot();
	glm::vec2 movement = glm::normalize(ctrl.move_vec());
	glm::vec2 rotated = math::vec2_rotate(movement, azimuth);
	apply_force(rotated, delta_time);

	return abstract_entity::calc_update(delta_time, friction);
}

