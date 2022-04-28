module;

#include "olcPixelGameEngine.h"
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

import Level; 
import Bullet; 
export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Level> m_level2;
	std::unique_ptr <Level> m_level3;
	//std::unique_ptr <Level> m_currentLevel;

	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;
	 

	std::string current_state = "intro"; 
	// other states : "level", "interlevelscreen" , "game over" 
	

	int currentLevel = 1;

	std::unique_ptr<olc::Sprite> alien;

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

	
		m_player->set_Scale(ScreenWidth(), ScreenHeight());
	

		//alien = std::make_unique<olc::Sprite>("./sprites/aliens_1.png");

		return true;
	}
	/* 
	list <level> contianing all levels 
	once all ships in a level are destroyed, destry the level 
	*/

	/*
	scores can be different thread 
	*/

	bool OnUserUpdate(float fElapsedTime) override
	{ 
	/****************************************************
	*                  Level Loading                    *
	****************************************************/

		//DrawSprite(olc::vi2d(100,100), alien.get());

		if (current_state == "intro") 
		{
			Clear(olc::WHITE);
			DrawString(ScreenWidth() / 5, 100, "Welcome to Space Invaders", olc::RED,3);
			DrawString(ScreenWidth() / 5, 300, "Press Enter to start", olc::RED, 3);

			if (GetKey(olc::Key::ENTER).bHeld)
			current_state = "level";
		}

		else if (current_state == "interLevelScreen")
		{
			Clear(olc::WHITE);
			DrawString(ScreenWidth() / 5, 100, "congrats", olc::RED, 3);
			DrawString(ScreenWidth() / 5, 300, "Press Enter to start next level", olc::RED, 3);

			if (GetKey(olc::Key::ENTER).bHeld)
			{
				current_state = "level";
				currentLevel += 1;
			}
		}

		else if (current_state == "level")
		{
			if ( currentLevel == 1)
			{
				play(m_level1, fElapsedTime);
			}

			else if ( currentLevel == 2)
			{
				play(m_level2, fElapsedTime);
			}

			else if ( currentLevel == 3)
			{
				play(m_level3, fElapsedTime);
			}
		}

		
	
	return true;
	}

	//reset player pos


	
	void play(std::unique_ptr<Level>& level, float fElapsedTime)
	{
		auto Itr = m_bullets.begin();

		level->LoadLevel(this, fElapsedTime);
		m_player->DrawSelf(this);

		level->Move_Ships(fElapsedTime, this);

		//collision detection between a bullet and a ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.move_Bullet(fElapsedTime, this);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 4; j++)
				{
					if (level->get_Ships()[i][j].is_exist()) //circle collision
						if (((level->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) * (level->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x))
							+ ((level->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (level->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <=
							((level->get_Ships()[i][j].get_Width()) * (level->get_Ships()[i][j].get_Width())))
						{
							bullet.Kill();
							m_bullets.erase(Itr);
							level->get_Ships()[i][j].Kill();
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

		if (level->is_finished())
		{
			m_bullets.clear(); 
			current_state = "interLevelScreen";
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
	}

};


/*
* threads ???? 
2- sprites 
3- score calculation  
4- score sheet 
*/