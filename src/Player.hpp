#pragma once

class Player
{
	public:
		Player() = default;
		Player(const Player&) = delete;
		Player(Player&&) = default;
		~Player() = default;

		Player& operator=(const Player&) = delete;
		Player& operator=(Player&&) = default;

	private:
};
