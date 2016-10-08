#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>

namespace frag {

#define FRAG_LOGLEVEL DEVELOPER

struct GLVersion {
    uint8_t major;
    uint8_t minor;
};

struct LogLevel {
    int numeric;
    std::string name;
};

const LogLevel DEVELOPER {0, "Developer"};
const LogLevel INFO      {1, "Info"};
const LogLevel WARNING   {2, "Warning"};
const LogLevel SEVERE    {3, "Severe"};

void log(LogLevel level, std::string format, ...);

}
