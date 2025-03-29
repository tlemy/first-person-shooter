#pragma once

#include <SDL2/SDL.h>

namespace FPS
{
    typedef struct Player
    {
        int x;
        int y;
    } Player;

    typedef struct Game
    {
        SDL_Window* win;
        SDL_Renderer* rend;
        SDL_Rect* map;
        SDL_Rect* ply;
    } Game;

    void init(Game* gme);
    void play(Game* gme);
    void quit(Game* gme);
}