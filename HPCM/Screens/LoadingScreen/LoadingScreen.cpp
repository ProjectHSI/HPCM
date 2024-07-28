#include "../../ApplicationContext.hpp"
#include "../../Interface.hpp"
#include "LoadingScreen.hpp"
#include <mutex>
#include <optional>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

std::recursive_mutex HPCM::Screens::LoadingScreen::loadingBarsMutex {};
std::vector<HPCM::Screens::LoadingScreen::LoadingBar> HPCM::Screens::LoadingScreen::loadingBars {};

std::recursive_mutex HPCM::Screens::LoadingScreen::logMutex {};
std::vector<std::string> HPCM::Screens::LoadingScreen::log {};

void HPCM::Screens::LoadingScreen::clear() { }

int HPCM::Screens::LoadingScreen::addLog() {
	std::lock_guard logLock(HPCM::Screens::LoadingScreen::logMutex);

	HPCM::Screens::LoadingScreen::log.emplace(HPCM::Screens::LoadingScreen::log.begin(), "t");

	return 1;
}
int t = HPCM::Screens::LoadingScreen::addLog();

std::mutex fontMutex {};
std::optional<TTF_Font *> ttfFont = std::nullopt;
std::thread fontThread {};

static bool justEmpty = true;

void HPCM::Screens::LoadingScreen::draw() {
	std::lock_guard loadingBarsMutex(HPCM::Screens::LoadingScreen::loadingBarsMutex);

	if (HPCM::Screens::LoadingScreen::loadingBars.empty()) {
		if (ttfFont.has_value()) {
			if (fontThread.get_id() == std::thread::id()) {
				fontThread = std::thread([]() {
					std::lock_guard fontLock(fontMutex);

					TTF_CloseFont(ttfFont.value());
					ttfFont.reset();

					fontThread.detach();
					});
			}
			// NOTE: Code path here is intentional - if there's a thread currently running, we'll let it finish it's thing before unloading the font.
		}
	} else {
		if (fontMutex.try_lock()) {
			if (!ttfFont.has_value()) {
				fontThread = std::thread([]() {
					std::lock_guard fontLock(fontMutex);

					ttfFont = TTF_OpenFont((CellMachine::ApplicationContext::basePathString + "/Resources/Fonts/ProggyClean.ttf").data(), 280);

					if (*ttfFont == NULL) {
						throw std::runtime_error(TTF_GetError());
					}

					fontThread.detach();
					});
			}

			// try_lock does lock the resource. even if the above condition fails, we still want to use the resource & prevent the same thread locking
			// a non-recursive mutx. if this code is reached, we know we have the lock so we release it here.
			fontMutex.unlock();
		}

		if (fontMutex.try_lock()) {
			if (ttfFont.has_value()) {
				SDL_Surface *textSurface = TTF_RenderUTF8_Shaded(ttfFont.value(), "test", {255, 255, 255}, {0, 0, 0});

				if (textSurface == NULL) {
					printf("%s", TTF_GetError());
				}

				SDL_Texture *textTexture = SDL_CreateTextureFromSurface(CellMachine::Interface::sdlRenderer, textSurface);

				if (textTexture == NULL) {
					printf("%s", SDL_GetError());
				}



				int t = SDL_RenderCopy(CellMachine::Interface::sdlRenderer, textTexture, NULL, NULL);

				if (t != 0) {
					printf("%s", SDL_GetError());
				}

				SDL_DestroyTexture(textTexture);
				SDL_FreeSurface(textSurface);
			}

			fontMutex.unlock();
		}
	}
}