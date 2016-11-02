/// @file
/// @brief State

#pragma once

#include "window.hpp"
#include "game.hpp"

namespace frag {

class Game;

/// The functionality of states are to be defined by the user.
///
/// Render and input functions are called each game cycle if they are the active
/// state.
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
