module;

#include "olcPixelGameEngine.h"
export module Ship; 
 
export class Alien_Ship {

private: 
	int element_Width, element_Height,
		pos_x, pos_y, 
		ScreenWidth, ScreenHeight,
		move_right_limit,
		move_left_limit;
	float vel_dir = 1; 

	bool exist = false; 
	float speed = 0.01f;

public: 

	Alien_Ship() = delete; 

	Alien_Ship(olc::vi2d pos, int w, int h, bool _exist) 
	{
		pos_x = pos.x;
		pos_y = pos.y;
		ScreenWidth = w; 
		ScreenHeight = h; 
		element_Width = w / 25; 
		move_right_limit = 5; 
		move_left_limit = 5;
		if (_exist)
			exist = true; 

	}

	/*int get_limit() {
		return move_limit;
	}*/

	void flip_dir() {
		vel_dir *= -1; 
	}

	void Move() {
		pos_x *= 5 * vel_dir; 
	}

	void Move_right (float time ) {
		pos_x += 1 ;
	}

	void Move_left(float time  )
	{
		pos_x -= 1 ;
		//move_limit += 2;
	}

	void DrawSelf(olc::PixelGameEngine* pge) {
		if (exist)
		pge->FillCircle(get_Pos(), get_Width(), olc::YELLOW);
	}

	void set_Speed(float s) {
		speed = s;
	}

	void set_Screen(int w, int h) {
		ScreenWidth = w;
		ScreenHeight = h;
	}

	void set_Width(int _width) {
		element_Width = _width;
	}

	int get_Width() {
		return element_Width;
	}

	void set_Height(int h) {
		element_Height = h;
	}

	int get_Height() {
		return element_Height;
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w;
		pos_y = h;
	}

	olc::vi2d  get_Pos() {
		return { pos_x, pos_y };
	}
};
