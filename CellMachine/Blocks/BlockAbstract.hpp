#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "../Grid.hpp"

namespace CellMachine {
	namespace Blocks {
		namespace BlockAbstract {
			class Block {
				/*!
				\brief This should be constant.
				*/
				virtual intmax_t getPriority() = 0;
				
				/*!
				\brief Called when an object is to act. You should modify the grid here.
				*/
				virtual void act(CellMachine::Gird::Grid& gird) = 0;

				/*!
				\brief RGBA colour (R, G, B, A, all 8 bits) of the block.
				*/
				virtual uint32_t getColour();
			};

			//const std::map<std::string, std::function<>> blockFactories {};

		//#define DECLARE_BLOCK(blockId, blockClass) CellMachine::Blocks::BlockAbstract::blockFactories[blockId] = []() -> CellMachine::Blocks::BlockAbstract::Block {return std::make_unique(new blockClass {})};
		}
	}
}