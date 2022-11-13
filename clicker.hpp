#include "includes.hpp"

namespace clicker {

	namespace random {
		int drop();
		int random_int(int min, int max);
		inline int mindelay = 14;
		inline int maxdelay = 37;
	}

	namespace mouse {
		void LUP();
		void LDOWN();
	}

	extern void thread();
}