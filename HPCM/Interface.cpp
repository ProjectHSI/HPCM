#include "Interface.hpp"
#include "Settings/Settings.hpp"
#include <SDL_error.h>
#include <SDL_render.h>
#include <SDL_video.h>
#include <Settings/Settings.pb.h>
#include <stdexcept>

SDL_Window *CellMachine::Interface::sdlWindow;
SDL_Renderer *CellMachine::Interface::sdlRenderer;

void CellMachine::Interface::createWindow() {
	auto settingsWindowType = CellMachine::Settings::Settings::currentSettings.windowtype();

	sdlWindow = SDL_CreateWindow("HPCM",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		CellMachine::Settings::Settings::currentSettings.resolutionx(),
		CellMachine::Settings::Settings::currentSettings.resolutiony(),
		(
		(settingsWindowType == CellMachine::Settings::Settings::WindowType::BorderlessWindowed ? SDL_WINDOW_BORDERLESS : 0) |
		(settingsWindowType == CellMachine::Settings::Settings::WindowType::FullScreen ? SDL_WINDOW_FULLSCREEN : 0)
	));

	if (sdlWindow == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
}

void CellMachine::Interface::destroyWindow() {
	SDL_DestroyWindow(sdlWindow);
}


void CellMachine::Interface::createRenderer() {
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
}

void CellMachine::Interface::destroyRenderer() {
	SDL_DestroyRenderer(sdlRenderer);
}


void CellMachine::Interface::updateWindow() {

}

void CellMachine::Interface::updateRenderer() {

}