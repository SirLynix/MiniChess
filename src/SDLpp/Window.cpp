#include <SDLpp/Window.hpp>
#include <SDL.h>
#include <cassert>
#include <stdexcept>
#include <utility>

namespace SDLpp
{
	Window::Window(const std::string& title, int width, int height) :
	Window(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height)
	{
	}

	Window::Window(const std::string& title, int x, int y, int width, int height) :
	Window(title, x, y, width, height, 0)
	{
	}

	Window::Window(const std::string& title, int x, int y, int width, int height, std::uint32_t flags)
	{
		m_handle = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
		if (!m_handle)
			throw std::runtime_error(std::string("failed to create window: ") + SDL_GetError());
	}

	Window::Window(Window&& window) noexcept :
	m_handle(window.m_handle)
	{
		window.m_handle = nullptr;
	}

	Window::~Window()
	{
		if (m_handle)
			SDL_DestroyWindow(m_handle);
	}

	Renderer Window::CreateRenderer()
	{
		assert(m_handle);
		SDL_Renderer* renderer = SDL_CreateRenderer(m_handle, -1, 0);
		if (!renderer)
			throw std::runtime_error(std::string("failed to create renderer: ") + SDL_GetError());

		return Renderer(renderer);
	}
	
	Window& Window::operator=(Window&& window) noexcept
	{
		using std::swap;
		swap(m_handle, window.m_handle);

		return *this;
	}
}
