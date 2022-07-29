#pragma once

#include <MovablePtr.hpp>
#include <SDL.h>
#include <cstdint>
#include <memory>
#include <string>

namespace SDLpp
{
	class Surface;
	class Texture;
	class Window;

	class Renderer
	{
		public:
			Renderer() = default;
			Renderer(const Renderer&) = delete;
			Renderer(Renderer&& renderer) noexcept = default;
			~Renderer();

			void Clear();

			std::shared_ptr<Texture> CreateTextureFromSurface(const Surface& surface);

			void Present();

			void RenderCopy(const Texture& texture);
			void RenderCopy(const Texture& texture, const SDL_Rect& destinationRect);
			void RenderCopy(const Texture& texture, const SDL_Rect& sourceRect, const SDL_Rect& destinationRect);
			void RenderCopy(const Texture& texture, const SDL_Rect& sourceRect, const SDL_Rect& destinationRect, double angle, const SDL_Point& center, SDL_RendererFlip flip = SDL_FLIP_NONE);

			void SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(Renderer&& renderer) noexcept = default;

		private:
			friend Window;

			explicit Renderer(SDL_Renderer* handle);

			MovablePtr<SDL_Renderer> m_handle;
	};
}