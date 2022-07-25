#pragma once

#include <SDLpp/Renderer.hpp>
#include <SDLpp/Texture.hpp>
#include <SDLpp/Window.hpp>
#include <Board.hpp>
#include <BoardDrawer.hpp>
#include <Player.hpp>
#include <Resources.hpp>
#include <optional>
#include <vector>

namespace SDLpp
{
	class Lib;
}

class ChessGame
{
	public:
		ChessGame(SDLpp::Lib& sdl);
		ChessGame(const ChessGame&) = delete;
		ChessGame(ChessGame&&) = delete;
		~ChessGame() = default;

		int Run();

		ChessGame& operator=(const ChessGame&) = delete;
		ChessGame& operator=(ChessGame&&) = delete;

	private:
		SDLpp::Lib& m_sdl;
		SDLpp::Window m_window;
		SDLpp::Renderer m_renderer;
		std::vector<Player> m_players;
		Resources m_resources;
		Board m_board;
		std::optional<BoardDrawer> m_boardDrawer;
};
