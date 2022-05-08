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

	int get_Width() {return element_Width;}

	int get_Height() {return element_Height;}

	void move_left(float ElapsedTime) {
		pos_x -= (ElapsedTime * speed);
		center_x -= (ElapsedTime * speed);
	}

	void move_right(float ElapsedTime) {
		pos_x += (ElapsedTime * speed);
		center_x += (ElapsedTime * speed);
	}

	olc::vf2d  get_Pos() {
		return { pos_x, pos_y };
	}

	void gotHit()
	{
		health--;
		if (health == 0)
			Kill();
	}

	void Kill()  {
		exist = false;
	}

	bool& is_exist() {
		return exist;
	}

	int get_Health() {
		return health; 
	}

};

