#include <Game.h>
#include <SDL_Error.h>
#include <SDL2/SDL.h>
#include <thread>
#include <iostream>

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
	throwSDL_Error();
    }

    // get display index
    int display_idx {SDL_GetWindowDisplayIndex(gme->win)};

    if (-1 == display_idx)
    {
        throwSDL_Error();
    }
    SDL_Log("Retrieved Display index");

    // get display bounds
    SDL_Rect rect {};

    if (-1 == SDL_GetDisplayUsableBounds(display_idx, &rect))
    {
    	throwSDL_Error();
    }
    SDL_Log("Retrieved display bounds");

    // resize window
    SDL_SetWindowSize(gme->win, rect.w, rect.h);
    SDL_Log("Resized Window");

    // Get surface
    if (NULL == (SDL_GetWindowSurface(gme->win)))
    {
        throwSDL_Error();
    }
    SDL_Log("Retrieved Surface");

    // refresh window surface
    if (-1 == SDL_UpdateWindowSurface(gme->win))
    {
        throwSDL_Error();
    }
    SDL_Log("Updated Surface");

    // create 2D renderer
    if (NULL == (gme->rend =
        SDL_CreateRenderer(gme->win, display_idx, SDL_RENDERER_TARGETTEXTURE)))
    {
        throwSDL_Error();
    }
    SDL_Log("Created Renderer");
}

void play (Game* gme)
{
    int size_w {};
    int size_h {};

    float scale_x  {};
    float scale_y  {};

    // set integer scale
    if (0 > SDL_RenderSetIntegerScale(gme->rend, SDL_TRUE))
    {
        throwSDL_Error();
    }

    // get init scale
    SDL_RenderGetScale(gme->rend, &scale_x, &scale_y);
    SDL_Log("Scale %f x %f", scale_x, scale_y);

    // set window dimensions
    SDL_GetWindowSize(gme->win, &size_w, &size_h);
    SDL_Log("Dimensions %d x %d", size_w, size_h);

    // init minimap borders
    int y {static_cast<int>(size_h * 0.55)};
    int d {size_h - y};

    gme->map->y = y;
    gme->map->h = d;
    gme->map->w = d;

    // init player pos
    gme->ply->x = gme->map->x + static_cast<int>(gme->map->w / 2);
    gme->ply->y = gme->map->y + static_cast<int>(gme->map->h / 2);

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

        // set minimap color
        if(0 > SDL_SetRenderDrawColor(gme->rend, 255, 255, 255, 255))
        {
       		throwSDL_Error(); 
        }

        // draw minimap
        if(0 > SDL_RenderDrawRect(gme->rend, gme->map))
        {
        	throwSDL_Error();
        }

        // draw player
        if(0 > SDL_RenderSetScale(gme->rend, scale_x * 1.1f, scale_y * 1.1f)
            || 0 > SDL_RenderDrawPoint(gme->rend, gme->ply->x, gme->ply->y)
            || 0 > SDL_RenderSetScale(gme->rend, scale_x, scale_y))
        {
        	throwSDL_Error();
        }

        // unset minimap color
        if(0 > SDL_SetRenderDrawColor(gme->rend, 0, 0, 0, 255))
        {
			throwSDL_Error();
        }

        // refresh screen
        SDL_RenderPresent(gme->rend);
        SDL_Delay(100);

        if (0 > SDL_RenderClear(gme->rend))
        {
			throwSDL_Error();
        }
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
