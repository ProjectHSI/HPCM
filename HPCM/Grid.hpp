#include <cstdint>
#include <map>
#include <vector>
#include <optional>

namespace CellMachine {
	namespace Grid {
		class Grid {
			uint64_t sizeX;
			uint64_t sizeY;

			std::optional<int> t1;
			std::vector<int> t;
		};
	}
}