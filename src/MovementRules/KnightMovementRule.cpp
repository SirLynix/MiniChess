#include <MovementRules/KnightMovementRule.hpp>
#include <Board.hpp>

KnightMovementRule::KnightMovementRule(std::size_t firstDist, std::size_t secondDist) :
m_firstDist(firstDist),
m_secondDist(secondDist)
{
}

bool KnightMovementRule::CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	std::size_t dx = Board::GetDistance(fromX, toX);
	std::size_t dy = Board::GetDistance(fromY, toY);

	if ((dx != m_firstDist || dy != m_secondDist) &&
		(dy != m_firstDist || dx != m_secondDist))
		return false;

	if (const Board::CellContent* content = board.GetCell(toX, toY); content && content->ownerIndex == playerIndex)
		return false;

	return true;
}
