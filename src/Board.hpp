#pragma once

#include <PieceType.hpp>
#include <array>
#include <optional>

class Board
{
	public:
		Board() = default;
		Board(const Board&) = delete;
		Board(Board&&) = default;
		~Board() = default;

		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = default;

		static constexpr std::size_t Width = 8;
		static constexpr std::size_t Height = 8;

	private:
		struct CellContent
		{
			PieceType pieceType;
			std::size_t ownerIndex;
		};

		std::array<std::optional<CellContent>, Width * Height> m_cells;
};
