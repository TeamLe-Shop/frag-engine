#include "fragengine.hpp"

#include <SDL.h>
#include "gl.h"
#include "glu.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

namespace frag {

void error(std::string format, ...) {
    va_list args; // Anyone know of a C++ specific way to do this?
    va_start(args, format);
    printf("[FragEngine Error]: ");
    vprintf(format.data(), args);
    printf("\n");
    
    va_end(args);
}

}