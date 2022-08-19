#include <MovementRules/PawnMovementRule.hpp>
#include <Board.hpp>
#include <ChessGame.hpp>

bool PawnMovementRule::CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	if (fromX != toX)
	{
		if (Board::GetDistance(fromX, toX) != 1)
			return false;

		std::size_t attackY = (playerIndex == ChessGame::WhitePlayerIndex) ? fromY + 1 : fromY - 1;
		if (toY != attackY)
			return false;

		const Board::CellContent* cellContent = board.GetCell(toX, toY);
		if (!cellContent || cellContent->ownerIndex == playerIndex)
			return false;

		return true;
	}

	std::size_t initialPosY = (playerIndex == ChessGame::WhitePlayerIndex) ? 1 : Board::Height - 2;
	std::size_t allowedDist = (fromY == initialPosY) ? 2 : 1;

	if (playerIndex == ChessGame::WhitePlayerIndex)
	{
		if (toY <= fromY)
			return false;
	}
	else
	{
		if (toY >= fromY)
			return false;
	}

	if (Board::GetDistance(fromY, toY) > allowedDist)
		return false;

	// Check if a piece blocks us
	if (board.GetCell(toX, toY) != nullptr)
		return false;

	return true;
}
