module; 

#include <list>

import Level; 
import Bullet; 
import Ship; 
import Player; 

export module CollisionDetector;

//export class CollisionDetector {
//
//private: 
//	std::list<Bullet> m_bullets;
//
//public: 
//
//
//	void playerBulletVsAlien(float fElapsedTime, std::unique_ptr<Level>& level)
//	{
//		auto Itr = m_bullets.begin();
//
//		//collision detection between a player's bullet and alien ship and killing in case of collision
//		for (auto& bullet : m_bullets)
//		{
//			bullet.move_PlayerBullet(fElapsedTime/*, this*/);
//			for (int i = 0; i < 5; i++)
//				for (int j = 0; j < 4; j++)
//				{
//					if (level->get_Ships()[i][j].is_exist()) //circle collision
//						if (((level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x) *
//							(level->get_Ships()[i][j].get_Center().x - bullet.get_Pos().x)) +
//							((level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y) *
//								(level->get_Ships()[i][j].get_Center().y - bullet.get_Pos().y)) <=
//							level->get_Ships()[i][j].get_Width() / 2 * level->get_Ships()[i][j].get_Width() / 2)
//						{
//							bullet.Kill();
//							m_bullets.erase(Itr);
//							level->get_Ships()[i][j].gotHit();
//							//scoreHandler->increase_Score_When_Hit_Alien();
//						}
//				}
//			Itr++;
//		}
//	}
//
//	void alienBulletVsPlayer(float fElapsedTime, std::unique_ptr<Level>& level)
//	{
//		//collision detection between player and aliens bullets 
//		for (auto& shipsrow : level->get_Ships())
//		{
//			for (auto& ship : shipsrow)
//			{
//				ship.shoot(this);
//				ship.move_AlienBullet(fElapsedTime, this);
//				auto ITR = ship.get_AlienBullets().begin();
//				for (auto A_bullet : ship.get_AlienBullets())
//				{
//					//check hit
//					if (A_bullet.get_Pos().y + 10 >= m_player->get_Pos().y)
//					{
//						if (A_bullet.get_Pos().x >= m_player->get_Pos().x && A_bullet.get_Pos().x <= (m_player->get_Pos().x + m_player->get_Width()))
//						{
//							A_bullet.Kill();
//							ship.get_AlienBullets().erase(ITR);
//							m_player->playerGotHit();
//							scoreHandler->decrease_Score_When_Health_Decreased();
//
//							//chech bullet outta screen
//							if (A_bullet.get_Pos().y + 10 >= ScreenHeight())
//							{
//								A_bullet.Kill();
//								ship.get_AlienBullets().erase(ITR);
//							}
//						}
//					}
//					ITR++;
//				}
//			}
//		}
//	}
//
//	void alienShipVsPlayerShip(float fElapsedTime, std::unique_ptr<Level>& level)
//	{
//		//collision detection between player and alien itself 
//		for (auto& shipsrow : level->get_Ships())
//		{
//			for (auto& ship : shipsrow)
//			{
//				if (ship.is_exist())
//					if (ship.get_Pos().y + ship.get_Height() >= m_player->get_Pos().y && ship.get_Pos().y <= m_player->get_Pos().y + m_player->get_Height()
//						&& ship.get_Pos().x + ship.get_Width() >= m_player->get_Pos().x && ship.get_Pos().x <= m_player->get_Pos().x + m_player->get_Width())
//					{
//						m_player->playerGotHit();
//						ship.gotHit();
//						scoreHandler->decrease_Score_When_Health_Decreased();
//					}
//			}
//		}
//	}
//
//};