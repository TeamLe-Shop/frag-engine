#include "fragengine.hpp"

#include <SDL.h>
#include <glu.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

namespace frag {

void log(LogLevel level, std::string format, ...) {
    if (FRAG_LOGLEVEL.numeric > level.numeric) { return; }

    va_list args; // Anyone know of a C++ specific way to do this?
    va_start(args, format);
    printf("[FragEngine %s]: ", level.name.c_str());
    vprintf(format.data(), args);
    printf("\n");

    va_end(args);
}

}
