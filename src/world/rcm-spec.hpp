#pragma once

#include <string>

namespace rc3 {
	namespace rcm {
		
		namespace meta {
			const std::string header = "[meta]";
			const std::string name = "name";
			const std::string size = "size";
			const std::string spawn = "spawn";
		}

	}
}

// Meta section
#define META_HDR "[meta]"
#define META_NAME "name"
#define META_SIZE "size"
#define META_SPAWN "spawn"

// Walls section
#define WALLS_HDR "[walls]"
#define WALLS_HWALL "hwall"
#define WALLS_VWALL "vwall"
