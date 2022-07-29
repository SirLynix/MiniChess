#pragma once

#include <cstddef>

enum class PieceType
{
	Bishop,
	King,
	Knight,
	Pawn,
	Queen,
	Rook,

	Max = Rook
};

constexpr std::size_t PieceCount = static_cast<std::size_t>(PieceType::Max) + 1;
