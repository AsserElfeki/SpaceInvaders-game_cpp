module;
#include "olcPixelGameEngine.h"
import Entity; 

export module Bullet;

export class Bullet : public Entity {


private: 

	bool drawn;

public: 
	Bullet() = delete; 

	Bullet(olc::PixelGameEngine* pge, float posx, float posy)
	{
		pos_x = posx;
		pos_y = posy;
		element_Height = 10;
		speed = 300.0f;
		DrawSelf(pge);
	}

	~Bullet(){}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
			pge->DrawLine(get_Pos().x, get_Pos().y, get_Pos().x, get_Pos().y - element_Height, olc::RED);	 
	}

	void move_PlayerBullet(float time, olc::PixelGameEngine* pge) 
	{
			pos_y -= (time * speed);
			DrawSelf(pge);
	}

	void move_AlienBullet(float time, olc::PixelGameEngine* pge)
	{
		pos_y += (time * speed);
		DrawSelf(pge);

	}

};