#pragma once

#include <functional>
#include <optional>

union SDL_Event;

class ChessGame;

class Player
{
	public:
		Player(ChessGame& game, std::size_t playerIndex);
		Player(const Player&) = delete;
		Player(Player&&) = default;
		~Player() = default;

		void HandleEvent(const SDL_Event& event);

		void StartTurn();

		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = default;

	private:
		struct SelectedPiece
		{
			std::size_t x;
			std::size_t y;
		};

		ChessGame& m_game;
		std::optional<SelectedPiece> m_selectedPiece;
		std::size_t m_playerIndex;
};
