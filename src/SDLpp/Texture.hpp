#pragma once

#include <MovablePtr.hpp>
#include <cstdint>
#include <memory>
#include <string>

struct SDL_Rect;
struct SDL_Texture;

namespace SDLpp
{
	class Renderer;
	class Surface;

	class Texture
	{
		struct ConstructToken {};

		public:
			Texture() = default;
			explicit Texture(SDL_Texture* handle, ConstructToken);
			Texture(const Texture&) = delete;
			Texture(Texture&&) noexcept = default;
			~Texture();

			SDL_Rect GetRect() const;

			int Query(std::uint32_t* format, int* access, int* width, int* height) const;

			Texture& operator=(const Texture&) = delete;
			Texture& operator=(Texture&&) noexcept = default;

			static std::shared_ptr<Texture> LoadFromFile(Renderer& renderer, const std::string& filepath);

		private:
			friend class Renderer;

			const SDL_Texture* GetHandle() const;

			MovablePtr<SDL_Texture> m_handle;
	};
}
