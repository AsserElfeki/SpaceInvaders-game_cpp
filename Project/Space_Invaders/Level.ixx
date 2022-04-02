module;

#include "olcPixelGameEngine.h"

import Ship;
import Player; 

export module Level;

export class Level {
	
private: 
	int32_t ScreenWidth;
	int32_t ScreenHeight;

	std::vector<Alien_Ship> ships; 
	std::vector<std::vector<olc::vi2d>> ships_pos;
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

	void set_Scale(int32_t w, int32_t h) {
		m_player.set_Screen(w, h);
		m_ship.set_Screen(w, h);
		m_player.set_Speed(500);
		m_player.set_Size(w / 10, h / 10);
		m_player.set_Pos(w, h);
		m_ship.set_Width(w / 25);
		ScreenWidth = w; 
		ScreenHeight = h;
	}

	void set_ShipsPos() {
		ships_pos.resize(5);
		for (int i = 0; i < 5; i++) 
		{
			for (int j = 0; j < 4; j++) {
				ships_pos[i].push_back({  (j+1) * (ScreenWidth / 5) , 
					 (i + 1) * (ScreenHeight / 7) });
			}
		}
	}

	void LoadLevel(olc::PixelGameEngine* pge, int level) {
		/*m_player.set_Screen(w, h);
		m_ship.set_Screen(w, h);*/

		// Erase previous frame
		pge->Clear(olc::BLACK);

		/*Boundaries*/
		pge->DrawLine(10, 50, ScreenWidth - 10, 50, olc::BLUE); //upper HZ line
		pge->DrawLine(10, 50, 10, ScreenHeight - 10, olc::BLUE); // left V line 
		pge->DrawLine(ScreenWidth - 10, 50, ScreenWidth - 10, ScreenHeight - 10, olc::BLUE); // right V line 
		//pge->DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // bottom HZ line
		
		/*Score*/
		pge->DrawString(ScreenWidth - 180, 10, "Score: 0000", olc::WHITE, 2);

		set_ShipsPos();
		m_player.DrawSelf(pge);

		std::vector<std::vector<bool>> tmp;
		if (level == 1)
			tmp = ships_pos_level_1; 
		else if (level ==2)
			tmp = ships_pos_level_2;
		else if (level == 3)
			tmp = ships_pos_level_3;

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (tmp[i][j])
					{
						m_ship.DrawSelf(pge, ships_pos[i][j]);
					}
				}
			}
			pge->DrawString(10, 10, "Level 1", olc::WHITE, 2);
	}

	Player& get_Player() {
		return m_player; 
	}

protected: 
	Alien_Ship m_ship;
	Player m_player;

};
