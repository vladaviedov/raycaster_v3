#pragma once

#include <iostream>

namespace rc3 {
	namespace log {

		enum loglvl {
			DEBUG,
			INFO,
			WARN,
			ERROR,
			FATAL
		};

		class logstream {

			public:
				logstream(loglvl log) : lvl(log) {}

				template<typename T>
				logstream &operator<<(const T &value) {
					if (newline) {
						std::cout << "[" << lvl_string() << "] ";
						newline = false;
					}
					
					std::cout << value;
					return *this;
				}

				logstream &operator<<(std::ostream &(*osmanip)(std::ostream &)) {
					std::cout << osmanip;
					newline = true;
					return *this;
				}

			private:
				const char *lvl_string() const;

				const loglvl lvl;
				bool newline = true;

		};

		extern logstream debug;
		extern logstream info;
		extern logstream warn;
		extern logstream error;
		extern logstream fatal;

	}
}
