#include <cstdint>
#include <functional>
#include <map>
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "../Grid.hpp"
#include <SDL_render.h>
#include <SDL_rect.h>
#include <array>
#include <SDL_pixels.h>

namespace CellMachine {
	namespace Blocks {
		namespace BlockAbstract {
			class Block {
			public:
				/*!
				\brief This should be constant.
				*/
				virtual size_t getPriority() = 0;
				
				/*!
				\brief Called when an object is to act. You should modify the grid here.
				*/
				//virtual void act(CellMachine::Grid::Grid grid) = 0;

				/*!
				\brief Called when an object is to render it's cell.

				\param[in] sdlRenderer An SDL_Renderer. No preparation is required to use the render, you can just start rendering.
				*/
				virtual void render(SDL_Renderer *sdlRenderer, SDL_Point sdlPoint) {
					{
						SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
						std::array<SDL_Rect, 2> rectArray {{ {0, 0, sdlPoint.x / 2, sdlPoint.y / 2}, {sdlPoint.x / 2, sdlPoint.y / 2, sdlPoint.x / 2, sdlPoint.y / 2} }};
						SDL_RenderFillRects(sdlRenderer, rectArray.data(), 2);
					}
					{
						SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
						std::array<SDL_Rect, 2> rectArray {{ {sdlPoint.x / 2, 0, sdlPoint.x / 2, sdlPoint.y / 2}, {0, sdlPoint.y / 2, sdlPoint.x / 2, sdlPoint.y / 2} }};
						SDL_RenderFillRects(sdlRenderer, rectArray.data(), 2);
					}
				};
			};

			//const std::map<std::string, std::function<>> blockFactories {};

		//#define DECLARE_BLOCK(blockId, blockClass) CellMachine::Blocks::BlockAbstract::blockFactories[blockId] = []() -> CellMachine::Blocks::BlockAbstract::Block {return std::make_unique(new blockClass {})};
		}
	}
}