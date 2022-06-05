module;

#include "olcPixelGameEngine.h"


export import SpritesManager;
export module Entity;

export class Entity {

protected:
	int element_Width, element_Height,
		 ScreenWidth, ScreenHeight,
		speed, health;
	float  pos_x, pos_y, center_x, center_y ;
	bool exist;

public:
	Entity() {}

	int getWidth() {return element_Width;}

	int getHeight() {return element_Height;}

	void moveLeft(float ElapsedTime) {
		pos_x -= (ElapsedTime * speed);
		center_x -= (ElapsedTime * speed);
	}

	void moveRight(float ElapsedTime) {
		pos_x += (ElapsedTime * speed);
		center_x += (ElapsedTime * speed);
	}

	olc::vf2d  getPos() {return { pos_x, pos_y };}

	void gotHit()
	{
		health--;
		if (health == 0)
			kill();
	}

	void kill()  {
		exist = false;
	}

	bool& isExist() {
		return exist;
	}

	int& getHealth() { return health; }
};

