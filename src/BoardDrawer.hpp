#pragma once

#include <Board.hpp> //< TODO: Replace by Constants.hpp
#include <bitset>
#include <cstddef>

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

		void ClearOverlay();

		void Draw(SDLpp::Renderer& renderer, const Board& board) const;

		void EnableOverlay(std::size_t cellX, std::size_t cellY, bool enable = true);

		bool GetHoveringCell(int x, int y, std::size_t& cellX, std::size_t& cellY) const;

		BoardDrawer& operator=(const BoardDrawer&) = delete;
		BoardDrawer& operator=(BoardDrawer&&) = default;

		static constexpr std::size_t CellSize = 64;

	private:
		std::bitset<Board::Width * Board::Height> m_overlaidCells;
		const Resources& m_resources;
		int m_height;
		int m_width;
};
