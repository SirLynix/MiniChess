#include <BoardDrawer.hpp>
#include <Resources.hpp>
#include <SDLpp/Renderer.hpp>
#include <SDL.h>

BoardDrawer::BoardDrawer(const Resources& resources, int width, int height) :
m_resources(resources),
m_height(height),
m_width(width)
{
}

void BoardDrawer::Draw(SDLpp::Renderer& renderer, const Board& board)
{
	SDL_Rect textureRect = m_resources.marbleAndStoneBoard.GetRect();
	textureRect.x = m_width / 2 - textureRect.w / 2;
	textureRect.y = m_height / 2 - textureRect.h / 2;

	renderer.RenderCopy(m_resources.marbleAndStoneBoard, textureRect);
}
