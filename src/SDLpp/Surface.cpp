#include <SDLpp/Surface.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <stdexcept>

namespace SDLpp
{
	Surface::Surface(SDL_Surface* surface) :
	m_handle(surface)
	{
	}

	const SDL_Surface* Surface::GetHandle() const
	{
		return m_handle;
	}

	Surface::~Surface()
	{
		if (m_handle)
			SDL_FreeSurface(m_handle);
	}

	void Surface::SetColorKey(std::uint8_t r, std::uint8_t g, std::uint8_t b, bool enable)
	{
		assert(m_handle);
		SDL_SetColorKey(m_handle, (enable) ? SDL_TRUE : SDL_FALSE, SDL_MapRGB(m_handle->format, r, g, b));
	}
	
	Surface Surface::LoadFromFile(const std::string& filepath)
	{
		SDL_Surface* surface = IMG_Load(filepath.c_str());
		if (!surface)
			throw std::runtime_error("failed to load " + filepath + ": " + IMG_GetError());

		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));

		return Surface(surface);
	}
}
