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

public:

	Player(){}


	Player(int32_t w, int32_t h) 
	{
		element_Width = 50;
		element_Height = 70; 
		resetPos();
		speed = 500.0f;
		exist = true;
		health = 3;	
		center_x = (pos_x + element_Width / 2);
		center_y = (pos_y + element_Height / 2);
	}

	void reload()
	{
		resetPos();
		exist = true;
		health = 3;
	}
	void resetPos() {
		pos_x = screenWidth / 2 - element_Width / 2;
		pos_y = screenHeight - 1.5 * element_Height;
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