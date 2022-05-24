module;
#include "olcPixelGameEngine.h"
import Entity; 

export module Bullet;

export class Bullet : public Entity {

private: 

	

public: 
	Bullet() = delete; 

	Bullet(olc::PixelGameEngine* pge, float posx, float posy)
	{
		exist = true;
		health = 1;
		pos_x = posx;
		pos_y = posy;
		element_Height = 10;
		speed = 500.0f;
	}

	~Bullet(){}

	void movePlayerBullet(float time, olc::PixelGameEngine* pge) 
	{
		pos_y -= (time * speed);
	}

	void moveAlienBullet(float time, olc::PixelGameEngine* pge)
	{
		pos_y += (time * speed);
	}

};