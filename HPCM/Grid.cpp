#include "Blocks/BlockAbstract.hpp"
#include "Grid.hpp"
#include "Interface.hpp"
#include <cassert>
#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <optional>
#include <SDL_error.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

void CellMachine::Grid::Grid::step() {
	//std::vector<std::vector<CellMachine::Blocks::BlockAbstract::Block>> blocksToProcess {};

	//for (auto &block : blocks) {
	//	if (!block)
	//		continue;
		/*
		class MyClass : public CellMachine::Blocks::BlockAbstract::Block {
		public:
			
			size_t getPriority() { return 5; }

			void act(CellMachine::Gird::Grid &gird) { }

			uint32_t getColour() { return 0x505050FF; }

		private:

		};

		MyClass MCT = MyClass();

		CellMachine::Blocks::BlockAbstract::Block* test = static_cast< CellMachine::Blocks::BlockAbstract::Block* >(&MCT);

		test.act;
		*/
	//}
}

void CellMachine::Grid::Grid::steps(size_t steps) {
	for (size_t i = 0; i < steps; i++) {
		Grid::step();
	}
}

std::thread CellMachine::Grid::Grid::stepA() {
	return std::thread(&Grid::step, *this);
}

std::thread CellMachine::Grid::Grid::stepsA(size_t steps) {
	return std::thread(&Grid::steps, *this, steps);
}

std::unique_ptr<SDL_Texture, CellMachine::Grid::TextureDeleter> CellMachine::Grid::Grid::getRenderTexture() const {
	assert(sizeX != 0);
	assert(sizeY != 0);

	std::unique_ptr<SDL_Texture, TextureDeleter> sdlTexture {};

	std::pair<uint32_t, uint32_t> textureSize {
		borderWidth*2 + cellSize * sizeX + borderWidth * (sizeX - 1),
		borderWidth*2 + cellSize * sizeY + borderWidth * (sizeY - 1)
	};

	{
		SDL_RendererInfo rendererInfo {};

		if (SDL_GetRendererInfo(CellMachine::Interface::sdlRenderer, &rendererInfo)) {
			throw std::runtime_error((std::string("Call to SDL_GetRendererInfo failed: ") + SDL_GetError()));
		}

		sdlTexture = std::unique_ptr<SDL_Texture, TextureDeleter>(
			SDL_CreateTexture(
			CellMachine::Interface::sdlRenderer,
			rendererInfo.texture_formats[0],
			SDL_TEXTUREACCESS_TARGET,
			textureSize.first,
			textureSize.second
		));
	}

	SDL_SetRenderTarget(CellMachine::Interface::sdlRenderer, sdlTexture.get());

	SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(CellMachine::Interface::sdlRenderer);

	SDL_SetRenderDrawColor(CellMachine::Interface::sdlRenderer, 50, 50, 50, SDL_ALPHA_OPAQUE );
	{
		SDL_Rect rect { 0, 0, textureSize.first, borderWidth };
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}
	{
		SDL_Rect rect {0, 0, borderWidth, textureSize.second};
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}
	{
		SDL_Rect rect {0, textureSize.first - borderWidth, textureSize.first, borderWidth};
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}
	{
		SDL_Rect rect {textureSize.first - borderWidth, 0, borderWidth, textureSize.second};
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}

	for (size_t i = 1; i < static_cast<size_t>(sizeX); i++) {
		SDL_Rect rect {borderWidth * i + cellSize * i, borderWidth, borderWidth, textureSize.first - borderWidth};
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}
	for (size_t i = 1; i < static_cast< size_t >(sizeY); i++) {
		SDL_Rect rect {borderWidth, borderWidth * i + cellSize * i, textureSize.first - borderWidth, borderWidth};
		SDL_RenderFillRect(CellMachine::Interface::sdlRenderer, &rect);
	}

	SDL_SetRenderTarget(CellMachine::Interface::sdlRenderer, NULL);

	return sdlTexture;
}

//std::vector<std::function<CellMachine::Blocks::BlockAbstract::Block>> CellMachine::Grid::blockFactories;

void CellMachine::Grid::TextureDeleter::operator()(SDL_Texture *texture) const {
	SDL_DestroyTexture(texture);
}
