#include <Settings.pb.h>

namespace CellMachine {
	namespace Settings {
		extern Settings currentSettings;

		void load();

		void save();
		void saveAsync();
	}
}