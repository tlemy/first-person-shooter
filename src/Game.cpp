#include <Game.h>
#include <InitException.h>
#include <iostream>

namespace FPS
{
    void init(Game* gme)
    {
        const char** errorMsg;
    
        if (GLFW_TRUE != glfwInit() && GLFW_NO_ERROR != glfwGetError(errorMsg))
        {
            throw InitException(*errorMsg);
        }

        if (!(gme->win = glfwCreateWindow(1920, 1080, "FPS", NULL, NULL))
            && GLFW_NO_ERROR != glfwGetError(errorMsg))
        {
            throw InitException(*errorMsg);
        }
		
        glfwMakeContextCurrent(gme->win);
		
		if (0 == gladLoadGL()) 
		{
			const char msg[] = "Could not load Glad";
			throw InitException(msg);
		}
    }

     void quit(Game* gme)
     {
     	glfwTerminate(); 
     }
}
