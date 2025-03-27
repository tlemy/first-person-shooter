#include <Game.h>
#include <exception>

int main(void)
{
    FPS::Game gme {NULL, NULL, NULL, -1};

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
