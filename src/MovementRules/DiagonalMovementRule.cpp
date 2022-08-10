#include <MovementRules/DiagonalMovementRule.hpp>

DiagonalMovementRule::DiagonalMovementRule(std::size_t maxDist) :
m_maxDist(maxDist)
{
}

bool DiagonalMovementRule::CheckMovement(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	std::size_t dx;
	if (toY > fromY)
		dx = (toY - fromY);
	else
		dx = (fromY - toY);

	if (dx == 0 || dx > m_maxDist)
		return false;

	std::size_t dy;
	if (toX > fromX)
		dy = (toX - fromX);
	else
		dy = (fromX - toX);

	if (dy == 0 || dy > m_maxDist)
		return false;

	if (dx != dy)
		return false;

	return true;
}
