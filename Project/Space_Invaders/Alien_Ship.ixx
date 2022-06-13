module;

#include "olcPixelGameEngine.h"
#include <random>
#include <chrono> 
#include "Constants.h"

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
		if (_health == healthConsts::bossInitHealth)
		{
			element_Width = screenConsts::bossWidth;
			element_Height = screenConsts::bossHeight;
		}
		else {
			element_Width = screenConsts::alienWidth;
			element_Height = screenConsts::alienWidth;
		}
		
		speed = _speed;
		pos_x = pos.x;
		pos_y = pos.y;
		
		center_x = (pos_x + element_Width / 2);
		center_y = (pos_y + element_Height / 2); 
		//these are not magic numbers, it's just getting half of the width and height so I get the center

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
			if (generator() < generator.min()+ (otherConsts::randGenSeed * speed) )
				m_alienBullets.emplace_back(this->getPos().x + this->getWidth()/2, this->getPos().y + this->getHeight());
		}
	}

	void moveAlienBullet(float time)
	{
		for (auto& bullet : m_alienBullets)
		{
			bullet.moveAlienBullet(time);
			if (bullet.getPos().y >= screenConsts::bottomBoundary)
				m_alienBullets.pop_front();
		}
	}

	void moveDown(float ElapsedTime) {
		pos_y += (ElapsedTime * speed) / screenConsts::verticalMovementFactor;
		center_y += (ElapsedTime * speed) / screenConsts::verticalMovementFactor;
	}

	void moveUp(float ElapsedTime) {
		pos_y -= (ElapsedTime * speed) / screenConsts::verticalMovementFactor;
		center_y -= (ElapsedTime * speed) / screenConsts::verticalMovementFactor;
	}

};
