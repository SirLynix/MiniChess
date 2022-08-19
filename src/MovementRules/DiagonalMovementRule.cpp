#include <MovementRules/DiagonalMovementRule.hpp>
#include <Board.hpp>

DiagonalMovementRule::DiagonalMovementRule(std::size_t maxDist) :
m_maxDist(maxDist)
{
}

bool DiagonalMovementRule::CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	std::size_t dx = Board::GetDistance(fromX, toX);
	if (dx == 0 || dx > m_maxDist)
		return false;

	std::size_t dy = Board::GetDistance(fromY, toY);
	if (dy == 0 || dy > m_maxDist)
		return false;

	if (dx != dy)
		return false;

	constexpr std::size_t NegOne = std::numeric_limits<std::size_t>::max();

	std::size_t incrX = (toX > fromX) ? 1 : NegOne;
	std::size_t incrY = (toY > fromY) ? 1 : NegOne;

	for (std::size_t i = 0; i < dx; ++i)
	{
		fromX += incrX;
		fromY += incrY;

		if (const Board::CellContent* content = board.GetCell(fromX, fromY))
			return toX == fromX && toY == fromY && content->ownerIndex != playerIndex;
	}

	return true;
}
