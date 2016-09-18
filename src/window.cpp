#include "window.hpp"

#include "fragengine.hpp"

#include <gl.h>
#include <SDL.h>

namespace frag {

Window::Window(std::string title, uint16_t width, uint16_t height, GLVersion gl)
{
    SDL_Window* sdlwindow;
    
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        error("Failed to initialise SDL: %s", SDL_GetError());
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl.minor);

    sdlwindow = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height,
                                 SDL_WINDOW_OPENGL);
    
    if (sdlwindow == NULL) {
        error("Failed to create window: %s", SDL_GetError());
    }
    
    glcontext = SDL_GL_CreateContext(sdlwindow);
}

Window::~Window()
{
    destroyWindow();
    SDL_Quit();
}

void Window::initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
}

void Window::destroyWindow()
{
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(sdlwindow);
    SDL_Quit();
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::present()
{
    SDL_GL_SwapWindow(sdlwindow);
}

}
