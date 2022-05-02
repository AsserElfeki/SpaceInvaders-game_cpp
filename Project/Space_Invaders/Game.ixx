module;

#include "olcPixelGameEngine.h"
#include <future>
#include <thread>
#include <chrono>


//using namespace std::this_thread;     // sleep_for, sleep_until
//using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
//using std::chrono::system_clock;

import FileHandler;
import Credits;
import Level;
import Bullet;

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	//paths
	std::filesystem::path screens_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/sprites/screens/";

	//game units
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Level> m_level2;
	std::unique_ptr <Level> m_level3;
	std::unique_ptr <Level> m_level4;
	std::unique_ptr<Credits> m_credits;
	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;

	//sprites
	std::unique_ptr <olc::Sprite> spr_intro;
	std::unique_ptr <olc::Sprite> spr_name;

	std::unique_ptr <olc::Sprite> spr_instructions;
	std::unique_ptr <olc::Sprite> spr_instructions2;

	std::unique_ptr <olc::Sprite> spr_pause;

	std::unique_ptr <olc::Sprite> spr_won;
	std::unique_ptr <olc::Sprite> spr_lost;
	std::unique_ptr <olc::Sprite> spr_credits_background;


	//others
	std::unique_ptr<FileHandler> scores_handler;

	std::vector<char> player_name;

	enum gameState
	{
		intro = 1,
		instructions,
		name,
		level,
		won,
		pause,
		lost,
		credits,
		quit
	};

	int current_score = 0000;
	gameState current_state = intro;
	int current_level = 1;
	bool score_was_set = false;
	bool writing_score_done = false;

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

		//game units
		m_level1 = std::make_unique<Level>(1, ScreenWidth(), ScreenHeight());
		m_level2 = std::make_unique<Level>(2, ScreenWidth(), ScreenHeight());
		m_level3 = std::make_unique<Level>(3, ScreenWidth(), ScreenHeight());
		m_level4 = std::make_unique<Level>(4, ScreenWidth(), ScreenHeight());

		m_player = std::make_unique<Player>(ScreenWidth(), ScreenHeight());

		m_credits = std::make_unique<Credits>(ScreenWidth(), ScreenHeight());

		//sprites
		spr_intro = std::make_unique<olc::Sprite>(screens_path.string() + "intro.png");
		spr_name = std::make_unique<olc::Sprite>(screens_path.string() + "name.png");
		spr_instructions = std::make_unique<olc::Sprite>(screens_path.string() + "instructions.png");
		spr_pause = std::make_unique<olc::Sprite>(screens_path.string() + "pause.png");
		spr_won = std::make_unique<olc::Sprite>(screens_path.string() + "won.png");
		spr_lost = std::make_unique<olc::Sprite>(screens_path.string() + "lost.png");

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		SetPixelMode(olc::Pixel::MASK);

		/****************************************************
		*                  Level Loading                    *
		****************************************************/
		//std::mutex 

		if (current_state == intro)
		{
			//lock
			Clear(olc::WHITE);
			DrawSprite(0, 0, spr_intro.get());

			if (GetKey(olc::Key::SPACE).bPressed)
				current_state = name;
			//unlock it
		}

		else if (current_state == name)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, spr_name.get());

			for (int i = 0; i < 25; i++)
			{
				int x = int(olc::Key::A + i);
				if (GetKey(olc::Key(x)).bPressed)
					player_name.push_back(x + 64);

			}
			if (GetKey(olc::Key::BACK).bPressed && !player_name.empty())
				player_name.pop_back();

			DrawString(737, 445, std::string(player_name.data(), player_name.size()), olc::BLUE, 2);

			if (GetKey(olc::Key::ENTER).bPressed)
				current_state = instructions;
		}

		else if (current_state == instructions)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, spr_instructions.get());

			if (GetKey(olc::Key::ENTER).bPressed)
				current_state = level;

			if (GetKey(olc::Key::K1).bPressed || GetKey(olc::Key::NP1).bPressed)
			{
				current_level = 1;
				current_state = level;
			}

			else if (GetKey(olc::Key::K2).bPressed || GetKey(olc::Key::NP2).bPressed)
			{
				current_level = 2;
				current_state = level;
			}

			else if (GetKey(olc::Key::K3).bPressed || GetKey(olc::Key::NP3).bPressed)
			{
				current_level = 3;
				current_state = level;
			}

			else if (GetKey(olc::Key::K4).bPressed || GetKey(olc::Key::NP4).bPressed)
			{
				current_level = 4;
				current_state = level;
			}

			if (GetKey(olc::Key::C).bPressed)
				current_state = credits;
		}

		else if (current_state == level)
		{
			if (current_level == 1)
			{
				play(m_level1, fElapsedTime);
			}

			else if (current_level == 2)
			{
				if (!score_was_set)
					m_level2->set_Score(current_score);

				score_was_set = false;

				play(m_level2, fElapsedTime);
			}

			else if (current_level == 3)
			{
				if (!score_was_set)
					m_level3->set_Score(current_score);

				score_was_set = false;
				play(m_level3, fElapsedTime);
			}

			else if (current_level == 4)
			{
				if (!score_was_set)
					m_level4->set_Score(current_score);

				score_was_set = false;
				play(m_level4, fElapsedTime);
			}
		}

		else if (current_state == won)
		{
			if (current_level < 4)
			{
				Clear(olc::WHITE);
				DrawSprite(0, 0, spr_won.get());

				if (GetKey(olc::Key::ENTER).bPressed)
				{
					current_level += 1;
					current_state = level;
				}
			}

			else
				current_state = credits;
		}

		else if (current_state == lost)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, spr_lost.get());

			if (GetKey(olc::Key::ENTER).bPressed)
			{
				if (current_level == 1)
				{
					m_level1->set_Score(0000);
					score_was_set = true;
					m_level1->Create_Ships(1, m_level1->level1_speed);
					m_player->reload();
					current_state = level;
				}

				else if (current_level == 2)
				{
					m_level2->set_Score(m_level1->get_Score());
					score_was_set = true;
					m_level2->Create_Ships(2, m_level1->level2_speed);
					m_player->reload();
					current_state = level;
				}

				else if (current_level == 3)
				{
					m_level3->set_Score(m_level2->get_Score());
					score_was_set = true;
					m_level3->Create_Ships(3, m_level1->level3_speed);
					m_player->reload();
					current_state = level;
				}

				else
				{
					m_level4->set_Score(m_level3->get_Score());
					score_was_set = true;
					m_level4->Create_Ships(4, m_level1->level4_speed);
					m_player->reload();
					current_state = level;
				}
			}
		}

		else if (current_state == credits)
		{
			if (!writing_score_done)
			{
				scores_handler = std::make_unique<FileHandler>(player_name, current_score);
				scores_handler->write();
				writing_score_done = true;
			}

			Clear(olc::BLACK);

			m_credits->run_Credits(this, fElapsedTime);

			if (GetKey(olc::Key::ENTER).bPressed)
			{
				m_level1->set_Score(0000);
				m_level2->set_Score(0000);
				m_level3->set_Score(0000);
				m_level4->set_Score(0000);
				m_level1->Create_Ships(1, m_level1->level1_speed);
				m_level2->Create_Ships(2, m_level2->level2_speed);
				m_level3->Create_Ships(3, m_level3->level3_speed);
				m_level4->Create_Ships(4, m_level4->level4_speed);
				m_player->reload();
				current_level = 1;
				current_state = intro;
			}

			else if (GetKey(olc::Key::C).bHeld)
			{
				Clear(olc::BLACK);
				m_credits->reset();
				m_credits->run_Credits(this, fElapsedTime);
			}
		}

		else if (current_state == pause)
		{
			SetPixelMode(olc::Pixel::ALPHA);
			DrawSprite(0, 0, spr_pause.get());
			if (GetKey(olc::Key::SPACE).bPressed)
			{
				current_state = level;
				SetPixelMode(olc::Pixel::MASK);
			}
		}

		else if (current_state == quit)
		{
			scores_handler = std::make_unique<FileHandler>(player_name, current_score);
			scores_handler->write();
			return false;
		}

		if (GetKey(olc::Key::Q).bHeld && current_state != name)
			current_state = quit;

		return true;
	}

	void userInput(float fElapsedTime)
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

		if (GetKey(olc::Key::Q).bHeld)
			current_state = quit;

		if (GetKey(olc::Key::ESCAPE).bHeld)
			current_state = pause;
	}


	void play(std::unique_ptr<Level>& level, float fElapsedTime)
	{
		level->increase_Score_With_Time(fElapsedTime);
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
							A_bullet.Kill();
							ship.get_AlienBullets().erase(ITR);
							m_player->gotHit();
							level->decrease_Score_When_Health_Decreased();

							if (!m_player->is_exist())
							{
								m_bullets.clear();
								current_state = lost;
							}
						}
					}
					ITR++;
				}
			}
		}

		//collision detection between a player's bullet and alien ship and killing in case of collision
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
							level->increase_Score_When_Hit_Alien();
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
			current_state = won;
		}

		std::future<void> thread1 = std::async(std::launch::async, &SpaceInvaders::userInput, this, fElapsedTime);

		current_score = level->get_Score();
	}

};



//todo:
/*
* ships creation (ughhhhhh)
* 4th thematic task
*/

