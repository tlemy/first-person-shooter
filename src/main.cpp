#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <thread>
#include <chrono>

#define TITLE "FPS Game"

using namespace std::chrono_literals;

typedef struct Game 
{
    SDL_Window *win;
    SDL_Surface *surf;
    int displayIdx;
} Game;

void init(Game* gme);
void play(Game* gme);
void quit(SDL_Window *win);

int main(void) 
{
    Game gme {NULL, NULL, -1};
    
    try
    {
        init(&gme);
        play(&gme);
    }
    catch(const std::exception& e)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s", e.what());
        if (gme.win != NULL) 
        {
            quit(gme.win);
            return -1;
        }
        return -1;
    }       
    return 0;
}

void init(Game* gme) 
{
    // init SDL library;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Log("Initialized SDL");

    // create window
    gme->win = SDL_CreateWindow(
        TITLE, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        0, 0, 
        SDL_WINDOW_RESIZABLE);
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
    SDL_Rect rect;
    
    if (-1 == SDL_GetDisplayUsableBounds(gme->displayIdx, &rect))
    {
        throw SDL_GetError();
    }
    SDL_Log("Retrieved display bounds");

    // resize window
    SDL_SetWindowSize(gme->win, rect.w, rect.h);
    SDL_Log("Resized Window");

    // create surface
    if (NULL == (gme->surf = SDL_GetWindowSurface(gme->win))) 
    {
        throw SDL_GetError();
    }
    SDL_Log("Created Surface");

    // refresh window surface
    if (-1 == SDL_UpdateWindowSurface(gme->win))
    {
        throw SDL_GetError();
    }
    SDL_Log("Updated Window");   
}

void play(Game* gme) 
{
    while (1)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event)) 
        {
            if (SDL_QUIT == event.type) 
            {

                quit(gme->win);
                SDL_Log("Closed Window");
                return;
            }
        }
        std::this_thread::sleep_for(100ms); // TODO search for alternatives
    } 
}

void quit(SDL_Window *win) 
{
    SDL_DestroyWindow(win);
    SDL_Quit();
}

