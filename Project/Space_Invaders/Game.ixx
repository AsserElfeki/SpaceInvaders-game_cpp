module;

#include "olcPixelGameEngine.h"
#include <string>
#include <future>
#include <thread>
#include <chrono>


import FileHandler;
import Presentation;
import Credits;
import AliensMovementHandler;
import CollisionDetectionHandler;
import LevelManager;
import Renderer; 

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
private:

	/*unique_ptr for objects that will not be passed to other classes\methods
	shared_ptr for objects that will be passed */

	//game units
	std::unique_ptr<LevelManager> levelManager; 
	std::unique_ptr <Renderer> renderer;
	std::shared_ptr <Player> m_player;
	std::shared_ptr<AliensMovementHandler> aliensMovementHandler;
	std::list<Bullet> m_bullets;
	std::shared_ptr <CollisionDetectionHandler> collisionDetector;
	std::shared_ptr<ScoreHandler> scoreHandler;
	std::unique_ptr<Presentation> m_presentation;
	
	//SpritesManager
	std::shared_ptr<SpriteManager> spritesManager;

	//others
	std::shared_ptr<FileHandler> outputScore;
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
	bool writing_score_done = false; //to not write score twice 

public:
	SpaceInvaders()
	{
		sAppName = "Space Invaders "" By: Asser Moustafa";
		//appears on window bar of the game window (if not in full screen mode)
	}

	bool OnUserCreate() override
	{
		// Called once at the start
		// instantiates all needed game units

		m_presentation = std::make_unique<Presentation>(); //just for presentation in the lab

		//game units
		renderer = std::make_unique<Renderer>();
		levelManager = std::make_unique<LevelManager>();
		m_player = std::make_shared<Player>(ScreenWidth(), ScreenHeight());
		m_credits = std::make_unique<Credits>(ScreenWidth(), ScreenHeight());
		scoreHandler = std::make_shared<ScoreHandler>();
		spritesManager = std::make_shared<SpriteManager>();
		aliensMovementHandler = std::make_shared<AliensMovementHandler>();
		collisionDetector = std::make_shared<CollisionDetectionHandler>();
		return true;
	}


	/****************************************************************
	*                      GamePlay Function
	*****************************************************************/

	void play(Level& level, float fElapsedTime)
	{
		std::future<void> thread1 = std::async(std::launch::async, &SpaceInvaders::handleUserInput, this, fElapsedTime);
		//handling the user input in parallel while the game logic is in another thread
	
		renderer->renderGame(level, m_bullets, current_score, spritesManager, m_player , this);

		aliensMovementHandler->moveShips(fElapsedTime, current_level, level.get_Ships());

		scoreHandler->increaseScoreWithTime(fElapsedTime);

		shootAlienBullets(fElapsedTime, level);

		collisionDetector->detectAllCollisions(fElapsedTime, level, m_player, scoreHandler,m_bullets);

		//if player bullet goes out of screen
		std::future<void> thread2 = std::async(std::launch::async, &SpaceInvaders::checkPlayerBulletsOutScreen, this);

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
				//60 because the upper line of game space is at 50 and bullet is 10px hight
			{
				bullet.kill();
				m_bullets.pop_front();
			}
		}
	}

	void didPlayerLose(Level& level) {
		if (!m_player->isExist())
		{
			m_bullets.clear(); //clear player's bullets
			level.clearAlienBullets(); 
			current_state = lost;
		}
	}

	void didPlayerWin(Level& level) {
		if (level.isFinished())
		{
			m_bullets.clear();
			level.clearAlienBullets();
			m_player->resetPos();
			current_state = won;
		}
	}
	
	void playAgainAfterLoss() {
		if (current_level == 1)
		{
			//levelManager->getLevel("Level 1").createShips();
			current_state = level;
		}

		else if (current_level == 2)
		{
			//levelManager->getLevel("Level 2").createShips();
			current_state = level;
		}

		else if (current_level == 3)
		{
			//levelManager->getLevel("Level 3").createShips();
			current_state = level;
		}

		else
		{
			//levelManager->getLevel("Level 4").createShips();
			current_state = level;
		}
	}

	void playAgainAfterFinished() {
		writing_score_done = false; 
		scoreHandler->resetScores();
		reloadAllLevels();
		m_player->reload();
		m_credits->reset();
		current_level = 1;
		current_state = level;
	}

	void reloadAllLevels() {
		levelManager->getLevel("Level 1").createShips();
		levelManager->getLevel("Level 2").createShips();
		levelManager->getLevel("Level 3").createShips();
		levelManager->getLevel("Level 4").createShips();
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
		//position is hard coded based on the screen dimensions 1200X800 
	}

	void changeGameStateFromInstructions() { 
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
			renderer->drawSprite("intro", this, spritesManager);

			if (GetKey(olc::Key::SPACE).bPressed || GetKey(olc::Key::ENTER).bPressed)
				current_state = name;

			if (GetKey(olc::Key::P).bPressed)
				current_state = presentation;
		}

		else if (current_state == name)
		{
			Clear(olc::WHITE);
			renderer->drawSprite("name", this, spritesManager);

			inputPlayerName();

			if (GetKey(olc::Key::ENTER).bPressed)
				current_state = instructions;
		}

		else if (current_state == instructions)
		{
			Clear(olc::WHITE);
			renderer->drawSprite("instructions", this, spritesManager);
			changeGameStateFromInstructions();
		}

		else if (current_state == level)
			play(levelManager->getLevel("Level " + std::to_string(current_level)), fElapsedTime);

		else if (current_state == won)
		{
			if (current_level < 4)
			{
				Clear(olc::WHITE);
				renderer->drawSprite("won", this, spritesManager);
				scoreHandler->setLastLevelHealth(m_player->getHealth());
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
			renderer->drawSprite("lost", this, spritesManager);
			levelManager->getLevel("Level " + std::to_string(current_level)).createShips();

			scoreHandler->setScore(scoreHandler->lastLevelScore());
			m_player->reload(scoreHandler->getLastLevelHealth());
			if (GetKey(olc::Key::ENTER).bPressed)
				playAgainAfterLoss();
		}

		else if (current_state == credits)
		{
			Clear(olc::BLACK);
			m_credits->runCredits(this, fElapsedTime);

			if (!outputScore)
				outputScore = std::make_unique<FileHandler>(player_name, current_score);
			outputScore->write();

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
			renderer->drawSprite("pause", this, spritesManager);
			if (GetKey(olc::Key::SPACE).bPressed)
			{
				SetPixelMode(olc::Pixel::MASK);
				current_state = level;
			}
		}

		else if (current_state == quit)
		{
			if (!outputScore)
				outputScore = std::make_unique<FileHandler>(player_name, current_score);
			outputScore->write();
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




