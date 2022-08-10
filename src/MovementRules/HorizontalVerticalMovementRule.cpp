#include <MovementRules/HorizontalVerticalMovementRule.hpp>

HorizontalVerticalMovementRule::HorizontalVerticalMovementRule(std::size_t maxDist) :
m_maxDist(maxDist)
{
}

bool HorizontalVerticalMovementRule::CheckMovement(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	if (fromX == toX)
	{
		if (toY > fromY)
			return (toY - fromY) <= m_maxDist;
		else if (toY < fromY)
			return (fromY - toY) <= m_maxDist;
	}

	if (fromY == toY)
	{
		if (toX > fromX)
			return (toX - fromX) <= m_maxDist;
		else if (toX < fromX)
			return (fromX - toX) <= m_maxDist;
	}

	return false;
}
