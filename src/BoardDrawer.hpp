#pragma once

#include <cstddef>

class Board;
class Resources;

namespace SDLpp
{
	class Renderer;
}

class BoardDrawer
{
	public:
		BoardDrawer(const Resources& resources, int width, int height);
		BoardDrawer(const BoardDrawer&) = delete;
		BoardDrawer(BoardDrawer&&) = default;
		~BoardDrawer() = default;

		void Draw(SDLpp::Renderer& renderer, const Board& board);

		BoardDrawer& operator=(const BoardDrawer&) = delete;
		BoardDrawer& operator=(BoardDrawer&&) = default;

		static constexpr std::size_t CellSize = 64;

	private:
		const Resources& m_resources;
		int m_height;
		int m_width;
};
