module;

#include "olcPixelGameEngine.h"

//import Bullet;

export module Entity;

export class Entity {

protected:
	int element_Width, element_Height,
		pos_x, pos_y, center_x, center_y, ScreenWidth, ScreenHeight,
		health;
	float speed;
	bool exist;



public:
	Entity() {
	}

	/*void set_Screen(int w, int h) {
		ScreenWidth = w;
		ScreenHeight = h;
	}*/

	//void set_Width(int _width) {
	//	element_Width = _width;
	//}

	int get_Width() {
		return element_Width;
	}

	/*void set_Height(int h) {
		element_Height = h;
	}*/

	int get_Height() {
		return element_Height;
	}

	/*void set_Size(int w, int h) {
		element_Width = w;
		element_Height = h;
	}*/

	void move_left(float ElapsedTime) {
		pos_x -= (ElapsedTime * speed);
		center_x -= (ElapsedTime * speed);
	}

	void move_right(float ElapsedTime) {
		pos_x += (ElapsedTime * speed);
		center_x += (ElapsedTime * speed);
	}

	/*void set_Pos(int32_t h, int32_t w)
	{
		pos_x = w;
		pos_y = h;
	}*/

	olc::vi2d  get_Pos() {
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

