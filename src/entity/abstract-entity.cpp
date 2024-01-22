#include "abstract-entity.hpp"

using namespace rc3::entity;

abstract_entity::abstract_entity(glm::vec2 spawn)
	: pos(spawn),
	  vel(0) {}

void abstract_entity::apply_force(glm::vec2 force, float delta_time) {
	// delta v = a * delta t
	vel += (force / inertia) * delta_time;
}

glm::vec2 abstract_entity::calc_update(float delta_time, float friction) {
	// Copy quantities
	pos_next = pos;
	vel_next = vel;

	// Apply friction force
	glm::vec2 fric_force = -vel * friction;
	vel_next += (fric_force / inertia) * delta_time;

	// Apply velocity
	pos_next += vel * delta_time;

	return pos_next;
}

void abstract_entity::commit_update() {
	pos = pos_next;
	vel = vel_next;
}
