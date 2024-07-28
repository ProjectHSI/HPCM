#include "../ApplicationContext.hpp"
#include "Settings.hpp"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <mutex>
#include <Settings/Settings.pb.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>

static std::recursive_mutex settingsLock {};

static std::filesystem::path settingsFilePath = std::filesystem::path {};

CellMachine::Settings::Settings::Settings CellMachine::Settings::Settings::currentSettings {};

static void fillInPaths() {
	if (settingsFilePath.empty()) {
		settingsFilePath = CellMachine::ApplicationContext::prefPathString + "settings.bin";
	}
}

void CellMachine::Settings::Settings::load() {
	std::lock_guard settingsLockGuard(settingsLock);

	fillInPaths();

	if (CellMachine::ApplicationContext::prefPathPath.empty())
		throw new std::runtime_error("Cannot save on this system (or ApplicationContext hasn't been initalized).");

	{
		if (!std::filesystem::exists(settingsFilePath)) {
			std::ofstream {settingsFilePath};
		}

		std::fstream settingsFileReadStream(settingsFilePath, std::ios::in | std::ios::binary);
		
		if (!currentSettings.ParseFromIstream(&settingsFileReadStream))
			throw new std::runtime_error("Failed to parse settings file.");
	}

	bool queueSave = false;

	if (!currentSettings.has_windowtype()) {
		currentSettings.set_windowtype(CellMachine::Settings::Settings::WindowType::Windowed);
		queueSave = true;
	}

	if (!currentSettings.has_resolutionx()) {
		currentSettings.set_resolutionx(854);
		queueSave = true;
	}

	if (!currentSettings.has_resolutiony()) {
		currentSettings.set_resolutiony(480);
		queueSave = true;
	}

	if (queueSave) {
		//if (!settingsLock.try_lock()) settingsLockGuard.~lock_guard(); // needed to run the operation below & prevent errors.
		CellMachine::Settings::Settings::save();
	}
}

void CellMachine::Settings::Settings::save() {
	std::lock_guard settingsLockGuard(settingsLock);

	fillInPaths();

	{
		std::fstream settingsFileWriteStream(settingsFilePath, std::ios::out | std::ios::trunc | std::ios::binary);

		if (!currentSettings.SerializeToOstream(&settingsFileWriteStream))
			throw new std::runtime_error("Failed to write to settings file.");
	}
}

void CellMachine::Settings::Settings::saveAsync() {
	std::thread saveThread(CellMachine::Settings::Settings::save);
}