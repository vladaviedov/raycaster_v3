#include "math.hpp"

using namespace rc3;
using namespace rc3::math;

glm::vec2 math::vec2_rotate(glm::vec2 in, float angle) {
	/*
	 * [ cos(th) -sin(th) ] [ x ]
	 * [ sin(th)  cos(th) ] [ y ]
	 */
	return glm::vec2(
		in.x * cos(angle) - in.y * sin(angle),
		in.x * sin(angle) + in.y * cos(angle)
	);
}
