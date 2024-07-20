#include <SDL.h>
#include <SDL_render.h>
#include <SDL_video.h>

namespace CellMachine {
	namespace Interface {
		extern SDL_Window *sdlWindow;
		extern SDL_Renderer *sdlRenderer;

		void createWindow();
		void destroyWindow();

		void updateWindow();
		void updateRenderer();

		void createRenderer();
		void destroyRenderer();
	}
}