#include <SDLpp/Lib.hpp>
#include <SDL.h>

namespace SDLpp
{
	Lib::Lib()
	{
		SDL_Init(0);
	}

	Lib::~Lib()
	{
		SDL_Quit();
	}

	bool Lib::PollEvent(SDL_Event* event)
	{
		return SDL_PollEvent(event) > 0;
	}
}