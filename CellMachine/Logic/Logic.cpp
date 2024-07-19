#include "../Interface.hpp"
#include "Logic.hpp"
#include <cstdint>
#include <mutex>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <thread>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <random>

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

		for (size_t i = 0; i < 20; i++) {
			SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, rng() / _8bitDiv, rng() / _8bitDiv, rng() / _8bitDiv, SDL_ALPHA_OPAQUE);

			float x1 = rng() / static_cast< float >(rng.max());
			float y1 = rng() / static_cast< float >(rng.max());
			float x2 = rng() / static_cast< float >(rng.max());
			float y2 = rng() / static_cast< float >(rng.max());

			SDL_RenderDrawLineF(CellMachine::Interface::sdlRenderer, x1, y1, x2, y2);
		}

		SDL_RenderPresent(CellMachine::Interface::sdlRenderer);
	}

	CellMachine::Interface::destroyRenderer();
	CellMachine::Interface::destroyWindow();
}
