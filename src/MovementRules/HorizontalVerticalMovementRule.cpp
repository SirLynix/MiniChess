#include <MovementRules/HorizontalVerticalMovementRule.hpp>
#include <Board.hpp>

HorizontalVerticalMovementRule::HorizontalVerticalMovementRule(std::size_t maxDist) :
m_maxDist(maxDist)
{
}

bool HorizontalVerticalMovementRule::CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	constexpr std::size_t NegOne = std::numeric_limits<std::size_t>::max();

	if (fromX == toX)
	{
		if (fromY == toY)
			return false;

		std::size_t dist = Board::GetDistance(fromY, toY);
		if (dist > m_maxDist)
			return false;

		std::size_t incrY = (toY > fromY) ? 1 : NegOne;

		for (std::size_t i = 0; i < dist; ++i)
		{
			fromY += incrY;

			if (const Board::CellContent* content = board.GetCell(fromX, fromY))
				return (fromY == toY && content->ownerIndex != playerIndex);
		}
	}
	else if (fromY == toY)
	{
		if (fromX == toX)
			return false;

		std::size_t dist = Board::GetDistance(fromX, toX);
		if (dist > m_maxDist)
			return false;

		std::size_t incrX = (toX > fromX) ? 1 : NegOne;

		for (std::size_t i = 0; i < dist; ++i)
		{
			fromX += incrX;

			if (const Board::CellContent* content = board.GetCell(fromX, fromY))
				return (fromX == toX && content->ownerIndex != playerIndex);
		}
	}
	else
		return false;

	return true;
}
