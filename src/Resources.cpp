#include <Resources.hpp>

Resources Resources::Load(SDLpp::Renderer& renderer)
{
	Resources resources;
	resources.marbleAndStoneBoard = SDLpp::Texture::LoadFromFile(renderer, "resources/Top Down/Boards/Full Boards/Marble and Stone 512x552.png");
	
	return resources;
}
