/// @file
/// @brief FragEngine header, contains general constants & types

#pragma once

#include <glew.h>
#include <SDL.h>
#include <string>

namespace frag {

#define FRAG_LOGLEVEL DEVELOPER

/// Struct representing OpenGL version.
struct GLVersion {
    uint8_t major;
    uint8_t minor;
};

/// Message type for the logging function. Constants are defined for the 4
/// default types.
struct LogLevel {
    int numeric;
    std::string name;
};

const LogLevel DEVELOPER {0, "Developer"};
const LogLevel INFO      {1, "Info"};
const LogLevel WARNING   {2, "Warning"};
const LogLevel SEVERE    {3, "Severe"};

/// Log a message
///
/// level - Message type: Developer -> Info -> Warning -> Severe.
///         Message must be at least FRAG_LOGLEVEL to be logged.
///
/// format - Format string
void log(LogLevel level, std::string format, ...);

}
