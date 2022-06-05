module;

#include "olcPixelGameEngine.h"
#include <string>
#include <future>
#include <thread>
#include <chrono>


import FileHandler;
import Credits;
//import Level;
//import Bullet;
//import SpritesManager;
import ScoreHandler;
import AliensMovementHandler;
import Presentation; 
import CollisionDetectionHandler;
import LevelManager;
import Renderer; 

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:
	//game units
	LevelManager levelManager; 
	Renderer renderer; 
	std::shared_ptr <Player> m_player;
	std::unique_ptr<AliensMovementHandler> aliensMovementHandler;
	std::list<Bullet> m_bullets;
	std::unique_ptr <CollisionDetectionHandler> collisionDetector;
	std::unique_ptr<ScoreHandler> scoreHandler;
	std::unique_ptr<Presentation> m_presentation;

	//SpritesManager
	std::shared_ptr<SpriteManager> spritesManager;

	//others
	std::unique_ptr<FileHandler> outputScore;
	std::unique_ptr <Credits> m_credits;


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
		quit,
		presentation
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
		// instantiates all needed game units


		m_presentation = std::make_unique<Presentation>(); //just for presentation in the lab

		//game units
		m_player = std::make_shared<Player>(ScreenWidth(), ScreenHeight());
		m_credits = std::make_unique<Credits>(ScreenWidth(), ScreenHeight());
		scoreHandler = std::make_unique<ScoreHandler>();
		spritesManager = std::make_shared<SpriteManager>();
		aliensMovementHandler = std::make_unique<AliensMovementHandler>();
		collisionDetector = std::make_unique<CollisionDetectionHandler>();
		return true;
	}


	/****************************************************************
	*                      GamePlay Function
	*****************************************************************/

	void play(Level& level, float fElapsedTime)
	{
		std::future<void> thread1 = std::async(std::launch::async, &SpaceInvaders::handleUserInput, this, fElapsedTime);
	
		renderer.drawLevel(level, m_bullets, current_score, spritesManager, m_player , this);

		aliensMovementHandler->moveShips(fElapsedTime, current_level, level.get_Ships());

		scoreHandler->increaseScoreWithTime(fElapsedTime);

		shootAlienBullets(fElapsedTime, level);

		collisionDetector->detectAllCollisions(fElapsedTime, level, m_player, scoreHandler,m_bullets);

		//if player bullet goes out of screen
		checkPlayerBulletsOutScreen();

		//check player lost
		didPlayerLose(level);

		//if all aliens are dead : go to next level
		didPlayerWin(level);

		current_score = scoreHandler->getScore();
	}


	/****************************************************************
	*                 Helper Functions used in Game
	*****************************************************************/

	void handleUserInput(float fElapsedTime)
	{
		if (GetKey(olc::Key::LEFT).bHeld)
			m_player->moveLeft(fElapsedTime);

		if (GetKey(olc::Key::RIGHT).bHeld)
			m_player->moveRight(fElapsedTime);

		if (m_player->getPos().x < 11)
			m_player->maxPosLeft();

		if ((m_player->getPos().x + m_player->getWidth()) > (ScreenWidth() - 11))
			m_player->maxPosRight();

		if (GetKey(olc::Key::SPACE).bPressed)
		{
			if (m_player->isExist())
				m_bullets.emplace_back(m_player->getPos().x + (m_player->getWidth() / 2) -4, m_player->getPos().y);
		}

		if (GetKey(olc::Key::Q).bHeld)
			current_state = quit;

		if (GetKey(olc::Key::ESCAPE).bHeld)
			current_state = pause;
	}
	
	void shootAlienBullets(float fElapsedTime, Level& level)
	{
		for (auto& shipsrow : level.get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				ship.shoot();
				ship.moveAlienBullet(fElapsedTime);
			}
		}
	}

	void checkPlayerBulletsOutScreen() {
		for (auto& bullet : m_bullets)
		{
			if (bullet.getPos().y < 60)
			{
				bullet.kill();
				m_bullets.pop_front();
			}
		}
	}

	void didPlayerLose(Level& level) {
		if (!m_player->isExist())
		{
			m_bullets.clear();
			level.clearAlienBullets();
			current_state = lost;
		}
	}

	void didPlayerWin(Level& level) {
		if (level.isFinished())
		{
			m_bullets.clear();
			level.clearAlienBullets();
			m_player->setPlayerPos(ScreenWidth(), ScreenHeight());
			current_state = won;
		}
	}
	
	void playAgainAfterLoss() {
		if (current_level == 1)
		{
			scoreHandler->resetScores();
			score_was_set = true;
			levelManager.getLevel("Level 1").createShips();
			m_player->reload();
			current_state = level;
		}

		else if (current_level == 2)
		{
			scoreHandler->setScore(scoreHandler->lastLevelScore());
			score_was_set = true;
			levelManager.getLevel("Level 2").createShips();
			m_player->reload();
			current_state = level;
		}

		else if (current_level == 3)
		{
			scoreHandler->setScore(scoreHandler->lastLevelScore());
			score_was_set = true;
			levelManager.getLevel("Level 3").createShips();
			m_player->reload();
			current_state = level;
		}

		else
		{
			scoreHandler->setScore(scoreHandler->lastLevelScore());
			score_was_set = true;
			levelManager.getLevel("Level 4").createShips();
			m_player->reload();
			current_state = level;
		}
	}

	void playAgainAfterFinished() {
		scoreHandler->resetScores();
		reloadAllLevels();
		m_player->reload();
		m_credits->reset();
		current_level = 1;
		current_state = level;
	}

	void reloadAllLevels() {
		levelManager.getLevel("Level 1").createShips();
		levelManager.getLevel("Level 2").createShips();
		levelManager.getLevel("Level 3").createShips();
		levelManager.getLevel("Level 4").createShips();

	}


	/****************************************************************
	*             functions used in opther game states
	*****************************************************************/
	
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
			play(levelManager.getLevel("Level 1"), fElapsedTime);

		else if (current_level == 2)
			play(levelManager.getLevel("Level 2"), fElapsedTime);

		else if (current_level == 3)
			play(levelManager.getLevel("Level 3"), fElapsedTime);

		else if (current_level == 4)
			play(levelManager.getLevel("Level 4"), fElapsedTime);
	}


	/****************************************************************
	*                          Game Loop
	*****************************************************************/

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

			if (GetKey(olc::Key::P).bPressed)
				current_state = presentation;
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
				scoreHandler->setLastLevelScore(scoreHandler->getScore());
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
			scoreHandler->setScore(scoreHandler->lastLevelScore());
			if (GetKey(olc::Key::ENTER).bPressed)
				playAgainAfterLoss();
		}

		else if (current_state == credits)
		{
			Clear(olc::BLACK);
			m_credits->runCredits(this, fElapsedTime);

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
				m_credits->runCredits(this, fElapsedTime);
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
			if (!writing_score_done)
			{
				outputScore = std::make_unique<FileHandler>(player_name, current_score);
				outputScore->write();
			}
			
			return false;
		}

		else if (current_state == presentation)
		{
			Clear(olc::WHITE);
			m_presentation->runPresentation(this);

			if (GetKey(olc::Key::ESCAPE).bPressed)
				current_state = intro; 
		}

		if (GetKey(olc::Key::Q).bHeld && current_state != name)
			current_state = quit;

		return true;
	}
};




