module;

#include "olcPixelGameEngine.h"
#include <random>
#include <chrono> 

import Entity; 
import Bullet; 
export module Ship; 
 
export class Alien_Ship : public Entity
{

private: 
	std::list<Bullet> m_alienBullets;

public: 

	Alien_Ship() = delete; 

	Alien_Ship(olc::vi2d pos, int w, int h, bool _exist, float _speed) 
	{
		speed = _speed;
		pos_x = pos.x;
		pos_y = pos.y;
		ScreenWidth = w; 
		ScreenHeight = h; 
		element_Width = w / 25; 
		
		exist = _exist;

	}

	std::list<Bullet>& get_AlienBullets() {
		return m_alienBullets; 
	}

	void shoot(olc::PixelGameEngine* pge) 
	{
		//rand
		if (exist)
		{
			unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed); 
			//std::cout << "min: " << generator.min() << " cuurent: " << generator() << " , max: " << generator.max() << std::endl;
			if (generator() < generator.min()+ (100000 * speed) )
				m_alienBullets.emplace_back(pge, this->get_Pos().x, this->get_Pos().y + this->get_Width());

		}
		
	}

	void move_AlienBullet(float time, olc::PixelGameEngine* pge)
	{
		for (auto& bullet : m_alienBullets)
		{
			bullet.move_AlienBullet(time, pge);
			if (bullet.get_Pos().y > ScreenHeight - 60)
				m_alienBullets.pop_front();
		}
		
	}

	//void update(float fElapsedTime, olc::PixelGameEngine* pge)
	//{
	//	for (auto& bullet : m_alienBullets)
	//	{
	//		bullet.move_Bullet_down(fElapsedTime, pge);
	//		
	//				 //circle collision
	//					if (((level->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x) * (level->get_Ships()[i][j].get_Pos().x - bullet.get_Pos().x))
	//						+ ((level->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y) * (level->get_Ships()[i][j].get_Pos().y - bullet.get_Pos().y)) <=
	//						((level->get_Ships()[i][j].get_Width()) * (level->get_Ships()[i][j].get_Width())))
	//					{
	//						bullet.Kill();
	//						m_bullets.erase(Itr);
	//						level->get_Ships()[i][j].Kill();
	//					}
	//		Itr++;
	//	}

	//	//if bullet goes out of screen
	//	for (auto& bullet : m_bullets)
	//	{
	//		if (bullet.get_Pos().y < 60)
	//			m_bullets.pop_front();
	//	}
	//}

	void DrawSelf(olc::PixelGameEngine* pge) {
		if (exist)
		pge->FillCircle(get_Pos(), get_Width(), olc::YELLOW);
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w;
		pos_y = h;
	}

	bool& is_exist() {
		return exist;
	}
};
