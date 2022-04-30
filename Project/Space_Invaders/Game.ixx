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

	std::unique_ptr <olc::Sprite> intro;

	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;
	
	std::string current_state = "intro"; 

	int currentLevel = 1;
	std::string player_name;


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
		m_player = std::make_unique<Player>(ScreenWidth(), ScreenHeight());
		intro = std::make_unique<olc::Sprite>("./sprites/intro.png");

	
		//m_player->set_Scale(ScreenWidth(), ScreenHeight());
	

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
		SetPixelMode(olc::Pixel::MASK);

	/****************************************************
	*                  Level Loading                    *
	****************************************************/

		//DrawSprite(olc::vi2d(100,100), alien.get());

		if (current_state == "intro")
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, intro.get());
			DrawString(ScreenWidth() / 8, 450, "Please Enter your name", olc::RED, 3);
			DrawString(ScreenWidth() / 8, 700, "Press Enter to start", olc::BLACK, 2);

			if (GetKey(olc::Key::ENTER).bHeld)
				current_state = "level";

			for (int i = 0; i <25; i++)
			{
				int x = int (olc::Key::A + i);
				if (GetKey(olc::Key(x)).bPressed)
					player_name += x + 64;
			}
			DrawString(ScreenWidth() / 5, 500, player_name, olc::BLUE, 2);

			//if (GetKey(olc::Key::A).bHeld)
			//{
			//	//display and save
			//}
			////repeat for all letters 
		}

		else if (current_state == "level")
		{
			if (currentLevel == 1)
			{
				play(m_level1, fElapsedTime);
			}

			else if (currentLevel == 2)
			{
				play(m_level2, fElapsedTime);
			}

			else if (currentLevel == 3)
			{
				play(m_level3, fElapsedTime);
			}
		}

		else if (current_state == "won")
		{
			if (currentLevel != 3)
				current_state = "interLevelScreen";
			else
				current_state = "finished";
		}

		else if (current_state == "interLevelScreen")
		{
			//m_alienBullets.clear();
			Clear(olc::WHITE);
			DrawString(ScreenWidth() / 5, 100, "congrats", olc::RED, 3);
			DrawString(ScreenWidth() / 5, 300, "Press Enter to start next level", olc::RED, 3);

			if (GetKey(olc::Key::ENTER).bHeld)
			{
				currentLevel += 1;
				current_state = "level";
			}
		}

		else if (current_state == "finished")
		{
			return false;
		}

		else if (current_state == "gameover")
		{
			Clear(olc::WHITE);
			DrawString(ScreenWidth() / 5, 100, "GAME OVER", olc::RED, 3);
			DrawString(ScreenWidth() / 5, 300, "Press Enter to start again", olc::RED, 3);
			DrawString(ScreenWidth() / 5, 500, "Press 'q' to quit", olc::RED, 3);

			if (GetKey(olc::Key::ENTER).bHeld)
			{
				//currentLevel = 1;
				if (currentLevel == 1)
				{
					m_level1->Create_Ships(1, 250.0f);
					m_player->reload();
					current_state = "level";
				}

				else if (currentLevel == 2)
				{
					m_level2->Create_Ships(2, 350.0f);
					m_player->reload();
					current_state = "level";
				}
				
				else
				{
					m_level3->Create_Ships(3, 450.0f);
					m_player->reload();
					current_state = "level";
				}
			}

			if (GetKey(olc::Key::Q).bHeld)
			{
				current_state = "quit";
				//currentLevel = 1;
			}
		}

		else if (current_state == "quit")
			return false; 
		
		//SetPixelMode(olc::Pixel::NORMAL);

	return true;
	}

	
	void play(std::unique_ptr<Level>& level, float fElapsedTime)
	{
		//level->Create_Ships();
		auto Itr = m_bullets.begin();

		level->LoadLevel(this, fElapsedTime);
		m_player->DrawSelf(this);

		level->Move_Ships(fElapsedTime, this);
		
		//collision detection between player and aliens bullets
		for (auto& shipsrow : level->get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				ship.shoot(this);
				ship.move_AlienBullet(fElapsedTime, this);
				auto ITR = ship.get_AlienBullets().begin();
				for (auto A_bullet : ship.get_AlienBullets())
				{
					if (A_bullet.get_Pos().y + 10 >= m_player->get_Pos().y)
					{
						if (A_bullet.get_Pos().x >= m_player->get_Pos().x && A_bullet.get_Pos().x <= (m_player->get_Pos().x + m_player->get_Width()))
						{
							std::cout << A_bullet.is_exist() << std::endl;
							A_bullet.Kill();
							ship.get_AlienBullets().erase(ITR);
							m_player->gotHit();
							std::cout << A_bullet.is_exist() << std::endl;

							if (!m_player->is_exist())
							{
								m_bullets.clear();
								current_state = "gameover";
							}
						}	
					}
					ITR++;
				}
				
			}
		}


		//collision detection between a bullet and alien ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.move_PlayerBullet(fElapsedTime, this);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 4; j++)
				{
					/*std::cout << "position of ship " << i << " , " << j << " is: {" << level->get_Ships()[i][j].get_Pos().x << " , " << level->get_Ships()[i][j].get_Pos().y << " }\n";
					std::cout << "center of ship is: {" << std::to_string(level->get_Ships()[i][j].get_Center().x) << " , " << std::to_string(level->get_Ships()[i][j].get_Center().y) << " }\n";
					std::cout << "distance of ship to bullet is: "
						<< std::to_string(((level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x) *
							(level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x))
							+ ((level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y) *
								(level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y))) << std::endl;*/
					
					//std::cout << "radius is: " << std::to_string((level->get_Ships()[i][j].get_Width() / 2) * (level->get_Ships()[i][j].get_Width() / 2)) << std::endl;

					if (level->get_Ships()[i][j].is_exist()) //circle collision
						if (((level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x) * 
							(level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x)) + 
							((level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y) * 
								(level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y)) <=
							 level->get_Ships()[i][j].get_Width() /2 * level->get_Ships()[i][j].get_Width() /2)
						{
  							bullet.Kill();
							m_bullets.erase(Itr);
							level->get_Ships()[i][j].gotHit();
						}
					//for some reason it doesnt work
					//if (level->get_Ships()[i][j].is_exist()) //rectangle collision 
					//	if (bullet.get_Pos().y <= level->get_Ships()[i][j].get_Pos().y + 50)
					//		if (bullet.get_Pos().x >= level->get_Ships()[i][j].get_Pos().x
					//			&& bullet.get_Pos().x <= level->get_Ships()[i][j].get_Pos().x + 60)
						
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
			level->clearAlienBullets();
			m_player->set_Player_Pos(ScreenWidth(), ScreenHeight());
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
		{
			if (m_player->is_exist())
			m_bullets.emplace_back(this, m_player->get_Pos().x + m_player->get_Width() / 2, m_player->get_Pos().y);
		}
	}

};


/*
* threads ???? 
2- sprites 
3- score calculation  
4- score sheet 
*/