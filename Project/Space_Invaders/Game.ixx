module;

#include "olcPixelGameEngine.h"

import Ship;

import Level; 

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

		m_level1 = std::make_unique<Level>();
		m_level1->set_Scale(ScreenWidth(), ScreenHeight());


		return true;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{

	/****************************************************
	*                  Level Loading                    *
	****************************************************/

		m_level1->LoadLevel(this, 2);


	/****************************************************
	*                  User Input                       *
	****************************************************/

		
		return true;
	}

protected: 
	std::unique_ptr <Level> m_level1;
};
