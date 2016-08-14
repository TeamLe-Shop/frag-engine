#pragma once

#include <SDL.h>
#include <string>

namespace frag {

extern "C" {
	SDL_Window* CreateWindow(std::string title, int width, int height);
	void DestroyWindow(SDL_Window* window);
	void Error(std::string format, ...);
	void AppLoop();
}

}