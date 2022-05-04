module;

#include "olcPixelGameEngine.h"
#include <thread>
#include <chrono>



export import Ship;
export import Player; 

export module Level;

export class Level {
	
private: 
	enum levelShipsSpeed {
		level1_speed = 100, 
		level2_speed = 150,
		level3_speed = 200,
		level4_speed = 300
	};

	enum levelShipCount {
		level1_rows = 3,
		level2_rows = 4,
		level3_rows = 5
	};

	enum shipsOnBorder {
		rightBorder = 3,
		left_and_upBorder = 0
	};

	int32_t ScreenWidth;
	int32_t ScreenHeight;
	bool last_move_h = true;
	bool last_move_v = true;
	std::string level_name; 
	
	int m_score = 0000;

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
			level_name = "Level 1";
			Create_Ships(_level, level1_speed);
		}
		else if (_level == 2)
		{
			level_name = "Level 2";
			Create_Ships(_level, level2_speed);
		}
		else if (_level == 3)
		{
			level_name = "Level 3";
			Create_Ships(_level, level3_speed);
		}
		else
		{
			level_name = "Level 4";
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

	void Create_Ships(int level, int _speed) 
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
				olc::vf2d tmp_pos = { (float) (j + 1) * (ScreenWidth / 5) ,
					(float) (i + 1) * (ScreenHeight / 7) };
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

	void MoveShips_h(float fElapsedTime, olc::PixelGameEngine* pge, int level) 
	{
		int rows;
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
				if (ships[i][rightBorder].get_Pos().x + ships[i][rightBorder].get_Width() >= ScreenWidth - 20)
				{
					last_move_h = false;
					continue;
				}
				for (int j = 0; j < 4; j++)
				{	
					ships[i][j].move_right(fElapsedTime);
					//ships[i][j].move_down(fElapsedTime);
					//ships[i][j].DrawShip(pge);
				}
			}
		}

		if (!last_move_h)
		{
			for (int i = 0; i < rows; i++)
			{
				if (ships[i][left_and_upBorder].get_Pos().x <= 20)
				{
					last_move_h = true;
					continue;
				}
				for (int j = 0; j < 4; j++)
				{
					ships[i][j].move_left(fElapsedTime);
					//ships[i][j].move_down(fElapsedTime);
					//ships[i][j].DrawShip(pge);
				}
			}
		}
	}

	void MoveShips_v(float fElapsedTime, olc::PixelGameEngine* pge, int level)
	{
		int rows;
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
				for (int j = 0; j < 4; j++)
				{
					ships[i][j].move_down(fElapsedTime);

					if (ships[rows-1][j].get_Pos().y + ships[rows-1][j].get_Height() >= ScreenHeight)
					{
						last_move_v = false;
						break;
					}
				}	
			}
		}

		if (!last_move_v)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					ships[i][j].move_up(fElapsedTime);

					if (ships[left_and_upBorder][j].get_Pos().y <= 50)
					{
						last_move_v = true;
						break;
					}
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
		pge->DrawString(ScreenWidth - 200, 20, "Score:" + std::to_string(m_score), olc::WHITE, 2);
		pge->DrawString(10, 20, level_name, olc::WHITE, 2);
	}

	std::vector<std::vector<Alien_Ship>>& get_Ships() {
		return ships;
	}

	void set_Score(int _score) {
		m_score = _score;
	}

	int get_Score() {
		return m_score;
	}

	void increase_Score_With_Time(float time) {
		m_score +=  (time * 60); 
	}

	void increase_Score_When_Hit_Alien() {
		m_score += 100;
	}

	void decrease_Score_When_Health_Decreased() {
		m_score -= 300;
	}
};
