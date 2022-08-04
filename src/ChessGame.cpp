#include <ChessGame.hpp>
#include <SDLpp/Lib.hpp>
#include <SDL.h>
#include <cassert>

ChessGame::ChessGame(SDLpp::Lib& sdl) :
m_sdl(sdl),
m_currentPlayer(std::numeric_limits<std::size_t>::max()) //< so that next player is player #0
{
	constexpr int WindowWidth = 1280;
	constexpr int WindowHeight = 720;

	m_window = SDLpp::Window("ChessGame", WindowWidth, WindowHeight);
	m_renderer = m_window.CreateRenderer();

	for (std::size_t i = 0; i < PlayerCount; ++i)
		m_players.emplace_back(*this, i);

	m_resources = Resources::Load(m_renderer);
	m_boardDrawer.emplace(m_resources, WindowWidth, WindowHeight);

	NextTurn();
}

const Board& ChessGame::GetBoard() const
{
	return m_board;
}

const BoardDrawer& ChessGame::GetBoardDrawer() const
{
	assert(m_boardDrawer);
	return *m_boardDrawer;
}

int ChessGame::Run()
{
	bool opened = true;

	while (opened)
	{
		SDL_Event event;
		while (m_sdl.PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					opened = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEMOTION:
				{
					m_players[m_currentPlayer].HandleEvent(event);
					break;
				}
			}
		}

		m_renderer.SetDrawColor(128, 128, 255, 255);
		m_renderer.Clear();
		
		m_boardDrawer->Draw(m_renderer, m_board);

		m_renderer.Present();
	}

	return 0;
}

bool ChessGame::MovePiece(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY)
{
	const Board::CellContent* cellContent = m_board.GetCell(fromX, fromY);
	if (!cellContent)
		return false;

	if (cellContent->ownerIndex != m_currentPlayer)
		return false;

	PieceType pieceType = cellContent->pieceType;

	m_board.ClearCell(fromX, fromY);
	m_board.UpdateCell(toX, toY, pieceType, m_currentPlayer);

	NextTurn();
	return true;
}

void ChessGame::NextTurn()
{
	m_currentPlayer = (m_currentPlayer + 1) % m_players.size();
	m_players[m_currentPlayer].StartTurn([this](std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY)
	{
		return MovePiece(fromX, fromY, toX, toY);
	});
}
