#include <SDLpp/Renderer.hpp>
#include <SDL.h>
#include <cassert>
#include <utility>

namespace SDLpp
{
	Renderer::Renderer(SDL_Renderer* handle) :
	m_handle(handle)
	{
	}

	Renderer::Renderer(Renderer&& renderer) noexcept :
	m_handle(renderer.m_handle)
	{
		renderer.m_handle = nullptr;
	}

	Renderer::~Renderer()
	{
		if (m_handle)
			SDL_DestroyRenderer(m_handle);
	}

	void Renderer::Clear()
	{
		assert(m_handle);
		SDL_RenderClear(m_handle);
	}

	void Renderer::Present()
	{
		assert(m_handle);
		SDL_RenderPresent(m_handle);
	}

	void Renderer::SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
		assert(m_handle);
		SDL_SetRenderDrawColor(m_handle, r, g, b, a);
	}

	Renderer& Renderer::operator=(Renderer&& renderer) noexcept
	{
		using std::swap;
		swap(m_handle, renderer.m_handle);

		return *this;
	}
}
