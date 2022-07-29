#include <SDLpp/Sprite.hpp>
#include <SDLpp/Renderer.hpp>
#include <cassert>
#include <stdexcept>

namespace SDLpp
{
	Sprite::Sprite(std::shared_ptr<const Texture> texture, const SDL_Rect& rect, const SDL_Point& center) :
	m_texture(std::move(texture)),
	m_rect(rect),
	m_center(center)
	{
	}

	void Sprite::Render(Renderer& renderer, int x, int y, SDL_RendererFlip flipFlags) const
	{
		SDL_Rect destRect;
		destRect.x = x - m_center.x;
		destRect.y = y - m_center.y;
		destRect.w = m_rect.w;
		destRect.h = m_rect.h;

		Render(renderer, destRect, flipFlags);
	}

	void Sprite::Render(Renderer& renderer, const SDL_Rect& destRect, SDL_RendererFlip flipFlags) const
	{
		assert(m_texture);
		renderer.RenderCopy(*m_texture, m_rect, destRect, 0.0, SDL_Point{0, 0}, flipFlags);
	}
}
