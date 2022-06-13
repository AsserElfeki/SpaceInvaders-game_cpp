module;

#include "olcPixelGameEngine.h"
#include "Constants.h"

import Entity; 

export module Bullet;

export class Bullet : public Entity {

private: 

public: 
	Bullet() = delete; 

	Bullet(float posx, float posy)
	{
		exist = true;
		health = healthConsts::bulletHealth;
		pos_x = posx;
		pos_y = posy;
		element_Height = screenConsts::bulletHeight;
		speed = speedConsts::bulletSpeed;
	}

	~Bullet(){}

	void movePlayerBullet(float time) 
	{
		pos_y -= (time * speed);
	}

	void moveAlienBullet(float time)
	{
		pos_y += (time * speed);
	}

};