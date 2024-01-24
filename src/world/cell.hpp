#pragma once

namespace rc3 {
	namespace world {
		
		class cell {
			
			private:
				bool solid;

			public:
				cell(bool solid_in) {
					solid = solid_in;
				}

				inline bool is_solid() const {
					return solid;
				}

		};

	}
}
