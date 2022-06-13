module;
#include "olcPixelGameEngine.h"
#include "Constants.h"

export import Level; 
export import SpritesManager;

export module Renderer;

export class Renderer {

private: 
	/*int screenWidth = screenConsts::ScreenWidth;
	int screenHeight = screenConsts::ScreenHeight;*/

public: 
	void drawSprite(std::string sprName, olc::PixelGameEngine* pge, 
		std::shared_ptr<SpriteManager>& spritesManager) {
		pge->DrawSprite(0, 0, spritesManager->screenSprite(sprName).get()); 
	}

	void drawLevelBoundary(Level& level, olc::PixelGameEngine* pge)
	{
		// Erase previous frame
		pge->Clear(olc::BLACK);

		/*Boundaries*/
		pge->DrawLine(screenConsts::playAreaBorder_hzPadding, screenConsts::playAreaBorder_vrPadding, screenConsts::ScreenWidth - screenConsts::playAreaBorder_hzPadding, screenConsts::playAreaBorder_vrPadding, olc::BLUE); //upper HZ line
		pge->DrawLine(screenConsts::playAreaBorder_hzPadding, screenConsts::playAreaBorder_vrPadding, screenConsts::playAreaBorder_hzPadding, screenConsts::ScreenHeight - screenConsts::playAreaBorder_hzPadding, olc::BLUE); // left V line 
		pge->DrawLine(screenConsts::ScreenWidth - screenConsts::playAreaBorder_hzPadding, screenConsts::playAreaBorder_vrPadding, screenConsts::ScreenWidth - screenConsts::playAreaBorder_hzPadding, screenConsts::ScreenHeight - screenConsts::playAreaBorder_hzPadding, olc::BLUE); // right V line 		

		pge->DrawString(screenConsts::playAreaBorder_hzPadding, screenConsts::levelInfo_vrPadding, level.getName(), olc::WHITE, screenConsts::fontScale);
	}

	void drawPlayerAndHealth(std::shared_ptr<Player> player, 
		std::shared_ptr<SpriteManager>& spritesManager, olc::PixelGameEngine* pge)
	{
		if (player->isExist())
		{
			pge->DrawString(screenConsts::healthText_hzPadding, screenConsts::levelInfo_vrPadding, "Health:", olc::WHITE, screenConsts::fontScale);

			//total 200 pixels
			if (player->getHealth() == healthConsts::playerInitHealth)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_3").get());
				pge->DrawSprite(screenConsts::healthSpr_hzPadding, screenConsts::levelInfo_vrPadding, spritesManager->entitySprite("health_3").get());
			}

			//150
			else if (player->getHealth() == healthConsts::playerHealthTwo)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_2").get());
				pge->DrawSprite(screenConsts::healthSpr_hzPadding, screenConsts::levelInfo_vrPadding, spritesManager->entitySprite("health_2").get());
			}

			//120
			else if (player->getHealth() == healthConsts::playerHealthOne)
			{
				pge->DrawSprite(player->getPos().x, player->getPos().y, spritesManager->entitySprite("player_1").get());
				pge->DrawSprite(screenConsts::healthSpr_hzPadding, screenConsts::levelInfo_vrPadding, spritesManager->entitySprite("health_1").get());
			}
		}
	}

	void drawShips(Level& level, std::shared_ptr<SpriteManager> spritesManager, olc::PixelGameEngine* pge) {
		for (auto& shipsrow : level.get_Ships())
			for (auto& ship : shipsrow)
			{
				if (ship.isExist())
				{
					if (ship.getHealth() == healthConsts::alien1InitHealth)
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("alien_1").get());

					else if (ship.getHealth() == healthConsts::alien2InitHealth)
						pge->DrawSprite(ship.getPos().x, ship.getPos().y, spritesManager->entitySprite("alien_2").get());

					else if (ship.getHealth() == healthConsts::alien3InitHealth)
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
			}
		}
	}

	void drawPlayerBullets(std::list<Bullet>& bullets, 
		std::shared_ptr<SpriteManager> spritesManager, olc::PixelGameEngine* pge)
	{
		for (auto& bullet : bullets)
		{
			if (bullet.isExist())
				pge->DrawSprite(bullet.getPos().x, bullet.getPos().y, spritesManager->entitySprite("bullet").get());
		}
	}

	void drawScore(int& current_score, olc::PixelGameEngine* pge) {
		pge->DrawString(screenConsts::scoreText_hzPadding, screenConsts::levelInfo_vrPadding, "Score:" + std::to_string(current_score), olc::WHITE, 2);
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