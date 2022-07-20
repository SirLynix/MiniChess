#include <iostream>
#include <SDLpp/Lib.hpp>
#include <SDLpp/Window.hpp>
#include <SDL.h>

int main(int argc, char** argv)
{
	try
	{
		SDLpp::Lib sdl;

		SDLpp::Window window("ChessGame", 1280, 720);
		SDLpp::Renderer renderer = window.CreateRenderer();

		bool opened = true;
		while (opened)
		{
			SDL_Event event;
			while (sdl.PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT:
						opened = false;
						break;
				}
			}

			renderer.SetDrawColor(128, 128, 255, 255);
			renderer.Clear();
			renderer.Present();
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 0;
	}
}
