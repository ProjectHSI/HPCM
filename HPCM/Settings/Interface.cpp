#include "../Interface.hpp"
#include "Interface.hpp"
#include <SDL_blendmode.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>

void HPCM::Settings::Interface::drawSettings() {
	const SDL_Rect settingsBackground = {10, 10, 854 - 10 - 10, 480 - 10 - 10};

	SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 0, 0, 0, 127);
	SDL_SetRenderDrawBlendMode(CellMachine::Interface::sdlRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &settingsBackground);

	SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(CellMachine::Interface::sdlRenderer, &settingsBackground);
}