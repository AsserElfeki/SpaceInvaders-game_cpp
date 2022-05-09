module;
#include "olcPixelGameEngine.h"
#include <chrono>
#include <time.h>

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
		setScale(w, h);
		speed = 500.0f;
		exist = true;
		health = 3;	
	}

	void reload()
	{
		setPlayerPos(ScreenWidth, ScreenHeight); 
		exist = true;
		health = 3;
	}

	void drawPlayer(olc::PixelGameEngine* pge)
	{
		if (exist)
		{
			pge->DrawString(500, 20, "Health:", olc::WHITE, 2);

			//total 200 pixels
			if (health == 3)
			{
				pge->DrawSprite(getPos().x, getPos().y, spritesManager->entitySprite("player_3").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_3").get());
			}

			//150
			else if (health == 2)
			{
				pge->DrawSprite(getPos().x, getPos().y, spritesManager->entitySprite("player_2").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_2").get());
			}

			//120
			else if (health == 1)
			{
				pge->DrawSprite(getPos().x, getPos().y, spritesManager->entitySprite("player_1").get());
				pge->DrawSprite(620, 20, spritesManager->entitySprite("health_1").get());
			}
		}
	}

	void setScale(int32_t w, int32_t h) 
	{
		setPlayerPos(w, h);
		ScreenWidth = w;
		ScreenHeight = h;
	}

	void setPlayerPos(int w, int h) 
	{
		pos_x = w / 2 - element_Width / 2;
		pos_y = h - 1.5 * element_Height;
	}

	void maxPosLeft() {pos_x = 11;}

	void maxPosRight() {pos_x = ScreenWidth - element_Width - 11;}
		
	void playerGotHit()
	{
		if ((clock() - time_of_last_hit) / CLOCKS_PER_SEC > 1)
		{
			health--;
			time_of_last_hit = clock();
		}
		if (health == 0)
			kill();
	}
};