#pragma once

#include "window.hpp"
#include "state.hpp"

namespace frag {

class State;

class Game {
public:
    Game(Window* w);
    ~Game();
    bool cycle();
    
private:
    State* state = nullptr;
    Window* window;
};

}