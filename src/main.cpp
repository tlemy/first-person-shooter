#include <Game.h>
#include <exception>
#include <iostream>

int main(void)
{
    FPS::Game gme {NULL};
	
	try
    {
        FPS::init(&gme);

        while (!glfwWindowShouldClose(gme.win))
        {
            glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(gme.win);

			glfwPollEvents();
        }

		glfwDestroyWindow(gme.win);
		FPS::quit(&gme);
    }
    catch(const std::exception& e)
    {
    	FPS::quit(&gme);
		
		std::cout << e.what() << std::endl;	
		
        return -1;
    }
	
    return 0;
}

