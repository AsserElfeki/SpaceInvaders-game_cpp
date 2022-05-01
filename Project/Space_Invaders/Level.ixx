module;

#include "olcPixelGameEngine.h"
#include <thread>
#include <chrono>



export import Ship;
export import Player; 

export module Level;

export class Level {
	
private: 
	enum levelSHipsSpeed {
		level1_speed = 100, 
		level2_speed = 150,
		level3_speed = 200,
		level4_speed = 300
	};

	int32_t ScreenWidth;
	int32_t ScreenHeight;
	bool last_move = true;
	std::string name; 
	

	std::vector<std::vector<Alien_Ship>> ships;

	std::vector<std::vector<bool>> ships_pos_level_1 =
	{
		/*{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}*/

		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	};

	std::vector<std::vector<bool>> ships_pos_level_2 =
	{
		/*{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}*/

		{1,0,0,1},
		{0,1,1,0},
		{0,1,1,0},
		{1,0,0,1},
		{0,0,0,0}
	};

	std::vector<std::vector<bool>> ships_pos_level_3 =
	{
		/*{0,0,1,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}*/

		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
	};
	
	std::vector<std::vector<bool>> ships_pos_level_4 =
	{
		{0,1,1,0},
		{1,0,0,1},
		{1,0,0,1},
		{0,1,1,0},
		{0,0,0,0}
	};
	
public: 

	Level() {}

	Level(int _level, int32_t w, int32_t h) {
		set_Scale(w, h);

		if (_level == 1)
		{
			name = "Level 1";
			Create_Ships(_level, level1_speed);
		}
		else if (_level == 2)
		{
			name = "Level 2";
			Create_Ships(_level, level2_speed);
		}
		else if (_level == 3)
		{
			name = "Level 3";
			Create_Ships(_level, level3_speed);
		}
		else
		{
			name = "Level 4";
			Create_Ships(_level, level4_speed);
		}
	}


	bool is_finished() {
		for (auto& shiprow : ships)
		{
			for (auto& ship : shiprow)
			{
				if ( ship.is_exist() )
					return false; 
			}
		}
		return true;
	}

	//std::vector<std::vector<bool>> get_level1() {
	//	return ships_pos_level_1; 
	//}

	//std::vector<std::vector<bool>> get_level2() {
	//	return ships_pos_level_2;
	//}

	//std::vector<std::vector<bool>> get_level3() {
	//	return ships_pos_level_3;
	//}

	void set_Scale(int32_t w, int32_t h) 
	{
		ScreenWidth = w; 
		ScreenHeight = h;
	}

	void Create_Ships(int level, float _speed) 
	{
		ships.clear();
		int tmp_health;
		std::vector<std::vector<bool>> booltmp;
		if (level == 1)
		{
			booltmp = ships_pos_level_1;
			tmp_health = 1;
		}
		else if (level == 2)
		{
			booltmp = ships_pos_level_2;
			tmp_health = 2;
		}
		else if (level == 3)
		{
			booltmp = ships_pos_level_3;
			tmp_health = 3;
		}
		else
		{
			booltmp = ships_pos_level_4;
			tmp_health = 5;
		}

		for (int i = 0; i < 5; i++) 
		{
			std::vector<Alien_Ship> tmp; 
			for (int j = 0; j < 4; j++) 
			{
				olc::vi2d tmp_pos = { (j + 1) * (ScreenWidth / 5) ,
					 (i + 1) * (ScreenHeight / 7) };
				tmp.emplace_back(tmp_pos, ScreenWidth, ScreenHeight, booltmp[i][j], _speed, tmp_health);
			}
			ships.push_back(tmp);
		}
	}

	void clearAlienBullets() {
		for (auto& shipsrow : ships)
			for (auto& ship : shipsrow)
				ship.get_AlienBullets().clear(); 
	}

	void Move_Ships(float time, olc::PixelGameEngine* pge) 
	{
		if (last_move)
		{
			for (int i = 0; i < 5; i++)
			{
				if (ships[i][3].get_Pos().x + ships[i][3].get_Width() >= ScreenWidth - 20)
				{
					last_move = false;
					continue;
				}
				for (int j = 0; j < 4; j++)
				{	
						ships[i][j].move_right(time);
						ships[i][j].DrawSelf(pge);
				}
			}
		}

		if (!last_move)
		{
			for (int i = 0; i < 5; i++)
			{
				if (ships[i][0].get_Pos().x <= 20)
				{
					last_move = true;
					continue;
				}
				for (int j = 0; j < 4; j++)
				{
						ships[i][j].move_left(time);
						ships[i][j].DrawSelf(pge);			
				}
			}
		}
	}

	void LoadLevel(olc::PixelGameEngine* pge, float time) 
	{
		// Erase previous frame
		pge->Clear(olc::BLACK);

		/*Boundaries*/
		pge->DrawLine(10, 50, ScreenWidth - 10, 50, olc::BLUE); //upper HZ line
		pge->DrawLine(10, 50, 10, ScreenHeight - 10, olc::BLUE); // left V line 
		pge->DrawLine(ScreenWidth - 10, 50, ScreenWidth - 10, ScreenHeight - 10, olc::BLUE); // right V line 
		//pge->DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // bottom HZ line
		
		/*Score and player*/
		pge->DrawString(ScreenWidth - 180, 10, "Score: 0000", olc::WHITE, 2);
		pge->DrawString(10, 10, name, olc::WHITE, 2);
	}

	std::vector<std::vector<Alien_Ship>>& get_Ships() {
		return ships;
	}

};
