#include "../Interface.hpp"
#include "Logic.hpp"
#include <cstdint>
#include <mutex>
#include <random>
#include <SDL_blendmode.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <thread>
#include "../Settings/Interface.hpp"
#include "../Screens/LoadingScreen/LoadingScreen.hpp"
#include "../Grid.hpp"

using namespace std::chrono_literals;

/*
std::mutex rgbMutex {};

static void rgbCount(bool *keepCounting) {
	while (keepCounting) {
		rgbMutex.lock();
		r++;

		if (r == 0) {
			g++;

			if (g == 0) {
				b++;
			}
		}
		rgbMutex.unlock();

		std::this_thread::sleep_for(5ms);
	}
}
*/

void CellMachine::Logic::Logic::logic() {
	CellMachine::Interface::createWindow();
	CellMachine::Interface::createRenderer();

	bool continueRunning = true;

	std::mt19937 rng {};
	
	constexpr float _8bitDiv = static_cast<float>(rng.max()) / 255;
	constexpr float _16bitDiv = static_cast< float >(rng.max()) / 255;

	while (continueRunning) {
		{
			SDL_Event event { };

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					continueRunning = false;
			}
		}

		SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(CellMachine::Interface::sdlRenderer);

		for (size_t i = 0; i < 250; i++) {
			SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, rng() / _8bitDiv, rng() / _8bitDiv, rng() / _8bitDiv, SDL_ALPHA_OPAQUE);

			float x1 = rng() / (static_cast< float >(rng.max()) / 864);
			float y1 = rng() / (static_cast< float >(rng.max()) / 480);
			float x2 = rng() / (static_cast< float >(rng.max()) / 854);
			float y2 = rng() / (static_cast< float >(rng.max()) / 480);

			SDL_RenderDrawLineF(CellMachine::Interface::sdlRenderer, x1, y1, x2, y2);
		}

		/*
		{
			const SDL_FRect rect = {10, 10, 40, 40};
			SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
			SDL_RenderDrawRectF(CellMachine::Interface::sdlRenderer, &rect);
		}
		*/

		//HPCM::Settings::Interface::drawSettings();

		HPCM::Screens::LoadingScreen::draw();

		{
			auto grid = CellMachine::Grid::Grid(25, 25);
			SDL_RenderCopy(CellMachine::Interface::sdlRenderer, grid.getRenderTexture().get(), NULL, NULL);
		}

		SDL_RenderPresent(CellMachine::Interface::sdlRenderer);
	}

	CellMachine::Interface::destroyRenderer();
	CellMachine::Interface::destroyWindow();
}
