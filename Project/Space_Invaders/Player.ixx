module;
#include "olcPixelGameEngine.h"
#include <chrono>
#include <time.h>

//extern std::string player_name;
import Bullet;
import Entity;

export module Player;

export class Player : public Entity  {

private:
	clock_t time_of_last_hit;
	std::unique_ptr<SpriteManager> spritesManager;

public:

	Player(){}


	Player(int32_t w, int32_t h) 
	{
		spritesManager = std::make_unique<SpriteManager>();

		element_Width = 50;
		element_Height = 70; 
		set_Scale(w, h);
		speed = 500.0f;
		exist = true;
		health = 3;
		
	}

	void reload()
	{
		set_Player_Pos(ScreenWidth, ScreenHeight); 
		exist = true;
		health = 3;
	}

	void DrawPlayer(olc::PixelGameEngine* pge)
	{
		if (exist)
		{
			pge->DrawString(500, 20, "Health:", olc::WHITE, 2);

			//total 200 pixels
			if (health == 3)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("player_3").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_1").get());
			}

			//150
			else if (health == 2)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("player_2").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_1").get());
			}

			//120
			else if (health == 1)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, spritesManager->entitySprite("player_1").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_1").get());
			}
		}
	}

	void set_Scale(int32_t w, int32_t h) 
	{
		set_Player_Pos(w, h);
		ScreenWidth = w;
		ScreenHeight = h;
	}

	void set_Player_Pos(int w, int h) 
	{
		pos_x = w / 2 - element_Width / 2;
		pos_y = h - 1.5 * element_Height;
	}

	void Pos_left() 
	{
		pos_x = 11;
	}

	void Pos_right() 
	{
		pos_x = ScreenWidth - element_Width - 11;
	}
		
	void playerGotHit()
	{
		if ((clock() - time_of_last_hit) / CLOCKS_PER_SEC > 1)
		{
			health--;
			time_of_last_hit = clock();
		}
		if (health == 0)
			Kill();
	}
};