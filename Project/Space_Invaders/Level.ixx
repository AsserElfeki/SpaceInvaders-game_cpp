module;

#include "olcPixelGameEngine.h"
#include <thread>
#include <chrono>
#include "Constants.h"

export import Ship;
export import Player; 

export module Level;

export class Level {
	
protected: 

	int ships_speed; 
	int ships_health; 
	std::string level_name; 
	int screenWidth = screenConsts::ScreenWidth;
	int screenHeight = screenConsts::ScreenHeight ;
	std::vector<std::vector<Alien_Ship>> ships;
	std::vector<std::vector<bool>> ships_positions; 

	
public: 

	Level() {}
	Level(std::string name, int _speed, int _ships_health, std::vector<std::vector<bool>> _ships_positions)
	{
		level_name = name;
		ships_speed = _speed;
		ships_health = _ships_health;
		ships_positions = _ships_positions; 
		createShips();
	}

	bool isFinished() {
		for (auto& shiprow : ships)
		{
			for (auto& ship : shiprow)
			{
				if ( ship.isExist() )
					return false; 
			}
		}
		return true;
	}

	void createShips() 
	{
 		ships.clear();

		for (int i = 0; i < shipsMatrixCount::rows; i++)
		{
			std::vector<Alien_Ship> tmp; 
			for (int j = 0; j < shipsMatrixCount::colomns; j++)
			{
				olc::vf2d tmp_pos = { (float) (j + 1) * (screenWidth / screenConsts::horizontalSeg_count) ,
					(float) (i + 1) * (screenHeight / screenConsts::verticalSeg_count) };
				tmp.emplace_back(tmp_pos, ships_positions[i][j], ships_speed, ships_health);
			}
			ships.push_back(tmp);
		}
	}

	void clearAlienBullets() {
		for (auto& shipsrow : ships)
			for (auto& ship : shipsrow)
				ship.getAlienBullets().clear(); 
	}

	std::vector<std::vector<Alien_Ship>>& getShips() {return ships;}

	std::string getName() { return level_name; }
};
