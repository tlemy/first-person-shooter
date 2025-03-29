#include <Game.h>
#include <exception>

int main(void)
{
    SDL_Rect map {};
    SDL_Rect ply {};
    FPS::Game gme {NULL, NULL, &map, &ply};

    try
    {
        FPS::init(&gme);
        FPS::play(&gme);
    }
    catch(const std::exception& e)
    {
        SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s", e.what());

        FPS::quit(&gme);

        return -1;
    }
    return 0;
}
