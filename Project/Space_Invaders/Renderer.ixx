module;
#include "olcPixelGameEngine.h"

//export import Player
export import Level; 
//export import Ship;
export import SpritesManager;

export module Renderer;

export class Renderer {

private: 
	double screenWidth = 1200;
	double screenHeight = 800; 
public: 

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

	void drawLevel(Level& level, std::list<Bullet>& bullets, 
		int& current_score, std::shared_ptr<SpriteManager>& spritesManager, 
		std::shared_ptr<Player> player, olc::PixelGameEngine* pge) {
		
		drawPlayerBullets(bullets, spritesManager, pge);
		drawShips(level, spritesManager, pge);
		drawAlienBullets(level, spritesManager, pge);
		drawScore(current_score, pge);
		drawPlayerAndHealth(player, spritesManager, pge);
	}

};