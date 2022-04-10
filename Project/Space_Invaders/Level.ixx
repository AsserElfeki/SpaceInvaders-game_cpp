module;

#include "olcPixelGameEngine.h"
extern std::string player_name;

export import Ship;
export import Player; 

export module Level;

export class Level {
	
private: 
	int32_t ScreenWidth;
	int32_t ScreenHeight;
	//bool drawn = false;
	bool last_move = true;


	std::vector<std::vector<Alien_Ship>> ships;
	std::vector<std::vector<bool>> ships_pos_level_1 =
	{
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1}
	};
	
	std::vector<std::vector<bool>> ships_pos_level_2 =
	{
		{1,1,1,1},
		{1,0,0,1},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	}; 
	
	std::vector<std::vector<bool>> ships_pos_level_3 =
	{
		{1,1,1,1},
		{1,1,1,1},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	};




public: 
	std::vector<std::vector<bool>> get_level1() {
		return ships_pos_level_1; 
	}

	std::vector<std::vector<bool>> get_level2() {
		return ships_pos_level_2;
	}

	std::vector<std::vector<bool>> get_level3() {
		return ships_pos_level_3;
	}

	

	void set_Scale(int32_t w, int32_t h) 
	{
		ScreenWidth = w; 
		ScreenHeight = h;
	}

	void Create_Ships(int level) 
	{
		std::vector<std::vector<bool>> booltmp;

		if (level == 1)
			booltmp = ships_pos_level_1;
		else if (level == 2)
			booltmp = ships_pos_level_2;
		else if (level == 3)
			booltmp = ships_pos_level_3;


		for (int i = 0; i < 5; i++) 
		{
			std::vector<Alien_Ship> tmp; 
			for (int j = 0; j < 4; j++) 
			{
				olc::vi2d tmp_pos = { (j + 1) * (ScreenWidth / 5) ,
					 (i + 1) * (ScreenHeight / 7) };
				tmp.emplace_back(tmp_pos, ScreenWidth, ScreenHeight, booltmp[i][j]);
			}
			ships.push_back(tmp);
		}
	}


	void Move_Ships(float time, olc::PixelGameEngine* pge) {


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
				if (ships[i][0].get_Pos().x - ships[i][0].get_Width() <= 20)
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

	void LoadLevel(olc::PixelGameEngine* pge, int level, float time) 
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
		pge->DrawString(10, 10, "Level 1", olc::WHITE, 2);
		pge->DrawString(200, 10, player_name, olc::WHITE, 2);



	}

	//Player& get_Player() {
	//	return m_player; 
	//}

protected: 
	//Player m_player;

};
