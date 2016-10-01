#pragma once

#include "window.hpp"
#include "game.hpp"

namespace frag {

class Game;

class State {
public:
    State(Game game);
    ~State();

    virtual void render();
    virtual void input(SDL_Event event);

private:
    Game* game;
};

}
