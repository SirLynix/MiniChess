#include <Board.hpp>
#include <cassert>

Board::Board()
{
	Reset();
}

auto Board::GetCell(std::size_t x, std::size_t y) const -> const CellContent*
{
	assert(x < Width);
	assert(y < Height);
	const auto& cellContent = m_cells[y * Width + x];
	if (!cellContent.has_value())
		return nullptr;

	return &cellContent.value();
}

void Board::Reset()
{
	auto Cell = [&](std::size_t x, std::size_t y) -> std::optional<CellContent>&
	{
		return m_cells[y * Width + x];
	};

	auto InitPiece = [&](PieceType type, std::size_t x, std::size_t y)
	{
		Cell(x, y) = CellContent{
			type,
			0     //< player index
		};

		Cell(Width - x - 1, Height - y - 1) = CellContent{
			type,
			1     //< player index
		};
	};

	InitPiece(PieceType::Rook,   0, 0);
	InitPiece(PieceType::Knight, 1, 0);
	InitPiece(PieceType::Bishop, 2, 0);
	InitPiece(PieceType::Queen,  3, 0);
	InitPiece(PieceType::King,   4, 0);
	InitPiece(PieceType::Bishop, 5, 0);
	InitPiece(PieceType::Knight, 6, 0);
	InitPiece(PieceType::Rook,   7, 0);

	for (std::size_t i = 0; i < Width; ++i)
		InitPiece(PieceType::Pawn, i, 1);

	// Swap black king and black queen
	std::swap(Cell(3, Height - 1), Cell(4, Height - 1));
}
