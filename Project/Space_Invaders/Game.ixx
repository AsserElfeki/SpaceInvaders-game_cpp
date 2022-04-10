module;

#include "olcPixelGameEngine.h"


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
	float fTargetFrameTime = 1.0f / 100.0f; // Virtual FPS of 100fps
	float fAccumulatedTime = 0.0f;

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		m_level1 = std::make_unique<Level>();
		m_player = std::make_unique<Player>();

		m_level1->set_Scale(ScreenWidth(), ScreenHeight());
		m_level1->Create_Ships(1);

		m_player->set_Scale(ScreenWidth(), ScreenHeight());

		return true;
	}


	bool OnUserUpdate(float fElapsedTime) override
	{
		//fAccumulatedTime += fElapsedTime;
		//if (fAccumulatedTime >= fTargetFrameTime)
		//{
		//	fAccumulatedTime -= fTargetFrameTime;
		//	fElapsedTime = fTargetFrameTime;
		//}
		//else
		//	return true; // Don't do anything this frame

	/****************************************************
	*                  Level Loading                    *
	****************************************************/

		m_level1->LoadLevel(this, 2, fElapsedTime);
		m_player->DrawSelf(this);

		m_level1->Move_Ships(fElapsedTime, this);
	

	/****************************************************
	*                  User Input                       *
	****************************************************/
		if (GetKey(olc::Key::LEFT).bHeld) 
			m_player->move_left(fElapsedTime);

		if (GetKey(olc::Key::RIGHT).bHeld) 
			m_player->move_right(fElapsedTime);

		if (m_player->get_Pos().x < 11) 
			m_player->Pos_left();

		if ((m_player->get_Pos().x + m_player->get_Width()) > (ScreenWidth() - 11))
			m_player->Pos_right();

		
		return true;
	}

protected: 
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Player> m_player;

};
