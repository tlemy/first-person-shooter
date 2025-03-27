#pragma once

#include <SDL2/SDL.h>

namespace FPS
{
    typedef struct Game
    {
        SDL_Window* win;
        SDL_Surface* surf;
        SDL_Renderer* rend;
        int displayIdx;
    } Game;

    void init(Game* gme);
    void play(Game* gme);
    void quit(Game* gme);
}