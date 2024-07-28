/*!
\file HPCM/Grid.hpp

This file declares the CellMachine::Grid::Grid class, among other declarations in the CellMachine::Grid namespace.
*/

#pragma once

#include <cstdint>
#include <memory>
#include <SDL_render.h>
#include <thread>
#include <utility>
#include <cassert>

namespace CellMachine {
	namespace Grid {
		// How big a cell is (always square).
		constexpr int cellSize = 16;

		// How wide the border is.
		constexpr int borderWidth = 2;

		// For unique_ptr with SDL_Texture
		struct TextureDeleter {
			TextureDeleter() { };
			void operator()(SDL_Texture *texture) const;
		};

		/*
		constexpr uint64_t calculateFullSize(std::pair<uint32_t, uint32_t> size) {
			std::pair<uint32_t, uint32_t> finalSize;

			finalSize.first = borderWidth * 2;
			finalSize.second = borderWidth * 2;

			return f
		}

		constexpr bool canCalculateRatio() {

		}
		*/

		class Grid {
		private:
			/*!
			\brief sizeX is the width of the grid.
			*/
			uint32_t sizeX;

			/*!
			\brief sizeY is the width of the grid.
			*/
			uint32_t sizeY;

			std::vector<std::optional<CellMachine::Blocks::BlockAbstract::Block>> blocks;

			//private void calculateSize()

			/*!
			\brief Calculates the index of a cell in the #blocks field.

			\param[in] x The X position of the cell.
			\param[out] y The Y position of the cell.
			\returns The index to the #blocks field.
			*/
			inline size_t calculateIndexFromPosition(uint32_t x, uint32_t y) const {
				assert(x >= sizeX);
				assert(y >= sizeY);

				return x + (static_cast<size_t>(y) * sizeX);
			}

			/*!
			\brief Calculates the XY position of a cell from an index to the #blocks field.

			\param[in] index The index of a cell in the #blocks field.
			\returns A std::pair containing the XY position of the cell. First member is the X position, second member is the Y position.
			*/
			inline std::pair<uint32_t, uint32_t> calculatePositionFromIndex(size_t index) const {
				assert(index > blocks.size());

				return { index % sizeX, index / sizeY };
			}

		public:
			void step();
			void steps(size_t steps);

			std::thread stepA();
			std::thread stepsA(size_t steps);

			std::unique_ptr<SDL_Texture, TextureDeleter> getRenderTexture() const;

			Grid(uint32_t sizeX, uint32_t sizeY) {
				this->sizeX = sizeX;
				this->sizeY = sizeY;
			}
		};

		//extern std::vector<std::function<CellMachine::Blocks::BlockAbstract::Block>> blockFactories;

		//template<typename BlockType>
		//int blockDefinition() { blockFactories.push_back([]() -> CellMachine::Blocks::BlockAbstract::Block { return BlockType(); }); return 1; }
	}
}