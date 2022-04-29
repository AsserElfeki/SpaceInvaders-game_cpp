module;
#include "olcPixelGameEngine.h"
import Entity; 

export module Bullet;

export class Bullet : public Entity {

private: 

	//bool m_checked; 
public: 
	Bullet() = delete; 

	Bullet(olc::PixelGameEngine* pge, float posx, float posy)
	{
		exist = true;
		//m_checked = false;
		health = 1;
		pos_x = posx;
		pos_y = posy;
		element_Height = 10;
		speed = 300.0f;
		DrawSelf(pge);
	}

	~Bullet(){}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
		if (exist)
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

	/*bool checked() {
		return m_checked; 
	}

	void set_Checked() {
		m_checked = true;
	}*/
};