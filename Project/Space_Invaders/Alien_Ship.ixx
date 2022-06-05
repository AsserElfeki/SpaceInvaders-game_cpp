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

	Alien_Ship(olc::vi2d pos, bool _exist, float _speed, int _health) 
	{
		
		health = _health;
		if (_health > 3)
		{
			element_Width = 100;
			element_Height = 100;
		}
		else {
			element_Width = 60;
			element_Height = 50;
		}
		
		speed = _speed;
		pos_x = pos.x;
		pos_y = pos.y;
		
		center_x = (pos_x + element_Width / 2);
		center_y = (pos_y + element_Height / 2);

		exist = _exist;
	}

	

	std::list<Bullet>& getAlienBullets() {
		return m_alienBullets; 
	}

	void shoot() 
	{
		if (exist)
		{
			unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed); 
			if (generator() < generator.min()+ (50000 * speed) )
				m_alienBullets.emplace_back(this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight());
		}
	}

	void moveAlienBullet(float time)
	{
		for (auto& bullet : m_alienBullets)
		{
			bullet.moveAlienBullet(time);
			if (bullet.getPos().y >= screenHeight - 20)
				m_alienBullets.pop_front();
		}
	}

	void moveDown(float ElapsedTime) {
		pos_y += (ElapsedTime * speed) / 10;
		center_y += (ElapsedTime * speed) / 10;
	}

	void moveUp(float ElapsedTime) {
		pos_y -= (ElapsedTime * speed) / 10;
		center_y -= (ElapsedTime * speed) / 10;
	}

};
