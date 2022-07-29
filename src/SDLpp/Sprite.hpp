#pragma once

#include <MovablePtr.hpp>
#include <SDL.h>
#include <memory>

namespace SDLpp
{
	class Renderer;
	class Texture;

	class Sprite
	{
		public:
			Sprite() = default;
			Sprite(std::shared_ptr<const Texture> texture, const SDL_Rect& rect, const SDL_Point& center = {0, 0});
			Sprite(const Sprite&) = delete;
			Sprite(Sprite&&) noexcept = default;
			~Sprite() = default;

			void Render(Renderer& renderer, int x, int y, SDL_RendererFlip flipFlags = SDL_FLIP_NONE) const;
			void Render(Renderer& renderer, const SDL_Rect& destRect, SDL_RendererFlip flipFlags = SDL_FLIP_NONE) const;

			Sprite& operator=(const Sprite&) = delete;
			Sprite& operator=(Sprite&&) noexcept = default;

		private:
			std::shared_ptr<const Texture> m_texture;
			SDL_Rect m_rect;
			SDL_Point m_center;
	};
}
