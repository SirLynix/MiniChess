#include <ChessGame.hpp>
#include <SDLpp/Lib.hpp>
#include <SDL.h>

ChessGame::ChessGame(SDLpp::Lib& sdl) :
m_sdl(sdl)
{
	constexpr int WindowWidth = 1280;
	constexpr int WindowHeight = 720;

	m_window = SDLpp::Window("ChessGame", WindowWidth, WindowHeight);
	m_renderer = m_window.CreateRenderer();

	m_players.emplace_back();
	m_players.emplace_back();

	m_resources = Resources::Load(m_renderer);
	m_boardDrawer.emplace(m_resources, WindowWidth, WindowHeight);
}

int ChessGame::Run()
{
	bool opened = true;
	while (opened)
	{
		SDL_Event event;
		while (m_sdl.PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					opened = false;
					break;
			}
		}

		m_renderer.SetDrawColor(128, 128, 255, 255);
		m_renderer.Clear();
		
		m_boardDrawer->Draw(m_renderer, m_board);

		m_renderer.Present();
	}
	return 0;
}
