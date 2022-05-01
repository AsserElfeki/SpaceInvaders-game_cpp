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

	//levels
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Level> m_level2;
	std::unique_ptr <Level> m_level3;
	std::unique_ptr <Level> m_level4;


	//sprites
	std::unique_ptr <olc::Sprite> m_intro;
	std::unique_ptr <olc::Sprite> m_instructions;
	std::unique_ptr <olc::Sprite> m_instructions2;
	std::unique_ptr <olc::Sprite> m_credits1;
	std::unique_ptr <olc::Sprite> m_credits2;
	std::unique_ptr <olc::Sprite> m_credits3;
	std::unique_ptr <olc::Sprite> m_credits4;
	std::unique_ptr <olc::Sprite> m_credits5;
	std::unique_ptr <olc::Sprite> m_credits6;
	std::unique_ptr <olc::Sprite> m_credits7;
	std::unique_ptr <olc::Sprite> m_congrats;
	std::unique_ptr <olc::Sprite> m_next;




	std::unique_ptr <olc::Sprite> m_gameOver;
	std::unique_ptr <olc::Sprite> m_startAgain;
	//std::unique_ptr <olc::Sprite> m_intro;
	//std::unique_ptr <olc::Sprite> m_intro;



	//entities
	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;


	std::string player_name;

	enum gameState {
		intro = 1,
		level,  //2 ... 
		won, //3
		interLevelScreen, //4
		finished, //5
		gameOver, //6
		quit, //7
		credits //8
	};

	int current_state = intro;
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

		//entities
		m_level1 = std::make_unique<Level>(1, ScreenWidth(), ScreenHeight());
		m_level2 = std::make_unique<Level>(2, ScreenWidth(), ScreenHeight());
		m_level3 = std::make_unique<Level>(3, ScreenWidth(), ScreenHeight());
		m_level4 = std::make_unique<Level>(4, ScreenWidth(), ScreenHeight());

		m_player = std::make_unique<Player>(ScreenWidth(), ScreenHeight());

		//sprites
		m_intro = std::make_unique<olc::Sprite>("./sprites/intro.png");
		m_instructions = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/instructions.png");
		m_instructions2 = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/instructions2.png");
		m_credits1 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/01_original.png");
		m_credits2 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/02_mockup.png");
		m_credits3 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/03_GUI.png");
		m_credits4 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/04_link.png");
		m_credits5 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/05_thanks.png");
		m_credits6 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/06_michal.png");
		//m_credits7 = std::make_unique<olc::Sprite>("./sprites/text_sprites/credits/01_original.png");
		m_gameOver = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/game_over.png");
		m_startAgain = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/start_again.png");
		m_congrats = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/congrats.png");
		m_next = std::make_unique<olc::Sprite>("./sprites/text_sprites/texts/next.png");



		return true;
	}

	/*
	scores can be different thread
	*/

	bool OnUserUpdate(float fElapsedTime) override
	{
		SetPixelMode(olc::Pixel::MASK);

		/****************************************************
		*                  Level Loading                    *
		****************************************************/

		if (current_state == intro)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 50, m_intro.get());
			DrawSprite(0, 400, m_instructions.get());
			DrawSprite(0, 500, m_instructions2.get());


			if (GetKey(olc::Key::K1).bHeld || GetKey(olc::Key::NP1).bHeld)
			{
				currentLevel = 1;
				current_state = level;
			}

			else if (GetKey(olc::Key::K2).bHeld || GetKey(olc::Key::NP2).bHeld)
			{
				currentLevel = 2;
				current_state = level;
			}

			else if (GetKey(olc::Key::K3).bHeld || GetKey(olc::Key::NP3).bHeld)
			{
				currentLevel = 3;
				current_state = level;
			}

			else if (GetKey(olc::Key::K4).bHeld || GetKey(olc::Key::NP4).bHeld)
			{
				currentLevel = 4;
				current_state = level;
			}

			if (GetKey(olc::Key::Q).bHeld)
				return false;

			if (GetKey(olc::Key::C).bHeld)
				current_state = credits;

			/*DrawString(20, 450, "Please Enter your name", olc::RED, 2);
			DrawString(ScreenWidth() / 2 - 150, 700, "Press Enter to start", olc::BLACK, 2);*/



			//std::string tmp;
			//for (int i = 0; i < 25; i++)
			//{
			//	int x = int(olc::Key::A + i);
			//	if (GetKey(olc::Key(x)).bPressed)
			//		player_name += x + 64;
			//	/*if (GetKey(olc::Key::BACK).bPressed)
			//		player_name -= x + 64; */
			//}
			//DrawString(ScreenWidth() / 4, 500, player_name, olc::BLUE, 2);

			if (GetKey(olc::Key::ENTER).bHeld)
			{
				current_state = level;

			}
		}

		else if (current_state == level)
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

			else if (currentLevel == 4)
			{
				play(m_level4, fElapsedTime);
			}
		}

		else if (current_state == won)
		{
			if (currentLevel != 4)
				current_state = interLevelScreen;
			else
				current_state = finished;
		}

		else if (current_state == interLevelScreen)
		{
			if (currentLevel < 4)
			{
				Clear(olc::WHITE);
				DrawSprite(0, 300, m_congrats.get());
				DrawSprite(0, 500, m_next.get());
				/*DrawString(ScreenWidth() / 5, 100, "congrats", olc::RED, 3);
				DrawString(ScreenWidth() / 5, 300, "Press Enter to start next level", olc::RED, 3);*/

				if (GetKey(olc::Key::ENTER).bHeld)
				{
					currentLevel += 1;
					current_state = level;
				}
			}

			else
				current_state = credits;
		}

		else if (current_state == finished)
		{
			return false;
		}

		else if (current_state == gameOver)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 200, m_gameOver.get());
			DrawSprite(0, 400, m_startAgain.get());
			/*DrawString(ScreenWidth() / 8 * 3, ScreenHeight() / 3, "GAME OVER", olc::RED, 3);
			DrawString(ScreenWidth() / 4, ScreenHeight() / 8 * 5, "Press Enter to start again", olc::BLACK, 2);
			DrawString(ScreenWidth() / 4, ScreenHeight() / 8 * 6, "Press 'q' to quit", olc::BLACK, 2);*/

			if (GetKey(olc::Key::ENTER).bHeld)
			{
				if (currentLevel == 1)
				{
					m_level1->Create_Ships(1, m_level1->level1_speed);
					m_player->reload();
					current_state = level;
				}

				else if (currentLevel == 2)
				{
					m_level2->Create_Ships(2, m_level1->level1_speed);
					m_player->reload();
					current_state = level;
				}

				else if (currentLevel == 3)
				{
					m_level3->Create_Ships(3, m_level1->level1_speed);
					m_player->reload();
					current_state = level;
				}

				else
				{
					m_level4->Create_Ships(4, m_level1->level1_speed);
					m_player->reload();
					current_state = level;
				}
			}

			if (GetKey(olc::Key::Q).bHeld)
				current_state = quit;
		}

		else if (current_state == quit)
			return false;

		else if (current_state == credits)
		{
		Clear(olc::BLACK);
		DrawSprite(0, 0, m_credits1.get());
		DrawSprite(0, 180, m_credits2.get());
		DrawSprite(0, 330, m_credits3.get());
		DrawSprite(0, 500, m_credits4.get());
		DrawSprite(0, 600, m_credits5.get());
		DrawSprite(0, 700, m_credits6.get());
		}

		return true;
	}


	void runCredits() {
		
		for (int i = 600; i > 300; i--)
		{
			
		}
	}

	void play(std::unique_ptr<Level>& level, float fElapsedTime)
	{
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
								current_state = gameOver;
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
					if (level->get_Ships()[i][j].is_exist()) //circle collision
						if (((level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x) *
							(level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x)) +
							((level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y) *
								(level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y)) <=
							level->get_Ships()[i][j].get_Width() / 2 * level->get_Ships()[i][j].get_Width() / 2)
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
			current_state = interLevelScreen;

		}

		/****************************************************
		*                  User Input                       *
		****************************************************/

		{
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

			//quit
		}
	}

};


/*
* threads : score
* filesystem : score sheet
* regex : name ?
2- sprites :  texts + moving credits
3- score calculation
4- score sheet
*/