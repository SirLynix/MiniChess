#pragma once

#include <MovablePtr.hpp>
#include <cstdint>
#include <string>

struct SDL_Renderer;
struct SDL_Rect;

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

			Texture CreateTextureFromSurface(const Surface& surface);

			void Present();

			void RenderCopy(const Texture& texture);
			void RenderCopy(const Texture& texture, const SDL_Rect& destinationRect);

			void SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(Renderer&& renderer) noexcept = default;

		private:
			friend Window;

			explicit Renderer(SDL_Renderer* handle);

			MovablePtr<SDL_Renderer> m_handle;
	};
}