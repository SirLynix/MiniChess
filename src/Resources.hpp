#pragma once

#include <SDLpp/Sprite.hpp>
#include <PieceType.hpp>
#include <array>
#include <memory>

namespace SDLpp
{
	class Renderer;
	class Texture;
}

struct Resources
{
	std::array<SDLpp::Sprite, PieceCount> blackPiecesSprites;
	std::array<SDLpp::Sprite, PieceCount> whitePiecesSprites;
	std::shared_ptr<SDLpp::Texture> marbleAndStoneBoardTexture;
	std::shared_ptr<SDLpp::Texture> blackPiecesTexture;
	std::shared_ptr<SDLpp::Texture> whitePiecesTexture;
	SDLpp::Sprite selectionOverlaySprite;

	int pieceCenterOffsetX;
	int pieceCenterOffsetY;

	static Resources Load(SDLpp::Renderer& renderer);
};