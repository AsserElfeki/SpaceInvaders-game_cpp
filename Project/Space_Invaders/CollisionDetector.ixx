module; 

#include "olcPixelGameEngine.h"
#include <memory>
#include <list>

import Level; 
import Bullet; 
import Ship; 
import Player; 
import ScoreHandler;

export module CollisionDetectionHandler;

export class CollisionDetectionHandler {

private: 

	enum shipsOnBorder {
		rightBorder = 3,
		left_and_upBorder = 0
	};
	const int num_of_rows = 5;
	const int num_of_cols = 4;

	float ScreenHeight = 800;
	float ScreenWidth = 1200;
	//constexpr int shipsinrow = 5;

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

	void playerBulletVsAlien(float fElapsedTime,
		Level& level,
		std::shared_ptr<Player>& m_player,
		std::unique_ptr<ScoreHandler>& scoreHandler,
		std::list<Bullet>& m_bullets)
	{

		auto Itr = m_bullets.begin();
		//collision detection between a player's bullet and alien ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.movePlayerBullet(fElapsedTime);
			for (int i = 0; i < num_of_rows; i++)
				for (int j = 0; j < num_of_cols; j++)
				{

					if (bullet.getPos().y > 0 && level.get_Ships()[i][j].isExist() && detectCircleCollision(level.get_Ships()[i][j], bullet))
					{
						bullet.kill();
						m_bullets.erase(Itr);
						level.get_Ships()[i][j].gotHit();
						scoreHandler->increaseScoreWhenHitAlien();
					}
				}
			Itr++;
		}
	}


	////ship's bullet vs player
	//bool detectCircleCollision(Bullet& bullet, std::shared_ptr<Player>& m_player)
	//{
	//	if (((m_player->getCenter().x - bullet.getPos().x) * (m_player->getCenter().x - bullet.getPos().x)) +
	//		((m_player->getCenter().y - bullet.getPos().y) * (m_player->getCenter().y - bullet.getPos().y)) <=
	//		( (m_player->getHeight() / 2) * (m_player->getHeight() / 2) ) )
	//		return true;
	//	else return false;
	//}

	void alienBulletVsPlayer(Level& level, std::shared_ptr<Player>& m_player, std::unique_ptr <ScoreHandler>& scoreHandler)
	{

		for (auto& shipsrow : level.get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				auto Itr = ship.getAlienBullets().begin();



				for (auto& A_bullet : ship.getAlienBullets())
				{
					//check hit

					//if (detectCircleCollision(A_bullet, m_player))
					//{
					//	A_bullet.kill();
					//	ship.getAlienBullets().erase(Itr);
					//	m_player->playerGotHit();
					//	scoreHandler->decreaseScoreWhenHealthDecreased();

					//	//check bullet outta screen
					//	if (A_bullet.getPos().y + 10 >= ScreenHeight)
					//		A_bullet.kill();
					//}

					if (A_bullet.getPos().y < ScreenHeight && A_bullet.getPos().y + 10 >= m_player->getPos().y) //chech if bullet in same vertical range
					{
						if (A_bullet.getPos().x >= m_player->getPos().x && A_bullet.getPos().x <= (m_player->getPos().x + m_player->getWidth()))
							//check if it's in same horizontal range
						{
							A_bullet.kill();
							ship.getAlienBullets().erase(Itr);
							m_player->playerGotHit();
							scoreHandler->decreaseScoreWhenHealthDecreased();

							//check bullet outta screen
							if (A_bullet.getPos().y + 10 >= ScreenHeight)
								A_bullet.kill();

						}
					}
					Itr++;
				}
			}
		}
	}


	//ship vs player
	bool detectCircleCollision() {

	}

	void alienShipVsPlayerShip(Level& level,
								std::shared_ptr<Player>& m_player,
								std::unique_ptr<ScoreHandler>& scoreHandler)
	{
		//collision detection between player and alien itself
		for (auto& shipsrow : level.get_Ships())
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


	void detectAllCollisions(float fElapsedTime,
		Level& level,
		std::shared_ptr<Player>& m_player,
		std::unique_ptr<ScoreHandler>& scoreHandler,
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