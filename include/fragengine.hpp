#pragma once

#include <SDL.h>
#include <string>

namespace frag {

struct GLVersion {
    uint8_t major;
    uint8_t minor;
};

void error(std::string format, ...);

}