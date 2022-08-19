#pragma once

#include <MovementRules/MovementRule.hpp>

class Board;

class HorizontalVerticalMovementRule : public MovementRule
{
	public:
		HorizontalVerticalMovementRule(std::size_t maxDist);

		bool CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const override;

	private:
		std::size_t m_maxDist;
};
