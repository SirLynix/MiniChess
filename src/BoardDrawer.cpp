#include <BoardDrawer.hpp>
#include <Board.hpp>
#include <Resources.hpp>
#include <SDLpp/Renderer.hpp>
#include <SDLpp/Texture.hpp>
#include <SDL.h>

BoardDrawer::BoardDrawer(const Resources& resources, int width, int height) :
m_resources(resources),
m_height(height),
m_width(width)
{
}

void BoardDrawer::Draw(SDLpp::Renderer& renderer, const Board& board)
{
	SDL_Rect textureRect = m_resources.marbleAndStoneBoardTexture->GetRect();
	textureRect.x = m_width / 2 - textureRect.w / 2;
	textureRect.y = m_height / 2 - textureRect.h / 2;

	renderer.RenderCopy(*m_resources.marbleAndStoneBoardTexture, textureRect);
	//renderer.RenderCopy(m_resources.whitePiecesTexture, SDL_Rect{ 0, 0, 128, 128 }, textureRect);

	int drawX = textureRect.x + CellSize / 2;
	int drawY = textureRect.y + CellSize / 2;

	for (std::size_t y = 0; y < Board::Height; ++y)
	{
		for (std::size_t x = 0; x < Board::Width; ++x)
		{
			const Board::CellContent* content = board.GetCell(x, y);
			if (!content)
				continue;

			const auto& pieceSprites = (content->ownerIndex == 1) ? m_resources.blackPiecesSprites : m_resources.whitePiecesSprites;
			const auto& sprite = pieceSprites[static_cast<std::size_t>(content->pieceType)];

			SDL_RendererFlip flipFlags = (content->ownerIndex == 1) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

			sprite.Render(renderer, drawX, drawY, flipFlags);
			drawY += CellSize;
		}
		drawX += CellSize;
		drawY = textureRect.y + CellSize / 2;
	}
}
