module;

#include <vector>
#include <algorithm>
#include <future>
#include <thread>
#include "Constants.h"
import Ship; 

export module AliensMovementHandler;

export class AliensMovementHandler {

private:
	enum levelShipCount {
		level1_rows = 3,
		level2_rows = 4,
		level3_rows = 5
	};


	bool last_move_h = true;
	bool last_move_v = true;

public: 

	void moveAlienShips(float& fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships)
	{
		//this is here because I wanna later make it work
		//std::future<void> thread1 = std::async(std::launch::async, &AliensMovementHandler::MoveShips_horizontally, this, fElapsedTime, level, ships);
		//std::future<void> thread2 = std::async(std::launch::async, &AliensMovementHandler::MoveShips_vertically, this, fElapsedTime, level, ships);

		MoveShips_horizontally(fElapsedTime, level, ships);
		MoveShips_vertically(fElapsedTime, level, ships);
	}

	void MoveShips_horizontally(float& fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships )
	{
		auto moveShipRight = [fElapsedTime](Alien_Ship& ship) {ship.moveRight(fElapsedTime); };
		auto moveShipLeft = [fElapsedTime](Alien_Ship& ship) {ship.moveLeft(fElapsedTime); };

		levelShipCount rows;
		if (level == 1)
			rows = level1_rows;
		else if (level == 3)
			rows = level3_rows;
		else
			rows = level2_rows;

		if (last_move_h) //if the ships are not on max right position
		{
			for (int i = 0; i < rows; i++)
			{
				std::ranges::for_each(ships[i], moveShipRight);

				if (ships[i][shipsOnBorder::rightBorder].getPos().x + ships[i][shipsOnBorder::rightBorder].getWidth() >= screenConsts::rightBoundary)
				{
					last_move_h = false;
					break;
				}	
			}
		}

		if (!last_move_h)
		{
			for (int i = 0; i < rows; i++)
			{
				std::ranges::for_each(ships[i], moveShipLeft);

				if (ships[i][shipsOnBorder::left_and_upBorder].getPos().x <= screenConsts::leftBoundary)
				{
					last_move_h = true;
					break;
				}
			}
		}
	}

	void MoveShips_vertically(float fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships)
	{
		auto moveShipUp = [fElapsedTime](Alien_Ship& ship) {ship.moveUp(fElapsedTime); };
		auto moveShipDown = [fElapsedTime](Alien_Ship& ship) {ship.moveDown(fElapsedTime); };

		levelShipCount rows;
		if (level == 1)
			rows = level1_rows;
		else if (level == 3)
			rows = level3_rows;
		else
			rows = level2_rows;


		if (last_move_v)
		{
			for (int i = 0; i < rows; i++)
			{
				std::ranges::for_each(ships[i], moveShipDown);

				if (ships[rows - 1][shipsOnBorder::rightBorder].getPos().y + ships[rows - 1][shipsOnBorder::rightBorder].getHeight() >= screenConsts::bottomBoundary)
				{
					last_move_v = false;
					break;
				}
			}
		}

		if (!last_move_v)
		{
			for (int i = 0; i < rows; i++)
			{
				std::ranges::for_each(ships[i], moveShipUp);

					if (ships[shipsOnBorder::left_and_upBorder][shipsOnBorder::rightBorder].getPos().y <= screenConsts::topBoundary)
					{
						last_move_v = true;
						break;
					}
			}
		}
	}
};