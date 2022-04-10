module;

#include "olcPixelGameEngine.h"


import Level; 
import Bullet; 
export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;

public:
	SpaceInvaders()
	{
		sAppName = "Space Invaders "
				   " By: Asser Moustafa";

	}

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

		if (GetKey(olc::Key::SPACE).bPressed)
			m_bullets.emplace_back(this, m_player->get_Pos().x + m_player->get_Width() / 2, m_player->get_Pos().y);


		auto Itr = m_bullets.begin(); 

		for (auto& bullet : m_bullets)
		{
			bullet.move_Bullet(fElapsedTime, this);
			for (int i = 0; i<5; i++)
				for (int j = 0; j < 4; j++)
				{
					if (m_level1->get_Ships()[i][j].is_exist())
						if ( ( (m_level1->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x)  * (m_level1->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) ) 
							+ ((m_level1->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (m_level1->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <= 
							 ( (m_level1->get_Ships()[i][j].get_Width()) * (m_level1->get_Ships()[i][j].get_Width()) ))
						{
							bullet.Kill(); 
							m_bullets.erase(Itr);
							m_level1->get_Ships()[i][j].Kill();
						}
				}
			Itr++;
		}

		for (auto& bullet : m_bullets)
		{
			if (bullet.get_Pos().y < 60)
				m_bullets.pop_front();
		}


		return true;
	}



};
