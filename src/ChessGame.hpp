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

		const Board& GetBoard() const;
		const BoardDrawer& GetBoardDrawer() const;

		int Run();

		ChessGame& operator=(const ChessGame&) = delete;
		ChessGame& operator=(ChessGame&&) = delete;

		static constexpr std::size_t PlayerCount = 2;

	private:
		bool MovePiece(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY);

		void NextTurn();

		SDLpp::Lib& m_sdl;
		SDLpp::Window m_window;
		SDLpp::Renderer m_renderer;
		std::vector<Player> m_players;
		Resources m_resources;
		Board m_board;
		std::optional<BoardDrawer> m_boardDrawer;
		std::size_t m_currentPlayer;
};
