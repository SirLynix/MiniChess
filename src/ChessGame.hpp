#pragma once

#include <SDLpp/Renderer.hpp>
#include <SDLpp/Texture.hpp>
#include <SDLpp/Window.hpp>
#include <MovementRules/MovementRule.hpp>
#include <Board.hpp>
#include <BoardDrawer.hpp>
#include <Player.hpp>
#include <PieceType.hpp>
#include <Resources.hpp>
#include <array>
#include <optional>
#include <vector>

namespace SDLpp
{
	class Lib;
}

class ChessGame
{
	friend class Player;

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

		static constexpr std::size_t BlackPlayerIndex = 1;
		static constexpr std::size_t PlayerCount = 2;
		static constexpr std::size_t WhitePlayerIndex = 0;

	private:
		bool CheckMovement(PieceType pieceType, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const;

		void InitMovementRules();

		bool MovePiece(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY);

		void NextTurn();

		void NotifyPieceDeselection();
		void NotifyPieceSelection(std::size_t cellX, std::size_t cellY);

		SDLpp::Lib& m_sdl;
		SDLpp::Window m_window;
		SDLpp::Renderer m_renderer;
		std::vector<Player> m_players;
		Resources m_resources;
		Board m_board;
		std::optional<BoardDrawer> m_boardDrawer;
		std::size_t m_currentPlayer;
		std::array<std::vector<std::unique_ptr<MovementRule>>, PieceCount> m_movementRules;
};
