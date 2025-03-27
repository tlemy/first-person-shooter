#include <Game.h>
#include <thread>
#include <iostream>
#include <SDL2/SDL.h>

namespace FPS
{
void init(Game* gme)
{
    // init SDL library;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Log("Initialized SDL");

    // create window
    gme->win = SDL_CreateWindow(
        "FPS Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        0, 0,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_Log("Created Window");

    if (NULL == gme->win)
    {
        throw SDL_GetError();
    }

    // get display index
    gme->displayIdx = SDL_GetWindowDisplayIndex(gme->win);

    if (-1 == gme->displayIdx)
    {
        throw SDL_GetError();
    }
    SDL_Log("Retrieved Display index");

    // get display bounds
    SDL_Rect rect {};

    if (-1 == SDL_GetDisplayUsableBounds(gme->displayIdx, &rect))
    {
        throw SDL_GetError();
    }
    SDL_Log("Retrieved display bounds");

    // resize window
    SDL_SetWindowSize(gme->win, rect.w, rect.h);
    SDL_Log("Resized Window");

    // GET surface
    if (NULL == (gme->surf = SDL_GetWindowSurface(gme->win)))
    {
        throw SDL_GetError();
    }
    SDL_Log("Got Surface");

    // refresh window surface
    if (-1 == SDL_UpdateWindowSurface(gme->win))
    {
        throw SDL_GetError();
    }
    SDL_Log("Updated Surface");

    // create 2D renderer
    if (NULL == (gme->rend =
        SDL_CreateRenderer(gme->win, gme->displayIdx, SDL_RENDERER_TARGETTEXTURE)))
    {
        throw SDL_GetError();
    }
    SDL_Log("Created Renderer");
}

void play(Game* gme)
{
    while (1)
    {
        SDL_Event event {};

        while (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
            {

                quit(gme);
                SDL_Log("Quit Game");
                return;
            }
        }

        const SDL_Rect square {0, 0, 100, 100};

        SDL_RenderClear(gme->rend);
        SDL_SetRenderDrawColor(gme->rend, 255, 255, 255, 255);
        SDL_RenderDrawRect(gme->rend, &square);
        SDL_SetRenderDrawColor(gme->rend, 0, 0, 0, 255);
        SDL_RenderPresent(gme->rend);
        SDL_Delay(100);
    }
}

void quit(Game* gme)
{
    if (gme->win)
    {
        SDL_DestroyWindow(gme->win);
    }

    if (gme->rend)
    {
        SDL_DestroyRenderer(gme->rend);
    }

    SDL_Quit();
}
}