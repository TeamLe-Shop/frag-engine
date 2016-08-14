#include "fragengine.hpp"

#include <SDL.h>
#include <stdio.h>
#include <stdarg.h>

namespace frag {

SDL_Window* CreateWindow(std::string title, int width, int height)
{
	SDL_Window* window;
	
	if (SDL_Init(SDL_INIT_VIDEO)) {
		Error("Failed to initialise SDL: %s", SDL_GetError());
	}
	
	window = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED,
							  SDL_WINDOWPOS_CENTERED, width, height,
							  SDL_WINDOW_SHOWN |
							  SDL_WINDOW_OPENGL);
	
	if (window == NULL) {
		Error("Failed to create window: %s", SDL_GetError());
		return NULL;
	}
	
	InitGL();
	
	return window;
}

void AppLoop()
{
    bool quit = false;
    SDL_Event e;
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}

void DestroyWindow(SDL_Window* window)
{
	SDL_DestroyWindow(window);
	
    SDL_Quit();
}

void Error(std::string format, ...) {
	va_list args; // Anyone know of a C++ specific way to do this?
	va_start(args, format);
	printf("[FragEngine Error]: ");
	vprintf(format.data(), args);
	printf("\n");
	
	va_end(args);
}

}