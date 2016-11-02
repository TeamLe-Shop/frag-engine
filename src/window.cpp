#include "window.hpp"

#include "fragengine.hpp"

#include <glew.h>
#include <SDL.h>

namespace frag {

Window::Window(std::string title, uint16_t width, uint16_t height, GLVersion gl)
{
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        log(SEVERE, "Failed to initialise SDL: %s", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, gl.major);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, gl.minor);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    sdlwindow = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, width, height,
                                 SDL_WINDOW_OPENGL);

    if (sdlwindow == NULL) {
        log(SEVERE, "Failed to create window: %s", SDL_GetError());
    }

    glcontext = SDL_GL_CreateContext(sdlwindow);

    glewExperimental = GL_TRUE;
    glewInit();

    log(INFO, "Window created, OpenGL version: %u.%u", gl.major, gl.minor);
}

Window::~Window()
{
    destroyWindow();
    SDL_Quit();
}

void Window::destroyWindow()
{
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(sdlwindow);
    SDL_Quit();
    log(INFO, "Quit SDL");
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
