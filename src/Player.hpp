#pragma once

#include <functional>
#include <optional>

union SDL_Event;

class ChessGame;

class Player
{
	public:
		using MoveCallback = std::function<bool(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY)>;

		Player(ChessGame& game, std::size_t playerIndex);
		Player(const Player&) = delete;
		Player(Player&&) = default;
		~Player() = default;

		void HandleEvent(const SDL_Event& event);

		void StartTurn(MoveCallback callback);

		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = default;

	private:
		struct SelectedPiece
		{
			std::size_t x;
			std::size_t y;
		};

		ChessGame& m_game;
		MoveCallback m_moveCallback;
		std::optional<SelectedPiece> m_selectedPiece;
		std::size_t m_playerIndex;
};
