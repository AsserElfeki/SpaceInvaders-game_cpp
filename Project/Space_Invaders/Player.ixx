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
	//std::unique_ptr<SpriteManager> spritesManager;

public:

	Player(){}


	Player(int32_t w, int32_t h) 
	{
		//spritesManager = std::make_unique<SpriteManager>();

		element_Width = 50;
		element_Height = 70; 
		pos_x = w / 2 - element_Width / 2;
		pos_y = h - 1.5 * element_Height;
		speed = 500.0f;
		exist = true;
		health = 3;	
	}

	void reload()
	{
		setPlayerPos(screenWidth, screenHeight); 
		exist = true;
		health = 3;
	}

	void maxPosLeft() {pos_x = 11;}

	void maxPosRight() {pos_x = screenWidth - element_Width - 11;}
		
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