#include <Board.hpp>
#include <cassert>

Board::Board()
{
	Reset();
}

void Board::ClearCell(std::size_t x, std::size_t y)
{
	AccessCell(x, y) = std::nullopt;
}

auto Board::GetCell(std::size_t x, std::size_t y) const -> const CellContent*
{
	const auto& cellContent = AccessCell(x, y);
	if (!cellContent.has_value())
		return nullptr;

	return &cellContent.value();
}

void Board::Reset()
{
	auto InitPiece = [&](PieceType type, std::size_t x, std::size_t y)
	{
		UpdateCell(x, y, type, 0);
		UpdateCell(Width - x - 1, Height - y - 1, type, 1);
	};

	InitPiece(PieceType::Rook,   0, 0);
	InitPiece(PieceType::Knight, 1, 0);
	InitPiece(PieceType::Bishop, 2, 0);
	InitPiece(PieceType::King,   3, 0);
	InitPiece(PieceType::Queen,  4, 0);
	InitPiece(PieceType::Bishop, 5, 0);
	InitPiece(PieceType::Knight, 6, 0);
	InitPiece(PieceType::Rook,   7, 0);

	for (std::size_t i = 0; i < Width; ++i)
		InitPiece(PieceType::Pawn, i, 1);

	// Swap black king and black queen
	std::swap(AccessCell(3, Height - 1), AccessCell(4, Height - 1));
}

void Board::UpdateCell(std::size_t x, std::size_t y, PieceType pieceType, std::size_t ownerIndex)
{
	AccessCell(x, y) = CellContent{
		pieceType,
		ownerIndex
	};
}

std::size_t Board::GetCellIndex(std::size_t x, std::size_t y)
{
	return y * Width + x;
}

std::size_t Board::GetDistance(std::size_t from, std::size_t to)
{
	std::size_t distance;
	if (to > from)
		distance = (to - from);
	else
		distance = (from - to);

	return distance;
}

auto Board::AccessCell(std::size_t x, std::size_t y) -> std::optional<CellContent>&
{
	assert(x < Width);
	assert(y < Height);
	return m_cells[y * Width + x];
}

auto Board::AccessCell(std::size_t x, std::size_t y) const -> const std::optional<CellContent>&
{
	assert(x < Width);
	assert(y < Height);
	return m_cells[y * Width + x];
}
