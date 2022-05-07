module;

#include "olcPixelGameEngine.h"
#include <string>
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
import SpritesManager;
import ScoreHandler;

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	//paths
	std::filesystem::path screens_path = "./sprites/screens/";

	//game units
	std::unique_ptr <Level> m_level1;
	std::unique_ptr <Level> m_level2;
	std::unique_ptr <Level> m_level3;
	std::unique_ptr <Level> m_level4;
	std::unique_ptr<Credits> m_credits;
	std::unique_ptr <Player> m_player;
	std::list<Bullet> m_bullets;
	std::unique_ptr<ScoreHandler> scoreHandler; 

	//SpritesManager
	std::unique_ptr<SpriteManager> spritesManager;

	//others
	std::unique_ptr<FileHandler> outputScore;

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
		sAppName = "Space Invaders "" By: Asser Moustafa";
	}

	bool OnUserCreate() override
	{
		// Called once at the start
		/* RESPONSIBLE FOR:
		1- instantiating a player obj
		2- instantiating all levels obj -> because there is only one 
		   function that runs one time OnUserCreate() 
		   so the have to be instantiated here, the other option to enhance scalability 
		   would be a level manager but this will add unnecessary complexity to such a small game. 
		3- instantiatiing credits obj
		
		*/

		scoreHandler = std::make_unique<ScoreHandler>();

		spritesManager = std::make_unique<SpriteManager>();

		//game units
		m_level1 = std::make_unique<Level>(1, ScreenWidth(), ScreenHeight());
		m_level2 = std::make_unique<Level>(2, ScreenWidth(), ScreenHeight());
		m_level3 = std::make_unique<Level>(3, ScreenWidth(), ScreenHeight());
		m_level4 = std::make_unique<Level>(4, ScreenWidth(), ScreenHeight());

		m_player = std::make_unique<Player>(ScreenWidth(), ScreenHeight());

		m_credits = std::make_unique<Credits>(ScreenWidth(), ScreenHeight());

		return true;
	}

	void drawScore() {
		DrawString(ScreenWidth() - 200, 20, "Score:" + std::to_string(current_score), olc::WHITE, 2);
	}

	void inputPlayerName() {
		for (int i = 0; i < 25; i++)
		{
			int x = int(olc::Key::A + i);
			if (GetKey(olc::Key(x)).bPressed)
				player_name.push_back(x + 64);

		}
		if (GetKey(olc::Key::BACK).bPressed && !player_name.empty())
			player_name.pop_back();

		DrawString(737, 445, std::string(player_name.data(), player_name.size()), olc::BLUE, 2);
	}

	void changeGameState() {
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

	void goToLevel(float fElapsedTime) {
		if (current_level == 1)
			play(m_level1, fElapsedTime);

		else if (current_level == 2)
			play(m_level2, fElapsedTime);

		else if (current_level == 3)
			play(m_level3, fElapsedTime);

		else if (current_level == 4)
			play(m_level4, fElapsedTime);
	}

	void play(std::unique_ptr<Level>& level, float fElapsedTime)
	{
		std::future<void> thread1 = std::async(std::launch::async, &SpaceInvaders::userInput, this, fElapsedTime);

		level->LoadLevel(this, fElapsedTime);
		m_player->DrawPlayer(this);
		drawScore(); 

		level->MoveShips_h(fElapsedTime, this, current_level);
		level->MoveShips_v(fElapsedTime, this, current_level);
		scoreHandler->increase_Score_With_Time(fElapsedTime);

		drawShips(level);

		auto Itr = m_bullets.begin();

		//collision detection between a player's bullet and alien ship and killing in case of collision
		playerBulletVsAlien(fElapsedTime, level);

		//collision detection between player and aliens bullets 
		alienBulletVsPlayer(fElapsedTime, level);

		//collision detection between player and alien itself 
		alienShipVsPlayerShip(fElapsedTime, level);

		//if player bullet goes out of screen
		checkPlayerBulletsOutScreen();

		//check player lost
		didPlayerLose();

		//if all aliens are dead : go to next level
		didPlayerWin(level);

		current_score = scoreHandler->get_Score();
	}

	void playAgainAfterLoss() {
		if (current_level == 1)
		{
			scoreHandler->reset_scores();
			score_was_set = true;
			m_level1->Create_Ships(1, m_level1->level1_speed);
			m_player->reload();
			current_state = level;
		}

		else if (current_level == 2)
		{
			scoreHandler->set_Score(scoreHandler->lastLevelScore());
			score_was_set = true;
			m_level2->Create_Ships(2, m_level1->level2_speed);
			m_player->reload();
			current_state = level;
		}

		else if (current_level == 3)
		{
			scoreHandler->set_Score(scoreHandler->lastLevelScore());
			score_was_set = true;
			m_level3->Create_Ships(3, m_level1->level3_speed);
			m_player->reload();
			current_state = level;
		}

		else
		{
			scoreHandler->set_Score(scoreHandler->lastLevelScore());
			score_was_set = true;
			m_level4->Create_Ships(4, m_level1->level4_speed);
			m_player->reload();
			current_state = level;
		}
	}


	void reloadAllLevels() {
		m_level1->Create_Ships(1, m_level1->level1_speed);
		m_level2->Create_Ships(2, m_level2->level2_speed);
		m_level3->Create_Ships(3, m_level3->level3_speed);
		m_level4->Create_Ships(4, m_level4->level4_speed);
	}

	void playAgainAfterFinished() {
		scoreHandler->reset_scores();
		reloadAllLevels();
		m_player->reload();
		m_credits->reset();
		current_level = 1;
		current_state = level;
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

		if (GetKey(olc::Key::SPACE).bHeld)
		{
			if (m_player->is_exist())
				m_bullets.emplace_back(this, m_player->get_Pos().x + m_player->get_Width() / 2, m_player->get_Pos().y);
		}

		if (GetKey(olc::Key::Q).bHeld)
			current_state = quit;

		if (GetKey(olc::Key::ESCAPE).bHeld)
			current_state = pause;
	}

	void drawShips(std::unique_ptr<Level>& level) {
		for (auto& shipsrow : level->get_Ships())
			for (auto& ship : shipsrow)
				ship.DrawShip(this);
	}

	void playerBulletVsAlien(float fElapsedTime, std::unique_ptr<Level>& level)
	{
		auto Itr = m_bullets.begin();

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
							scoreHandler->increase_Score_When_Hit_Alien();
						}
				}
			Itr++;
		}
	}

	void alienBulletVsPlayer(float fElapsedTime, std::unique_ptr<Level>& level)
	{
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
					//check hit
					if (A_bullet.get_Pos().y + 10 >= m_player->get_Pos().y)
					{
						if (A_bullet.get_Pos().x >= m_player->get_Pos().x && A_bullet.get_Pos().x <= (m_player->get_Pos().x + m_player->get_Width()))
						{
							A_bullet.Kill();
							ship.get_AlienBullets().erase(ITR);
							m_player->playerGotHit();
							scoreHandler->decrease_Score_When_Health_Decreased();

							//chech bullet outta screen
							if (A_bullet.get_Pos().y + 10 >= ScreenHeight())
							{
								A_bullet.Kill();
								ship.get_AlienBullets().erase(ITR);
							}
						}
					}
					ITR++;
				}
			}
		}
	}

	void alienShipVsPlayerShip(float fElapsedTime, std::unique_ptr<Level>& level)
	{
		//collision detection between player and alien itself 
		for (auto& shipsrow : level->get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				if (ship.is_exist())
					if (ship.get_Pos().y + ship.get_Height() >= m_player->get_Pos().y && ship.get_Pos().y <= m_player->get_Pos().y + m_player->get_Height()
						&& ship.get_Pos().x + ship.get_Width() >= m_player->get_Pos().x && ship.get_Pos().x <= m_player->get_Pos().x + m_player->get_Width())
					{
						m_player->playerGotHit();
						ship.gotHit();
						scoreHandler->decrease_Score_When_Health_Decreased();
					}
			}
		}
	}

	void checkPlayerBulletsOutScreen() {
		for (auto& bullet : m_bullets)
		{
			if (bullet.get_Pos().y < 60)
			{
				bullet.Kill();
				m_bullets.pop_front();
			}
		}
	}

	void didPlayerLose() {
		if (!m_player->is_exist())
		{
			m_bullets.clear();
			current_state = lost;
		}
	}

	void didPlayerWin(std::unique_ptr<Level>& level) {
		if (level->is_finished())
		{
			m_bullets.clear();
			level->clearAlienBullets();
			m_player->set_Player_Pos(ScreenWidth(), ScreenHeight());
			current_state = won;
		}
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		SetPixelMode(olc::Pixel::MASK);

		/****************************************************
		*                  Checking Game State              *
		****************************************************/

		if (current_state == intro)
		{
			Clear(olc::WHITE);
			DrawSprite(0,0, spritesManager->screenSprite("intro").get());

			if (GetKey(olc::Key::SPACE).bPressed || GetKey(olc::Key::ENTER).bPressed)
				current_state = name;
		}

		else if (current_state == name)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, spritesManager->screenSprite("name").get());

			inputPlayerName();

			if (GetKey(olc::Key::ENTER).bPressed)
				current_state = instructions;
		}

		else if (current_state == instructions)
		{
			Clear(olc::WHITE);
			DrawSprite(0, 0, spritesManager->screenSprite("instructions").get());

			changeGameState();
		}

		else if (current_state == level)
			goToLevel(fElapsedTime);

		else if (current_state == won)
		{
			if (current_level < 4)
			{
				Clear(olc::WHITE);
				DrawSprite(0, 0, spritesManager->screenSprite("won").get());
				scoreHandler->setLastLevelScore(scoreHandler->get_Score());
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
			DrawSprite(0, 0, spritesManager->screenSprite("lost").get());
			scoreHandler->set_Score(scoreHandler->lastLevelScore());
			if (GetKey(olc::Key::ENTER).bPressed)
				playAgainAfterLoss();
		}

		else if (current_state == credits)
		{
			Clear(olc::BLACK);
			m_credits->run_Credits(this, fElapsedTime);

			if (!writing_score_done)
			{
				outputScore = std::make_unique<FileHandler>(player_name, current_score);
				outputScore->write();
				writing_score_done = true;
			}

			if (GetKey(olc::Key::ENTER).bPressed)
				playAgainAfterFinished();

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
			DrawSprite(0, 0, spritesManager->screenSprite("pause").get());
			if (GetKey(olc::Key::SPACE).bPressed)
			{
				SetPixelMode(olc::Pixel::MASK);
				current_state = level;
			}
		}

		else if (current_state == quit)
		{
			outputScore = std::make_unique<FileHandler>(player_name, current_score);
			outputScore->write();
			return false;
		}

		if (GetKey(olc::Key::Q).bHeld && current_state != name)
			current_state = quit;

		return true;
	}

	
	

};


//BUGS:
/*
* bullets and ships cant be in sprite manager
*/

//questions: 
/*
* 1- it crashes in debug mode !? 
*/




//todo:
/*
* clean level code 
* 4th thematic task : ranges in move ships
* level manager ? 
* presentation class? 
*/

