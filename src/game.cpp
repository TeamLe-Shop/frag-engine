#include "game.hpp"

namespace frag {

Game::Game(Window* w) : window(w)
{

}

Game::~Game()
{

}

bool Game::cycle()
{
    SDL_Event e;

    int frame_start_time = SDL_GetTicks();
    
    window->clear();
    if (state != nullptr) { state->render(); }
    
    int sleeptime = (1000 / window->fps_max) - (SDL_GetTicks() - frame_start_time);
    if (SDL_GetTicks() - frame_start_time < 1000.0 / window->fps_max) {
        SDL_Delay(sleeptime);
    }
    
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
    }
    
    if (state != nullptr) { state->input(e); }
    window->present();
     
    return true;
}

}