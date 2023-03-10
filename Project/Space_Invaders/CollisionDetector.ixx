module; 

#include "olcPixelGameEngine.h"
#include <memory>
#include <list>
#include <ranges>
#include "Constants.h"

export import Level; 
export import Bullet; 
export import Ship; 
export import Player; 
export import ScoreHandler;

export module CollisionDetectionHandler;

export class CollisionDetectionHandler {

private: 

public: 

	//ship vs player's bullet 
	bool detectCircleCollision(Alien_Ship& ship, Bullet& bullet)
	{
		if (((ship.getCenter().x - bullet.getPos().x) *
			(ship.getCenter().x - bullet.getPos().x)) +
			((ship.getCenter().y - bullet.getPos().y) *
				(ship.getCenter().y - bullet.getPos().y)) <=
			ship.getWidth() / 2 * ship.getWidth() / 2)
			return true;
		else return false; 
	}

	void collision(Bullet& bullet, std::list<Bullet> m_bullets, Level& level, 
		std::shared_ptr<ScoreHandler>& scoreHandler, Alien_Ship& ship, std::list<Bullet>::iterator & Itr) {
		//auto Itr = m_bullets.begin();
		bullet.kill();
		m_bullets.erase(Itr);
		ship.gotHit();
		scoreHandler->increaseScoreWhenHitAlien();
	}

	void playerBulletVsAlien(float fElapsedTime,
		Level& level,
		std::shared_ptr<Player>& m_player,
		std::shared_ptr<ScoreHandler>& scoreHandler,
		std::list<Bullet>& m_bullets)
	{

		auto Itr = m_bullets.begin();
		//collision detection between a player's bullet and alien ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.movePlayerBullet(fElapsedTime);

			for (int i = 0; i < shipsMatrixCount::rows; i++)
				for (int j = 0; j < shipsMatrixCount::colomns; j++)
				{
					if (bullet.getPos().y > 0 && level.getShips()[i][j].isExist() && 
						detectCircleCollision(level.getShips()[i][j], bullet))
					{
						bullet.kill();
						m_bullets.erase(Itr);
						level.getShips()[i][j].gotHit();
						scoreHandler->increaseScoreWhenHitAlien();
					}
				}
			Itr++;
		}
	}


	void alienBulletVsPlayer(Level& level, std::shared_ptr<Player>& m_player, 
		std::shared_ptr <ScoreHandler>& scoreHandler)
	{
 		for (auto& shipsrow : level.getShips())
		{
			for (auto& ship : shipsrow)
			{
				auto Itr = ship.getAlienBullets().begin();
				for (auto& A_bullet : ship.getAlienBullets())
				{
					if (A_bullet.getPos().y < screenConsts::ScreenHeight 
						&& A_bullet.getPos().y + A_bullet.getHeight() >= m_player->getPos().y) //chech if bullet in same vertical range
					{
						if (A_bullet.getPos().x >= m_player->getPos().x 
							&& A_bullet.getPos().x <= (m_player->getPos().x + m_player->getWidth()))
							//check if it's in same horizontal range
						{
							A_bullet.kill();
							ship.getAlienBullets().erase(Itr);
							m_player->gotHit();
							scoreHandler->decreaseScoreWhenHealthDecreased();
						}

						//check bullet outta screen
						else if (A_bullet.getPos().y + A_bullet.getHeight() >= screenConsts::bottomBoundary)
						{
							A_bullet.kill();
							ship.getAlienBullets().erase(Itr);
						}
					}
					Itr++;
				}
			}
		}
	}


	void alienShipVsPlayerShip(Level& level,
								std::shared_ptr<Player>& m_player,
								std::shared_ptr<ScoreHandler>& scoreHandler)
	{
		//collision detection between player and alien itself
		for (auto& shipsrow : level.getShips())
		{
			for (auto& ship : shipsrow)
			{
				if (ship.isExist())
					if (ship.getPos().y + ship.getHeight() >= m_player->getPos().y && ship.getPos().y <= 
						m_player->getPos().y + m_player->getHeight()
						&& ship.getPos().x + ship.getWidth() >= m_player->getPos().x 
						&& ship.getPos().x <= m_player->getPos().x + m_player->getWidth())
					{
						m_player->gotHit();
						ship.gotHit();
						scoreHandler->decreaseScoreWhenHealthDecreased();
					}
			}
		}
	}


	void detectAllCollisions(float fElapsedTime,
		Level& level,
		std::shared_ptr<Player>& m_player,
		std::shared_ptr<ScoreHandler>& scoreHandler,
		std::list<Bullet>& m_bullets)
	{
		//collision detection between a player's bullet and alien ship and killing in case of collision
		playerBulletVsAlien(fElapsedTime, level, m_player, scoreHandler, m_bullets);

		//collision detection between player and aliens bullets 
		alienBulletVsPlayer(level, m_player, scoreHandler);

		//collision detection between player and alien itself 
		alienShipVsPlayerShip(level, m_player, scoreHandler);
	}
};