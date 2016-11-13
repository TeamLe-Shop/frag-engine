/// @file

#pragma once

#include "window.hpp"
#include "state.hpp"

namespace frag {

class State;

class Game {
public:
    Game(Window* w);
    ~Game();
    /// Do one cycle of rendering and game logic. This function also attempts to
    /// regulate FPS
    bool cycle();

public:
    State* state = nullptr;
    Window* window;
};

}
