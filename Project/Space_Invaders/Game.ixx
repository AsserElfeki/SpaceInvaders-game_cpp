module;

#include "olcPixelGameEngine.h"
import <vector>;

import Ships;
import Player;

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
public:
	SpaceInvaders()
	{
		sAppName = "Space Invaders "
				   " By: Asser Moustafa";
	}

private:
	

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		m_Player.set_Size(float(ScreenWidth() / 10), float(ScreenHeight() / 10));
		m_ships.set_Width(ScreenWidth() / 22);
		m_ships.set_ShipsPos();


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Erase previous frame
		Clear(olc::BLACK);

		/*################ Place Holders ################*/

		// Draw Boundary
		DrawLine(10, 50, ScreenWidth() - 10, 50, olc::BLUE); //upper HZ line
		DrawLine(10, 50, 10, ScreenHeight() - 10, olc::BLUE); // left V line 
		DrawLine(ScreenWidth() - 10, 50, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // right V line 
		//DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // bottom HZ line

		// placeholder for the player (top left x & y co-ord. , width, height) 
		FillRect(float((ScreenWidth() / 2) - (m_Player.get_Size().x / 2)), ScreenHeight() - 2 * m_Player.get_Size().y, m_Player.get_Size().x, m_Player.get_Size().y, olc::GREEN);
		
		// placeholder for the ships 
	/*	for (auto a : m_ships.get_ships_pos_vec()) {
			FillCircle(a, m_ships.get_Width(), olc::RED);
		}*/
		m_ships.DrawSelf(this);

		DrawString(10.0f, 10.0f , "Score: 0000", olc::WHITE, 2);
		DrawString(ScreenWidth()-120, 10.0f, "Level 1", olc::WHITE, 2);

		/*################ User Input ################*/

		
		return true;
	}

	

protected:
	Alien_ships m_ships;
	Player m_Player; 
};

/*
1- Level should have : 
	different vector<bool> 
	different speed 
	different bps 

2- fix the set ship pos 
3- make it "ship" and it stores info about one ship 
4- in Level : draw ships & setshipspos 
5- 

*/