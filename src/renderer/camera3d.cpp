#include "camera3d.hpp"

#include <memory>
#include <cmath>
#include <cstdint>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../util/log.hpp"
#include "../util/math.hpp"
#include "../world/world.hpp"
#include "../entity/abstract-entity.hpp"

#define WIDTH 2560.0f
#define HEIGHT 1440.0f
#define DEG (M_PI / 180)

using namespace rc3;
using namespace rc3::renderer;

camera3d::camera3d(float fov_in, float rpd_in, float max_dist_in) : fov(fov_in), rpd(rpd_in), max_dist(max_dist_in) {}

raycast camera3d::cast(world::world &world, float azimuth) const {
	raycast h_res = h_cast(world, azimuth);
	raycast v_res = v_cast(world, azimuth);

	return h_res.distance > v_res.distance
		? v_res
		: h_res;
}

raycast camera3d::h_cast(world::world &world, float azimuth) const {
	raycast res = {
		.success = false,
		.dir = HORIZONTAL,
		.cell = nullptr,
		.distance = 0,
	};

	// These will have undef tangents
	if (math::near(azimuth, 0) || math::near(azimuth, M_PI)) {
		return res;
	}

	int dir = azimuth > M_PI ? -1 : 1;
	glm::vec2 pos = entity_bind->get_pos();
	glm::vec2 ray;

	// Reach first boundary
	ray.y = dir == 1 ? std::ceil(pos.y) : std::floor(pos.y);
	ray.x = pos.x + (ray.y - pos.y) / std::tan(azimuth);
	uint32_t cell_y = dir == 1 ? ray.y : (ray.y - 1);
	bool solid = world.map->get_cell(glm::vec<2, uint32_t>(ray.x, cell_y)).is_solid();
	float distance = glm::length(ray - pos);
	
	// If first ray is too far, exit now
	if (distance > max_dist) {
		return res;
	}

	// Continue until solid or maxed distance
	while (!solid && distance < max_dist) {
		ray.y += dir;
		ray.x += dir / std::tan(azimuth);
		cell_y = dir == 1 ? ray.y : (ray.y - 1);
		solid = world.map->get_cell(glm::vec<2, uint32_t>(ray.x, cell_y)).is_solid();
		distance = glm::length(ray - pos);
	}

	// If solid hit & in-distance, populate res
	if (solid && distance < max_dist) {
		res.success = true;
		res.distance = distance;
		res.cell = &world.map->get_cell(glm::vec<2, uint32_t>(ray.x, cell_y));
	}
	
	return res;
}

raycast camera3d::v_cast(world::world &world, float azimuth) const {
	raycast res = {
		.success = false,
		.dir = VERTICAL,
		.cell = nullptr,
		.distance = 0,
	};

	// These will have undef tangents
	if (math::near(azimuth, M_PI / 2) || math::near(azimuth, 3 * M_PI / 2)) {
		return res;
	}

	int dir = (azimuth > M_PI / 2 && azimuth < 3 * M_PI / 2) ? -1 : 1;
	glm::vec2 pos = entity_bind->get_pos();
	glm::vec2 ray;

	// Reach first boundary
	ray.x = dir == 1 ? std::ceil(pos.x) : std::floor(pos.x);
	ray.y = pos.y + (ray.x - pos.x) * std::tan(azimuth);
	uint32_t cell_x = dir == 1 ? ray.x : (ray.x - 1);
	bool solid = world.map->get_cell(glm::vec<2, uint32_t>(cell_x, ray.y)).is_solid();
	float distance = glm::length(ray - pos);

	// If first ray is too far, exit now
	if (distance > max_dist) {
		return res;
	}

	// Continue until solid or maxed distance
	while (!solid && distance < max_dist) {
		ray.x += dir;
		ray.y += dir * std::tan(azimuth);
		cell_x = dir == 1 ? ray.x : (ray.x - 1);
		solid = world.map->get_cell(glm::vec<2, uint32_t>(cell_x, ray.y)).is_solid();
		distance = glm::length(ray - pos);
	}

	// If solid hit & in-distance, populate res
	if (solid && distance < max_dist) {
		res.success = true;
		res.distance = distance;
		res.cell = &world.map->get_cell(glm::vec<2, uint32_t>(cell_x, ray.y));
	}
	
	return res;
}

void camera3d::draw_line(float width, float height, float start) const {
	glBegin(GL_QUADS);
	glVertex2d(start, (HEIGHT - height) / 2.0f);
	glVertex2d(start + width, (HEIGHT - height) / 2.0f);
	glVertex2d(start + width, (HEIGHT + height) / 2.0f);
	glVertex2d(start, (HEIGHT + height) / 2.0f);
	glEnd();
}

void camera3d::render(world::world &world) const {
	if (entity_bind == nullptr) {
		return;
	}

	float az = entity_bind->get_azimuth();

	uint32_t line_count = fov * rpd;
	float line_width = WIDTH / line_count;
	glLineWidth(line_width);

	// Left size of the screen
	float start_az = az - (fov * DEG / 2.0f);

	// Draw rays
	for (uint32_t i = 0; i < line_count; i++) {
		// This ray's angle
		float cur_az = math::wrap_angle(start_az + i * (DEG / rpd));
		float delta = az - cur_az;

		// Do raycast
		raycast result = cast(world, cur_az);
		if (!result.success) {
			continue;
		}
		log::debug << "Angle: " << cur_az << std::endl;
		log::debug << "RES: " <<  result.distance << std::endl;

		// Set color
		if (result.success) {
			result.dir == HORIZONTAL
				? glColor3d(0.7, 0, 0)
				: glColor3d(0.5, 0, 0);
		} else {
			glColor3d(0.3, 0.3, 0.3);
		}

		// Correct distance for side angles
		float adj_distance = result.distance * std::cos(delta);

		// Draw box
		float height = HEIGHT / adj_distance;
		draw_line(line_width, height, line_width * i);
	}
}
