#pragma once

#include <SDLpp/Renderer.hpp>
#include <MovablePtr.hpp>
#include <cstdint>
#include <string>

struct SDL_Window;

namespace SDLpp
{
	class Window
	{
		public:
			Window() = default;
			Window(const std::string& title, int width, int height);
			Window(const std::string& title, int x, int y, int width, int height);
			Window(const std::string& title, int x, int y, int width, int height, std::uint32_t flags);
			Window(const Window&) = delete;
			Window(Window&& window) noexcept = default;
			~Window();

			Renderer CreateRenderer();

			Window& operator=(const Window&) = delete;
			Window& operator=(Window&& window) noexcept = default;

		private:
			MovablePtr<SDL_Window> m_handle;
	};
}
