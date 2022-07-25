#pragma once

#include <SDLpp/Texture.hpp>

namespace SDLpp
{
	class Renderer;
}

struct Resources
{
	SDLpp::Texture marbleAndStoneBoard;

	static Resources Load(SDLpp::Renderer& renderer);
};