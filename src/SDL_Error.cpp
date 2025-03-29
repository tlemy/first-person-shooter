#include <SDL_Error.h>
#include <SDL2/SDL.h>

namespace FPS 
{

void throwSDL_Error ()
{
	throw SDL_Error(SDL_GetError());
}

}
