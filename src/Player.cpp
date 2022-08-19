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
			if (boardDrawer.GetHoveringCell(event.button.x, event.button.y, cellX, cellY))
			{
				if (const Board::CellContent* content = board.GetCell(cellX, cellY))
				{
					if (content->ownerIndex == m_playerIndex)
					{
						if (m_selectedPiece)
						{
							const SelectedPiece& selectedPiece = *m_selectedPiece;
							if (selectedPiece.x == cellX && selectedPiece.y == cellY)
							{
								m_selectedPiece.reset(); //< unselect
								m_game.NotifyPieceDeselection();
								break;
							}
						}

						m_selectedPiece = SelectedPiece{ cellX, cellY };
						m_game.NotifyPieceSelection(cellX, cellY);
						break;
					}
				}

				if (m_selectedPiece)
				{
					const SelectedPiece& selectedPiece = *m_selectedPiece;
					if (m_game.MovePiece(selectedPiece.x, selectedPiece.y, cellX, cellY))
						m_selectedPiece.reset();
				}
			}
			break;
		}
	}
}

void Player::StartTurn()
{
	assert(!m_selectedPiece.has_value());
}
