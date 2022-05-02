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
	//paths
	std::filesystem::path entity_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/sprites/entity/";


	std::list<Bullet> m_alienBullets;
	std::shared_ptr<olc::Sprite> alien1Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alien2Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alien3Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alienBossSpr; //100 * 100


public: 

	Alien_Ship() = delete; 

	Alien_Ship(olc::vi2d pos, int w, int h, bool _exist, float _speed, int _health) 
	{
		alien1Spr = std::make_shared<olc::Sprite>(entity_path.string() + "alien_1.png");
		alien2Spr = std::make_shared<olc::Sprite>(entity_path.string() + "alien_2.png");
		alien3Spr = std::make_shared<olc::Sprite>(entity_path.string() + "alien_3.png");
		alienBossSpr = std::make_shared<olc::Sprite>(entity_path.string() + "boss.png");

		ScreenWidth = w;
		ScreenHeight = h;
		
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

	olc::vi2d get_Center() {
		return { center_x, center_y };
	}

	std::list<Bullet>& get_AlienBullets() {
		return m_alienBullets; 
	}


	void shoot(olc::PixelGameEngine* pge) 
	{
		if (exist)
		{
			unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 generator(seed); 
			if (generator() < generator.min()+ (50000 * speed) )
				m_alienBullets.emplace_back(pge, this->get_Pos().x + this->get_Width()/2, this->get_Pos().y + this->get_Height());
		}
	}

	void move_AlienBullet(float time, olc::PixelGameEngine* pge)
	{
		for (auto& bullet : m_alienBullets)
		{
			bullet.move_AlienBullet(time, pge);
			if (bullet.get_Pos().y >= ScreenHeight - 20)
				m_alienBullets.pop_front();
		}
		
	}

	void erase_bullet() {
		auto Itr = m_alienBullets.begin();
		m_alienBullets.erase(Itr);
		Itr++; 

	}

	void DrawSelf(olc::PixelGameEngine* pge) {
		
		if (exist)
		{
			if (health == 1)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien1Spr.get());
			
			else if (health == 2)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien2Spr.get());

			else if (health ==3)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien3Spr.get());

			else 
				pge->DrawSprite(get_Pos().x, get_Pos().y, alienBossSpr.get());

		}
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w;
		pos_y = h;
	}

	
};
