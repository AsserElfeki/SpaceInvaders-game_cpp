module; 

#include "olcPixelGameEngine.h"
#include <memory>
#include <list>

import Level; 
import LevelFour;
import Bullet; 
import Ship; 
import Player; 
import ScoreHandler;

export module CollisionDetectionHandler;

export class CollisionDetectionHandler {

private: 
	float ScreenHeight = 800;
	float ScreenWidth = 1200;

public: 

	CollisionDetectionHandler() {}

	void playerBulletVsAlien(float fElapsedTime, std::shared_ptr<Level>& level, std::unique_ptr<Player>& m_player, std::unique_ptr<ScoreHandler>& scoreHandler, std::list<Bullet>& m_bullets, olc::PixelGameEngine* pge)
	{

		auto Itr = m_bullets.begin();
		//collision detection between a player's bullet and alien ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.movePlayerBullet(fElapsedTime, pge);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 4; j++)
				{
					
					if (bullet.getPos().y > 0 && level->get_Ships()[i][j].isExist()) //circle collision
						if (((level->get_Ships()[i][j].getCenter().x - bullet.getPos().x) *
							(level->get_Ships()[i][j].getCenter().x - bullet.getPos().x)) +
							((level->get_Ships()[i][j].getCenter().y - bullet.getPos().y) *
								(level->get_Ships()[i][j].getCenter().y - bullet.getPos().y)) <=
							level->get_Ships()[i][j].getWidth() / 2 * level->get_Ships()[i][j].getWidth() / 2)
						{
							bullet.kill();
							m_bullets.erase(Itr);
							level->get_Ships()[i][j].gotHit();
							scoreHandler->increaseScoreWhenHitAlien();
						}
				}
			Itr++;
		}
	}

	void alienBulletVsPlayer(std::shared_ptr<Level>& level, std::unique_ptr<Player>& m_player, std::unique_ptr <ScoreHandler>& scoreHandler)
	{

		for (auto& shipsrow : level->get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				auto Itr = ship.getAlienBullets().begin();

				for (auto A_bullet : ship.getAlienBullets())
				{
					//check hit
					if (A_bullet.getPos().y < ScreenHeight && A_bullet.getPos().y + 10 >= m_player->getPos().y)
					{
						if (A_bullet.getPos().x >= m_player->getPos().x && A_bullet.getPos().x <= (m_player->getPos().x + m_player->getWidth()))
						{
							A_bullet.kill();
							ship.getAlienBullets().erase(Itr);
							m_player->playerGotHit();
							scoreHandler->decreaseScoreWhenHealthDecreased();

							//check bullet outta screen
							if (A_bullet.getPos().y + 10 >= ScreenHeight)
							{
								A_bullet.kill();
								//ship.getAlienBullets().erase(Itr);
							}
						}
					}
					Itr++;
				}
			}
		}

		
	}

	void alienShipVsPlayerShip(std::shared_ptr<Level>& level, std::unique_ptr<Player>& m_player, std::unique_ptr<ScoreHandler>& scoreHandler)
	{
		//collision detection between player and alien itself
		for (auto& shipsrow : level->get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				if (ship.isExist())
					if (ship.getPos().y + ship.getHeight() >= m_player->getPos().y && ship.getPos().y <= m_player->getPos().y + m_player->getHeight()
						&& ship.getPos().x + ship.getWidth() >= m_player->getPos().x && ship.getPos().x <= m_player->getPos().x + m_player->getWidth())
					{
						m_player->playerGotHit();
						ship.gotHit();
						scoreHandler->decreaseScoreWhenHealthDecreased();
					}
			}
		}
	}
};