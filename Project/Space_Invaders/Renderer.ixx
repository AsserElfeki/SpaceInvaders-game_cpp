module;
#include "olcPixelGameEngine.h"

export import Level; 
export import SpritesManager;

export module Renderer;

export class Renderer {

private: 
	int32_t screenWidth = 1200;
	int32_t screenHeight = 800;
public: 

	void drawLevelBoundary(Level& level, olc::PixelGameEngine* pge)
	{
		// Erase previous frame
		pge->Clear(olc::BLACK);

		/*Boundaries*/
		pge->DrawLine(10, 50, screenWidth - 10, 50, olc::BLUE); //upper HZ line
		pge->DrawLine(10, 50, 10, screenHeight - 10, olc::BLUE); // left V line 
		pge->DrawLine(screenWidth - 10, 50, screenWidth - 10, screenHeight - 10, olc::BLUE); // right V line 		

		pge->DrawString(10, 20, level.getName(), olc::WHITE, 2);
	}

	void drawPlayerAndHealth(std::shared_ptr<Player> player, std::shared_ptr<SpriteManager>& spritesManager, olc::PixelGameEngine* pge)
	{
		if (player->isExist())
		{
			pge->DrawString(500, 20, "Health:", olc::WHITE, 2);

			//total 200 pixels
			if (player->getHealth() == 3)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_3").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_3").get());
			}

			//150
			else if (player->getHealth() == 2)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_2").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_2").get());
			}

			//120
			else if (player->getHealth() == 1)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_1").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_1").get());
			}
		}
	}

	void drawShips(Level& level, std::shared_ptr<SpriteManager> spritesManager, olc::PixelGameEngine* pge) {
		for (auto& shipsrow : level.get_Ships())
			for (auto& ship : shipsrow)
			{
				if (ship.isExist())
				{
					if (ship.getHealth() == 1)
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("alien_1").get());

					else if (ship.getHealth() == 2)
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("alien_2").get());

					else if (ship.getHealth() == 3)
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("alien_3").get());

					else
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("boss").get());
				}
			}
	}

	void drawAlienBullets(Level& level, std::shared_ptr<SpriteManager> spritesManager,olc::PixelGameEngine* pge) {
		for (auto& shipsrow : level.get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				if (ship.isExist())
					for (auto& bullet : ship.getAlienBullets())
						if (bullet.isExist())
							pge->DrawSprite(bullet.getPos().x, bullet.getPos().y, spritesManager->entitySprite("bullet").get());
				//bullet.drawSelf(this);
			}
		}
	}

	void drawPlayerBullets(std::list<Bullet>& bullets, std::shared_ptr<SpriteManager> spritesManager, olc::PixelGameEngine* pge)
	{
		for (auto& bullet : bullets)
		{
			if (bullet.isExist())
				pge->DrawSprite(bullet.getPos().x, bullet.getPos().y, spritesManager->entitySprite("bullet").get());
		}
	}

	void drawScore(int& current_score, olc::PixelGameEngine* pge) {
		pge->DrawString(screenWidth - 200, 20, "Score:" + std::to_string(current_score), olc::WHITE, 2);
	}

	void renderGame(Level& level, std::list<Bullet>& bullets, 
		int& current_score, std::shared_ptr<SpriteManager>& spritesManager, 
		std::shared_ptr<Player> player, olc::PixelGameEngine* pge) {
		
		drawLevelBoundary(level, pge);
		drawPlayerBullets(bullets, spritesManager, pge);
		drawShips(level, spritesManager, pge);
		drawAlienBullets(level, spritesManager, pge);
		drawScore(current_score, pge);
		drawPlayerAndHealth(player, spritesManager, pge);
	}

};