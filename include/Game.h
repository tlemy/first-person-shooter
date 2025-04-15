#ifndef _Game_
#define _Game_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FPS
{
    typedef struct Game
    {
        GLFWwindow* win;
    } Game;

    void init(Game* gme);
    // void play(Game* gme);
    void quit(Game* gme);
}
#endif
