module;

#include "olcPixelGameEngine.h"


import Level; 
import Bullet; 
export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Level> m_level2;
	std::unique_ptr <Level> m_level3;
	std::unique_ptr <Level> m_currentLevel;

	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;
	 

	int currentLevel = 1;

public:
	SpaceInvaders()
	{
		sAppName = "Space Invaders "
				   " By: Asser Moustafa";

	}

	bool OnUserCreate() override
	{
		// Called once at the start
		/* 
		1- instantiating a player
		2- instantiating a level and player
		3- passing screen params to level 
		4- creating ships 
		*/

		m_level1 = std::make_unique<Level>(1, ScreenWidth(), ScreenHeight());
		m_level2 = std::make_unique<Level>(2, ScreenWidth(), ScreenHeight());
		m_level3 = std::make_unique<Level>(3, ScreenWidth(), ScreenHeight());
		m_player = std::make_unique<Player>();

		//m_level1->set_Scale(ScreenWidth(), ScreenHeight());
		m_player->set_Scale(ScreenWidth(), ScreenHeight());
		//m_level1->Create_Ships(2);


		return true;
	}
	/* 
	list <level> contianing all levels 
	once all ships in a level are destroyed, destry the level 
	*/

	bool OnUserUpdate(float fElapsedTime) override
	{

	/****************************************************
	*                  Level Loading                    *
	****************************************************/
		auto Itr = m_bullets.begin();

		if (currentLevel == 1) 
		{
			m_level1->LoadLevel(this, fElapsedTime);
			m_player->DrawSelf(this);

			m_level1->Move_Ships(fElapsedTime, this);
		}

		else if (currentLevel == 2)
		{
			m_level2->LoadLevel(this, fElapsedTime);
			m_player->DrawSelf(this);

			m_level2->Move_Ships(fElapsedTime, this);
		}

		else if (currentLevel == 3)
		{
			m_level3->LoadLevel(this, fElapsedTime);
			m_player->DrawSelf(this);

			m_level3->Move_Ships(fElapsedTime, this);
		}

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


		if (currentLevel == 1) 
		{
			//collision detection between a bullet and a ship and killing in case of collision
			for (auto& bullet : m_bullets)
			{
				bullet.move_Bullet(fElapsedTime, this);
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 4; j++)
					{
						if (m_level1->get_Ships()[i][j].is_exist()) //circle collision
							if (((m_level1->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) * (m_level1->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x))
								+ ((m_level1->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (m_level1->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <=
								((m_level1->get_Ships()[i][j].get_Width()) * (m_level1->get_Ships()[i][j].get_Width())))
							{
								bullet.Kill();
								m_bullets.erase(Itr);
								m_level1->get_Ships()[i][j].Kill();
							}
					}
				Itr++;
			}

			//if bullet goes out of screen
			for (auto& bullet : m_bullets)
			{
				if (bullet.get_Pos().y < 60)
					m_bullets.pop_front();
			}
			if (m_level1->is_finished())
				currentLevel = 2;
		}

		else if (currentLevel == 2)
		{
			//collision detection between a bullet and a ship and killing in case of collision
			for (auto& bullet : m_bullets)
			{
				bullet.move_Bullet(fElapsedTime, this);
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 4; j++)
					{
						if (m_level2->get_Ships()[i][j].is_exist()) //circle collision
							if (((m_level2->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) * (m_level2->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x))
								+ ((m_level2->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (m_level2->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <=
								((m_level2->get_Ships()[i][j].get_Width()) * (m_level2->get_Ships()[i][j].get_Width())))
							{
								bullet.Kill();
								m_bullets.erase(Itr);
								m_level2->get_Ships()[i][j].Kill();
							}
					}
				Itr++;
			}

			//if bullet goes out of screen
			for (auto& bullet : m_bullets)
			{
				if (bullet.get_Pos().y < 60)
					m_bullets.pop_front();
			}
			if (m_level2->is_finished())
				currentLevel = 3;
		}

		else if (currentLevel == 3)
		{
			//collision detection between a bullet and a ship and killing in case of collision
			for (auto& bullet : m_bullets)
			{
				bullet.move_Bullet(fElapsedTime, this);
				for (int i = 0; i < 5; i++)
					for (int j = 0; j < 4; j++)
					{
						if (m_level3->get_Ships()[i][j].is_exist()) //circle collision
							if (((m_level3->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) * (m_level3->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x))
								+ ((m_level3->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (m_level3->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <=
								((m_level3->get_Ships()[i][j].get_Width()) * (m_level3->get_Ships()[i][j].get_Width())))
							{
								bullet.Kill();
								m_bullets.erase(Itr);
								m_level3->get_Ships()[i][j].Kill();
							}
					}
				Itr++;
			}

			//if bullet goes out of screen
			for (auto& bullet : m_bullets)
			{
				if (bullet.get_Pos().y < 60)
					m_bullets.pop_front();
			}
		}
		

		/*if (currentLevel == 1)
		{
			if (m_level1->is_finished())
			currentLevel = 2;
		}
		else if (currentLevel == 2 && m_level2->is_finished())
			currentLevel = 3;*/

		/*if (currentLevel == 1 && m_level1->get_Ships().size() == 0)
			currentLevel = 2;*/
		return true;
	}



};


/*
1- level instatitiation 
2- sprites 
3- score calculation  
4- score sheet 
*/