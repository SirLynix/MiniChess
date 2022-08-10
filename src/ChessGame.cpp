#include <ChessGame.hpp>
#include <SDLpp/Lib.hpp>
#include <SDL.h>
#include <MovementRules/DiagonalMovementRule.hpp>
#include <MovementRules/HorizontalVerticalMovementRule.hpp>
#include <cassert>
#include <iostream>
#include <limits>

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

	InitMovementRules();

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

bool ChessGame::CheckMovement(PieceType pieceType, std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY) const
{
	for (const auto& movementRulePtr : m_movementRules[static_cast<std::size_t>(pieceType)])
	{
		if (movementRulePtr->CheckMovement(fromX, fromY, toX, toY))
			return true;
	}

	return false;
}

void ChessGame::InitMovementRules()
{
	auto AddRule = [&](PieceType pieceType, std::unique_ptr<MovementRule> movementRule)
	{
		m_movementRules[static_cast<std::size_t>(pieceType)].push_back(std::move(movementRule));
	};

	constexpr std::size_t InfiniteDistance = std::numeric_limits<std::size_t>::max();

	AddRule(PieceType::Rook, std::make_unique<HorizontalVerticalMovementRule>(InfiniteDistance));
	AddRule(PieceType::Bishop, std::make_unique<DiagonalMovementRule>(InfiniteDistance));

	AddRule(PieceType::Queen, std::make_unique<HorizontalVerticalMovementRule>(InfiniteDistance));
	AddRule(PieceType::Queen, std::make_unique<DiagonalMovementRule>(InfiniteDistance));

	AddRule(PieceType::King, std::make_unique<HorizontalVerticalMovementRule>(1));
	AddRule(PieceType::King, std::make_unique<DiagonalMovementRule>(1));
}

bool ChessGame::MovePiece(std::size_t fromX, std::size_t fromY, std::size_t toX, std::size_t toY)
{
	const Board::CellContent* cellContent = m_board.GetCell(fromX, fromY);
	if (!cellContent)
		return false;

	if (cellContent->ownerIndex != m_currentPlayer)
		return false;

	PieceType pieceType = cellContent->pieceType;

	if (CheckMovement(pieceType, fromX, fromY, toX, toY))
	{
		m_board.ClearCell(fromX, fromY);
		m_board.UpdateCell(toX, toY, pieceType, m_currentPlayer);

		NextTurn();
		return true;
	}
	else
	{
		std::cout << "Illegal move!" << std::endl;
		return false;
	}
}

void ChessGame::NextTurn()
{
	m_boardDrawer->ClearOverlay();

	m_currentPlayer = (m_currentPlayer + 1) % m_players.size();
	m_players[m_currentPlayer].StartTurn();

	std::cout << ((m_currentPlayer == 0) ? "White" : "Black") << " turn" << std::endl;
}

void ChessGame::NotifyPieceDeselection()
{
	m_boardDrawer->ClearOverlay();
}

void ChessGame::NotifyPieceSelection(std::size_t cellX, std::size_t cellY)
{
	const Board::CellContent* selectedCell = m_board.GetCell(cellX, cellY);
	assert(selectedCell);
	if (!selectedCell)
		return;

	for (std::size_t y = 0; y < Board::Height; ++y)
	{
		for (std::size_t x = 0; x < Board::Width; ++x)
			m_boardDrawer->EnableOverlay(x, y, CheckMovement(selectedCell->pieceType, cellX, cellY, x, y));
	}
}
