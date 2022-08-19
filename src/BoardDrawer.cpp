#include <BoardDrawer.hpp>
#include <Board.hpp>
#include <Resources.hpp>
#include <SDLpp/Renderer.hpp>
#include <SDLpp/Texture.hpp>
#include <algorithm>

BoardDrawer::BoardDrawer(const Resources& resources, int width, int height) :
m_resources(resources),
m_height(height),
m_width(width)
{
}

void BoardDrawer::ClearMovementOverlay()
{
	m_overlaidCells.reset();
}

void BoardDrawer::ClearSelectionOverlay()
{
	m_selectionOverlay.reset();
}

void BoardDrawer::Draw(SDLpp::Renderer& renderer, const Board& board) const
{
	SDL_Rect textureRect = m_resources.marbleAndStoneBoardTexture->GetRect();
	textureRect.x = m_width / 2 - textureRect.w / 2;
	textureRect.y = m_height / 2 - textureRect.h / 2;

	renderer.RenderCopy(*m_resources.marbleAndStoneBoardTexture, textureRect);

	int originX = textureRect.x + CellSize / 2;
	int originY = textureRect.y + CellSize / 2;

	m_drawSprites.clear();

	if (m_selectionOverlay)
	{
		const SelectionOverlay& selectionOverlay = *m_selectionOverlay;
		float xOffset, yOffset;
		GetDrawPosition(selectionOverlay.cellX, selectionOverlay.cellY, xOffset, yOffset);

		m_drawSprites.push_back({ &m_resources.selectionOverlaySprite, originX + xOffset, originY + yOffset, SDL_FLIP_NONE, -1 });
	}

	for (std::size_t x = 0; x < Board::Width; ++x)
	{
		for (std::size_t y = 0; y < Board::Height; ++y)
		{
			// Compute grid coordinates
			float xOffset, yOffset;
			GetDrawPosition(x, y, xOffset, yOffset);

			float drawX = originX + xOffset;
			float drawY = originY + yOffset;

			// Draw movement overlay
			std::size_t cellIndex = Board::GetCellIndex(x, y);
			if (m_overlaidCells[cellIndex])
				m_drawSprites.push_back({ &m_resources.movementOverlaySprite, drawX, drawY, SDL_FLIP_NONE, -1 });

			// Draw piece, if any
			const Board::CellContent* content = board.GetCell(x, y);
			if (content)
			{
				const auto& pieceSprites = (content->ownerIndex == 1) ? m_resources.blackPiecesSprites : m_resources.whitePiecesSprites;
				const auto& sprite = pieceSprites[static_cast<std::size_t>(content->pieceType)];

				SDL_RendererFlip flipFlags = (content->ownerIndex == 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
				m_drawSprites.push_back({ &sprite, drawX, drawY, flipFlags, 0 });

				sprite.Render(renderer, drawX, drawY, flipFlags);
			}
		}
	}

	std::sort(m_drawSprites.begin(), m_drawSprites.end(), [](const DrawSprite& lhs, const DrawSprite& rhs)
	{
		if (lhs.order == rhs.order)
			return lhs.drawY < rhs.drawY;
		else
			return lhs.order < rhs.order;
	});

	for (const auto& drawSprite : m_drawSprites)
		drawSprite.sprite->Render(renderer, drawSprite.drawX, drawSprite.drawY, drawSprite.flipFlags);
}

void BoardDrawer::EnableMovementOverlay(std::size_t cellX, std::size_t cellY, bool enable)
{
	std::size_t cellIndex = Board::GetCellIndex(cellX, cellY);
	m_overlaidCells[cellIndex] = enable;
}

void BoardDrawer::EnableSelectionOverlay(std::size_t cellX, std::size_t cellY)
{
	m_selectionOverlay = SelectionOverlay{ cellX, cellY };
}

bool BoardDrawer::GetHoveringCell(int x, int y, std::size_t& cellX, std::size_t& cellY) const
{
	SDL_Rect textureRect = m_resources.marbleAndStoneBoardTexture->GetRect();
	textureRect.x = m_width / 2 - textureRect.w / 2;
	textureRect.y = m_height / 2 - textureRect.h / 2;

	if (x < textureRect.x || y < textureRect.y)
		return false;

	if (x >= textureRect.x + Board::Width * CellSize ||
		y >= textureRect.y + Board::Height * CellSize)
		return false;

	cellX = (x - textureRect.x) / CellSize;
	cellY = (y - textureRect.y) / CellSize;

	std::swap(cellX, cellY);
	cellX = Board::Width - cellX - 1;

	return true;
}

void BoardDrawer::GetDrawPosition(std::size_t cellX, std::size_t cellY, float& xOffset, float& yOffset)
{
	std::swap(cellX, cellY);
	cellY = Board::Height - cellY - 1;

	xOffset = cellX * CellSize;
	yOffset = cellY * CellSize;
}
