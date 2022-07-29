#include <SDLpp/Renderer.hpp>
#include <SDLpp/Surface.hpp>
#include <SDLpp/Texture.hpp>
#include <SDL.h>
#include <cassert>
#include <utility>

namespace SDLpp
{
	Renderer::Renderer(SDL_Renderer* handle) :
	m_handle(handle)
	{
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

	std::shared_ptr<Texture> Renderer::CreateTextureFromSurface(const Surface& surface)
	{
		return std::make_shared<Texture>(SDL_CreateTextureFromSurface(m_handle, const_cast<SDL_Surface*>(surface.GetHandle())), Texture::ConstructToken{}); //< SDL isn't const-correct
	}

	void Renderer::Present()
	{
		assert(m_handle);
		SDL_RenderPresent(m_handle);
	}

	void Renderer::RenderCopy(const Texture& texture)
	{
		assert(m_handle);
		SDL_RenderCopy(m_handle, const_cast<SDL_Texture*>(texture.GetHandle()), nullptr, nullptr);
	}

	void Renderer::RenderCopy(const Texture& texture, const SDL_Rect& destinationRect)
	{
		assert(m_handle);
		SDL_RenderCopy(m_handle, const_cast<SDL_Texture*>(texture.GetHandle()), nullptr, &destinationRect);
	}

	void Renderer::RenderCopy(const Texture& texture, const SDL_Rect& sourceRect, const SDL_Rect& destinationRect)
	{
		assert(m_handle);
		SDL_RenderCopy(m_handle, const_cast<SDL_Texture*>(texture.GetHandle()), &sourceRect, &destinationRect);
	}

	void Renderer::RenderCopy(const Texture& texture, const SDL_Rect& sourceRect, const SDL_Rect& destinationRect, double angle, const SDL_Point& center, SDL_RendererFlip flip)
	{
		assert(m_handle);
		SDL_RenderCopyEx(m_handle, const_cast<SDL_Texture*>(texture.GetHandle()), &sourceRect, &destinationRect, angle, &center, flip);
	}

	void Renderer::SetDrawColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
	{
		assert(m_handle);
		SDL_SetRenderDrawColor(m_handle, r, g, b, a);
	}
}
