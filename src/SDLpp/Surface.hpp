#pragma once

#include <MovablePtr.hpp>
#include <cstdint>
#include <string>

struct SDL_Surface;

namespace SDLpp
{
	class Surface
	{
		public:
			Surface() = default;
			Surface(const Surface&) = delete;
			Surface(Surface&&) noexcept = default;
			~Surface();

			void SetColorKey(std::uint8_t r, std::uint8_t g, std::uint8_t b, bool enable = true);

			Surface& operator=(const Surface&) = delete;
			Surface& operator=(Surface&&) noexcept = default;

			static Surface LoadFromFile(const std::string& filepath);

		private:
			friend class Renderer;

			explicit Surface(SDL_Surface* surface);

			const SDL_Surface* GetHandle() const;

			MovablePtr<SDL_Surface> m_handle;
	};
}
