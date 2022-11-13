#include "includes.hpp"

namespace utils {
	namespace thread {
		namespace launch {
			void compatibility();
			void normal();
		}
	}
	namespace selfdestruct {
		void selfdelete();
	}
	namespace compatibility {
		void check();
		inline RTL_OSVERSIONINFOW GetRealOSVersion();
	}
	namespace debug {
		inline bool logs = true;
	}
	namespace userdata {
		inline char* username = getenv("username");
	}
	void init();
	void ShowConsoleCursor(bool showFlag);
	inline void visuals();
}