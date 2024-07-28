#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace HPCM {
	namespace Screens {
		namespace LoadingScreen {
			extern std::recursive_mutex loadingBarsMutex;
			struct LoadingBar {
				std::string name {};
				uintmax_t workRequired {};
				uintmax_t workDone = 0;
			};
			extern std::vector<LoadingBar> loadingBars;

			extern std::recursive_mutex logMutex;
			extern std::vector<std::string> log;

			void clear();
			int addLog();

			void draw();
		}
	}
}