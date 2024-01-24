#pragma once

#include <string>

namespace rc3 {
	namespace rcm {

		const char separator = ',';
		
		namespace meta {
			const std::string header = "[meta]";
			const std::string name = "name";
			const std::string size = "size";
			const std::string spawn = "spawn";
		}

		namespace walls {
			const std::string header = "[walls]";
			const std::string hwall = "hwall";
			const std::string vwall = "vwall";
		}

	}
}
