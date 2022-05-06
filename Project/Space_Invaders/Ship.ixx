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
	std::filesystem::path entity_path = "./sprites/entity/";


	std::list<Bullet> m_alienBullets;
	std::shared_ptr<olc::Sprite> alien1Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alien2Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alien3Spr; //60 * 50
	std::shared_ptr<olc::Sprite> alienBossSpr; //100 * 100

	//std::unique_ptr<SpriteManager> spritesManager; 

public: 

	Alien_Ship() = delete; 

	Alien_Ship(olc::vi2d pos, int w, int h, bool _exist, float _speed, int _health) 
	{
		//spritesManager = std::make_unique<SpriteManager>();


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

	void DrawShip(olc::PixelGameEngine* pge) {

		if (exist)
		{
			if (health == 1)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien1Spr.get());
			//pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("alien_1").get());

			else if (health == 2)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien2Spr.get());
			//pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("alien_2").get());

			else if (health == 3)
				pge->DrawSprite(get_Pos().x, get_Pos().y, alien3Spr.get());
			//pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("alien_3").get());

			else
				pge->DrawSprite(get_Pos().x, get_Pos().y, alienBossSpr.get());
			//pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("boss").get());

		}
	}

	olc::vf2d get_Center() {
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

	/*void erase_bullet() {
		auto Itr = m_alienBullets.begin();
		m_alienBullets.erase(Itr);
		Itr++; 
	}*/

	void move_down(float ElapsedTime) {
		pos_y += (ElapsedTime * speed) / 10;
		center_y += (ElapsedTime * speed) / 10;
	}

	void move_up(float ElapsedTime) {
		pos_y -= (ElapsedTime * speed) / 10;
		center_y -= (ElapsedTime * speed) / 10;
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w;
		pos_y = h;
	}
};
