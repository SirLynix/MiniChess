#include <Resources.hpp>
#include <SDLpp/Renderer.hpp>
#include <SDLpp/Surface.hpp>
#include <SDLpp/Texture.hpp>

Resources Resources::Load(SDLpp::Renderer& renderer)
{
	Resources resources;
	resources.marbleAndStoneBoardTexture = SDLpp::Texture::LoadFromFile(renderer, "resources/Top Down/Boards/Full Boards/Marble and Stone 512x552.png");
	
	SDLpp::Surface blackPieceSurface = SDLpp::Surface::LoadFromFile("resources/Top Down/Pieces/Black/Black - Marble 1 128x128.png");
	blackPieceSurface.SetColorKey(0, 128, 128);

	resources.blackPiecesTexture = renderer.CreateTextureFromSurface(blackPieceSurface);

	SDLpp::Surface whitePieceSurface = SDLpp::Surface::LoadFromFile("resources/Top Down/Pieces/White/White - Marble 1 128x128.png");
	whitePieceSurface.SetColorKey(0, 0, 0);

	resources.whitePiecesTexture = renderer.CreateTextureFromSurface(whitePieceSurface);
	resources.pieceCenterOffsetX = 65;
	resources.pieceCenterOffsetY = 88;

	constexpr int PieceWidth = 128;

	auto InitPiece = [&](PieceType type, int coordX, int coordY)
	{
		SDL_Rect rect{ coordX * PieceWidth, coordY * PieceWidth, PieceWidth, PieceWidth };
		SDL_Point center{ resources.pieceCenterOffsetX, resources.pieceCenterOffsetY };
		resources.blackPiecesSprites[static_cast<std::size_t>(type)] = SDLpp::Sprite(resources.blackPiecesTexture, rect, center);
		resources.whitePiecesSprites[static_cast<std::size_t>(type)] = SDLpp::Sprite(resources.whitePiecesTexture, rect, center);
	};

	InitPiece(PieceType::Bishop, 0, 0);
	InitPiece(PieceType::King,   1, 2);
	InitPiece(PieceType::Knight, 0, 1);
	InitPiece(PieceType::Pawn,   0, 3);
	InitPiece(PieceType::Queen,  2, 2);
	InitPiece(PieceType::Rook,   3, 2);

	return resources;
}
