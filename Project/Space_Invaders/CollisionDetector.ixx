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

	CollisionDetectionHandler() {

	}

	void playerBulletVsAlien(float fElapsedTime, std::shared_ptr<Level>& level, std::unique_ptr<Player>& m_player, std::unique_ptr<ScoreHandler>& scoreHandler, std::list<Bullet>& m_bullets, olc::PixelGameEngine* pge)
	{

		auto Itr = m_bullets.begin();
		//collision detection between a player's bullet and alien ship and killing in case of collision
		for (auto& bullet : m_bullets)
		{
			bullet.move_PlayerBullet(fElapsedTime, pge);
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

	void alienBulletVsPlayer(std::shared_ptr<Level>& level, std::unique_ptr<Player>& m_player, std::unique_ptr <ScoreHandler>& scoreHandler)
	{

		for (auto& shipsrow : level->get_Ships())
		{
			for (auto& ship : shipsrow)
			{
				auto Itr = ship.get_AlienBullets().begin();

				for (auto A_bullet : ship.get_AlienBullets())
				{
					//check hit
					if (A_bullet.get_Pos().y + 10 >= m_player->get_Pos().y)
					{
						if (A_bullet.get_Pos().x >= m_player->get_Pos().x && A_bullet.get_Pos().x <= (m_player->get_Pos().x + m_player->get_Width()))
						{
							A_bullet.Kill();
							ship.get_AlienBullets().erase(Itr);
							m_player->playerGotHit();
							scoreHandler->decrease_Score_When_Health_Decreased();

							//check bullet outta screen
							if (A_bullet.get_Pos().y + 10 >= ScreenHeight)
							{
								A_bullet.Kill();
								ship.get_AlienBullets().erase(Itr);
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
};