#pragma once

#include <PieceType.hpp>
#include <array>
#include <optional>

class Board
{
	public:
		struct CellContent;

		Board();
		Board(const Board&) = delete;
		Board(Board&&) = default;
		~Board() = default;

		void ClearCell(std::size_t x, std::size_t y);

		const CellContent* GetCell(std::size_t x, std::size_t y) const;

		void Reset();

		void UpdateCell(std::size_t x, std::size_t y, PieceType pieceType, std::size_t ownerIndex);

		static std::size_t GetCellIndex(std::size_t x, std::size_t y);
		static std::size_t GetDistance(std::size_t from, std::size_t to);

		Board& operator=(const Board&) = delete;
		Board& operator=(Board&&) = default;

		static constexpr std::size_t Width = 8;
		static constexpr std::size_t Height = 8;

		struct CellContent
		{
			PieceType pieceType;
			std::size_t ownerIndex;
		};

	private:
		std::optional<CellContent>& AccessCell(std::size_t x, std::size_t y);
		const std::optional<CellContent>& AccessCell(std::size_t x, std::size_t y) const;

		std::array<std::optional<CellContent>, Width * Height> m_cells;
};
