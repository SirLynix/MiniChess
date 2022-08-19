#pragma once

#include <cstddef>

class Board;

class MovementRule
{
	public:
		MovementRule() = default;
		MovementRule(const MovementRule&) = delete;
		MovementRule(MovementRule&&) = delete;
		virtual ~MovementRule() = default;

		virtual bool CheckMovement(const Board& board, std::size_t playerIndex, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const = 0;

		MovementRule& operator=(const MovementRule&) = delete;
		MovementRule& operator=(MovementRule&&) = delete;
};
