#include <stdexcept>

namespace FPS
{

class SDL_Error : public std::runtime_error
{
public:
	SDL_Error(const char* err) : std::runtime_error(err) {}
};

void throwSDL_Error ();

}
