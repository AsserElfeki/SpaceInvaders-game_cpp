module;

#include <vector>
#include <algorithm>
import Ship; 

export module AliensMovementHandler;

export class AliensMovementHandler {

private:
	enum levelShipCount {
		level1_rows = 3,
		level2_rows = 4,
		level3_rows = 5
	};

	enum shipsOnBorder {
		rightBorder = 3,
		left_and_upBorder = 0
	};

	bool last_move_h = true;
	bool last_move_v = true;

public: 

	void moveShips(float& fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships)
	{
		MoveShips_h(fElapsedTime, level, ships);
		MoveShips_v(fElapsedTime, level, ships);
	}

	void MoveShips_h(float& fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships )
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

		if (last_move_h)
		{
			for (int i = 0; i < rows; i++)
			{
				std::ranges::for_each(ships[i], moveShipRight);

				if (ships[i][rightBorder].getPos().x + ships[i][rightBorder].getWidth() >= 1200 - 20)
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

				if (ships[i][left_and_upBorder].getPos().x <= 20)
				{
					last_move_h = true;
					break;
				}
			}
		}
	}

	void MoveShips_v(float fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships)
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

				if (ships[rows - 1][rightBorder].getPos().y + ships[rows - 1][rightBorder].getHeight() >= 800)
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

					if (ships[left_and_upBorder][rightBorder].getPos().y <= 50)
					{
						last_move_v = true;
						break;
					}
			}
		}
	}
};