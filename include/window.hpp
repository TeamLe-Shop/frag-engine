#pragma once

#include <stdint.h>
#include <SDL.h>
#include <gl.h>

#include "fragengine.hpp"
#include <string>

namespace frag {

class Window {
public:
    /* Creates a new Window object.
     *
     * title - Name of the window
     * width - Width of the window in pixels
     * height - Height of the window in pixels
     * gl - OpenGL version.
     */
    Window(std::string title, uint16_t width, uint16_t height,
           GLVersion gl);
    ~Window();
    /* Initialise OpenGL. */
    void initGL();
    /* Destroy the window. */
    void destroyWindow();
    /* Clear the screen. */
    void clear();
    /* Draw everything on the window buffer to the screen. */
    void present();
    
private:
    SDL_Window* sdlwindow;
    SDL_GLContext glcontext;
    uint16_t width;
    uint16_t height;
    
public:
    uint8_t fps_max = 60;
};

}