#include "camera2d.hpp"

#include <cstdint>
#include <GL/gl.h>
#include <glm/glm.hpp>

#include "../world/world.hpp"

using namespace rc3;
using namespace rc3::renderer;

camera2d::camera2d(uint32_t scale_in) : scale(scale_in) {}

void camera2d::render(world::world &world) const {
	glm::vec<2, uint32_t> size = world.map->size();

	for (uint32_t i = 0; i < size.x; i++) {
		uint32_t scaled_x = i * scale;

		for (uint32_t j = 0; j < size.y; j++) {
			uint32_t scaled_y = j * scale;

			// TODO: proper texturing
			if (world.map->get_cell(glm::vec<2, uint32_t>(i, j)).is_solid()) {
				glColor3f(0.3f, 0.5f, 0.3f);
			} else {
				glColor3f(0.0f, 0.0f, 0.0f);
			}

			// Draw square (leave 1 pixel for grid)
			glBegin(GL_QUADS);
			glVertex2i(scaled_x + 1, scaled_y + 1);
			glVertex2i(scaled_x + 1, scaled_y + scale - 1);
			glVertex2i(scaled_x + scale - 1, scaled_y + scale - 1);
			glVertex2i(scaled_x + scale - 1, scaled_y + 1);
			glEnd();
		}
	}

	glPointSize(scale / 2.0f);
	glLineWidth(scale / 5.0f);
	for (auto &ent : world.get_entities()) {
		auto pos = ent->get_pos();
		auto az = ent->get_azimuth();

		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2d(pos.x * scale, pos.y * scale);
		glVertex2d((pos.x + 1 * cos(az)) * scale, (pos.y + 1 * sin(az)) * scale);
		glEnd();

		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2d(pos.x * scale, pos.y * scale);
		glEnd();
	}
}
