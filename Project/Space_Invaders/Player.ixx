module;
#include "olcPixelGameEngine.h"
#include <chrono>
#include <time.h>
#include "Constants.h"

import Bullet;
import Entity;

export module Player;

export class Player : public Entity  {

private:
	clock_t time_of_last_hit= 0;

public:

	Player(){}


	Player(int32_t w, int32_t h) 
	{
		element_Width = screenConsts::playerWidth;
		element_Height = screenConsts::playerHeight;
		resetPos();
		speed = speedConsts::playerSpeed;
		exist = true;
		health = healthConsts::playerInitHealth;
		center_x = (pos_x + element_Width / 2);
		center_y = (pos_y + element_Height / 2);
	}

	void reload(int h)
	{
		resetPos();
		exist = true;
		health = h;
	}

	void reload()
	{
		resetPos();
		exist = true;
		health = healthConsts::playerInitHealth;
	}

	void resetPos() {
		pos_x = screenWidth / 2 - element_Width / 2;
		pos_y = screenConsts::playerPos_y; 
	}

	void maxPosLeft() {pos_x = screenConsts::maxLeftPlayerPos;}

	void maxPosRight() {pos_x = screenConsts::maxRightPlayerPos;}
		
	void gotHit() override
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