#include <iostream>
#include <SDLpp/Lib.hpp>
#include <ChessGame.hpp>

int main(int argc, char** argv)
{
	try
	{
		SDLpp::Lib sdl;
		ChessGame game(sdl);
		return game.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 0;
	}
}
