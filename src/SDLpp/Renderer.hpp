#pragma once

#include <cstdint>
#include <string>

struct SDL_Renderer;

namespace SDLpp
{
	class Window;

	class Renderer
	{
		public:
			Renderer(const Renderer&) = delete;
			Renderer(Renderer&& renderer) noexcept;
			~Renderer();

			void Clear();

			void Present();

			void SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(Renderer&& renderer) noexcept;

		private:
			friend Window;

			explicit Renderer(SDL_Renderer* handle);

			SDL_Renderer* m_handle;
	};
}
