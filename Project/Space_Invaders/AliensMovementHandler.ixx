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
		auto moveShipRight = [fElapsedTime](Alien_Ship& ship) {ship.move_right(fElapsedTime); };
		auto moveShipLeft = [fElapsedTime](Alien_Ship& ship) {ship.move_left(fElapsedTime); };

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

				if (ships[i][rightBorder].get_Pos().x + ships[i][rightBorder].get_Width() >= 1200 - 20)
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

				if (ships[i][left_and_upBorder].get_Pos().x <= 20)
				{
					last_move_h = true;
					break;
				}
			}
		}
	}

	void MoveShips_v(float fElapsedTime, int level, std::vector<std::vector<Alien_Ship>>& ships)
	{
		auto moveShipUp = [fElapsedTime](Alien_Ship& ship) {ship.move_up(fElapsedTime); };
		auto moveShipDown = [fElapsedTime](Alien_Ship& ship) {ship.move_down(fElapsedTime); };

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

				if (ships[rows - 1][rightBorder].get_Pos().y + ships[rows - 1][rightBorder].get_Height() >= 800)
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

					if (ships[left_and_upBorder][rightBorder].get_Pos().y <= 50)
					{
						last_move_v = true;
						break;
					}
			}
		}
	}
};