module;
#include "olcPixelGameEngine.h"
import Entity; 

export module Bullet;

export class Bullet : public Entity {

private: 

	std::shared_ptr<olc::Sprite> bulletSpr; //10 * 15
	std::filesystem::path entity_path = "./sprites/entity/";

public: 
	Bullet() = delete; 

	Bullet(olc::PixelGameEngine* pge, float posx, float posy)
	{
		bulletSpr = std::make_shared<olc::Sprite>(entity_path.string() + "player_bullet.png");
	
		exist = true;
		health = 1;
		pos_x = posx;
		pos_y = posy;
		element_Height = 10;
		speed = 500.0f;
		DrawSelf(pge);
	}

	~Bullet(){}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
		if (exist)
			pge->DrawSprite(get_Pos().x, get_Pos().y, bulletSpr.get());	 
	}

	void move_PlayerBullet(float time, olc::PixelGameEngine* pge) 
	{
		DrawSelf(pge);
		pos_y -= (time * speed);
	}

	void move_AlienBullet(float time, olc::PixelGameEngine* pge)
	{
		DrawSelf(pge);
		pos_y += (time * speed);
	}

	/*bool checked() {
		return m_checked; 
	}

	void set_Checked() {
		m_checked = true;
	}*/
};