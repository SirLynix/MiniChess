#include <BoardDrawer.hpp>
#include <ChessGame.hpp>
#include <Player.hpp>
#include <SDL.h>
#include <cassert>

Player::Player(ChessGame& game, std::size_t playerIndex) :
m_game(game),
m_playerIndex(playerIndex)
{
}

void Player::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			const Board& board = m_game.GetBoard();
			const BoardDrawer& boardDrawer = m_game.GetBoardDrawer();
			std::size_t cellX, cellY;
			if (boardDrawer.GetHoveringPiece(event.button.x, event.button.y, cellX, cellY))
			{
				if (!m_selectedPiece)
				{
					if (const Board::CellContent* content = board.GetCell(cellX, cellY))
					{
						if (content->ownerIndex == m_playerIndex)
							m_selectedPiece = SelectedPiece{ cellX, cellY };
					}
				}
				else
				{
					const SelectedPiece& selectedPiece = *m_selectedPiece;
					if (selectedPiece.x == cellX && selectedPiece.y == cellY)
						m_selectedPiece.reset(); //< unselect
					else
					{
						assert(m_moveCallback);
						if (m_moveCallback(selectedPiece.x, selectedPiece.y, cellX, cellY))
							m_selectedPiece.reset();
					}
				}
			}
			break;
		}
	}
}

void Player::StartTurn(MoveCallback moveCallback)
{
	assert(!m_selectedPiece.has_value());

	m_moveCallback = std::move(moveCallback);
}
