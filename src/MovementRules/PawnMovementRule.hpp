#pragma once

#include <MovementRules/MovementRule.hpp>

class Board;

class PawnMovementRule : public MovementRule
{
	public:
		bool CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const override;
};
