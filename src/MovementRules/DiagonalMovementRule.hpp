#pragma once

#include <MovementRules/MovementRule.hpp>

class DiagonalMovementRule : public MovementRule
{
	public:
		DiagonalMovementRule(std::size_t maxDist);

		bool CheckMovement(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const override;

	private:
		std::size_t m_maxDist;
};
