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
		if (GetKey(olc::Key::LEFT).bHeld) 
			m_level1->get_Player().move_left();

		if (GetKey(olc::Key::RIGHT).bHeld) 
			m_level1->get_Player().move_right();

		if (m_level1->get_Player().get_Pos().x < 11) 
			m_level1->get_Player().Pos_left();

		if ((m_level1->get_Player().get_Pos().x + ScreenWidth() /10) > (ScreenWidth() - 11))
			m_level1->get_Player().Pos_right();


		/*if (fBatPos < 11.0f) fBatPos = 11.0f;
		if (fBatPos + fBatWidth > float(ScreenWidth()) - 10.0f) fBatPos = float(ScreenWidth()) - 10.0f - fBatWidth;*/
		
		return true;
	}

protected: 
	std::unique_ptr <Level> m_level1;
};
