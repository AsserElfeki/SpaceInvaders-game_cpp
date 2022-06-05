module;

#include "olcPixelGameEngine.h"
#include <thread>
#include <chrono>

export import Ship;
export import Player; 

export module Level;

export class Level {
	
protected: 

	int speed; 
	int ships_health; 
	std::string level_name; 
	int32_t ScreenWidth = 1200;
	int32_t ScreenHeight = 800 ;
	std::vector<std::vector<Alien_Ship>> ships;
	std::vector<std::vector<bool>> ships_positions; 

	
public: 

	Level() {}
	Level(int _speed, int _ships_health, std::vector<std::vector<bool>> _ships_positions)
	{
		speed = _speed;
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

	void setScale(int32_t w, int32_t h) 
	{
		ScreenWidth = w; 
		ScreenHeight = h;
	}

	void createShips() 
	{
 		ships.clear();

		for (int i = 0; i < 5; i++) 
		{
			std::vector<Alien_Ship> tmp; 
			for (int j = 0; j < 4; j++) 
			{
				olc::vf2d tmp_pos = { (float) (j + 1) * (ScreenWidth / 5) ,
					(float) (i + 1) * (ScreenHeight / 7) };
				tmp.emplace_back(tmp_pos, ScreenWidth, ScreenHeight, ships_positions[i][j], speed, ships_health);
			}
			ships.push_back(tmp);
		}
	}

	void clearAlienBullets() {
		for (auto& shipsrow : ships)
			for (auto& ship : shipsrow)
				ship.getAlienBullets().clear(); 
	}

	void loadLevel(olc::PixelGameEngine* pge, float time) 
	{
		// Erase previous frame
		pge->Clear(olc::BLACK);

		/*Boundaries*/
		pge->DrawLine(10, 50, ScreenWidth - 10, 50, olc::BLUE); //upper HZ line
		pge->DrawLine(10, 50, 10, ScreenHeight - 10, olc::BLUE); // left V line 
		pge->DrawLine(ScreenWidth - 10, 50, ScreenWidth - 10, ScreenHeight - 10, olc::BLUE); // right V line 		
		
		pge->DrawString(10, 20, level_name, olc::WHITE, 2);
	}

	std::vector<std::vector<Alien_Ship>>& get_Ships() {return ships;}

};
