module;

#include "olcPixelGameEngine.h"
export import Player; 
export module Ship; 
 
export class Alien_Ship {

private: 
	int element_Width, element_Height,
		pos_x, pos_y, ScreenWidth, ScreenHeight;
	float speed;

public: 

	Alien_Ship(){}

	Alien_Ship(olc::vi2d pos, int w, int h ) 
	{
		pos_x = pos.x;
		pos_y = pos.y;
		ScreenWidth = w; 
		ScreenHeight = h; 
		element_Width = w / 25; 
	}

	void DrawSelf(olc::PixelGameEngine* pge) {
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
