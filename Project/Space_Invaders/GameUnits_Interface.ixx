module;

#include "olcPixelGameEngine.h"



export module GameUnits_Interface;

export class Units_Interface {

private:
	int element_Width, element_Height, 
		pos_x, pos_y, ScreenWidth, ScreenHeight;
	float speed; 
	
	 

public:
	Units_Interface(){
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

	void set_Size(int w, int h) {
		element_Width = w;
		element_Height = h;
	}

	/*olc::vi2d get_Size() {
		return Size;
	}*/

	void set_Player_Pos(int w, int h) {
		pos_x = w / 2 - element_Width/2;
		pos_y = h - 1.5 * element_Height;
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w ;
		pos_y = h ;
	}

	void Pos_left() {
		pos_x = 11;
	}

	void Pos_right() {
		pos_x = ScreenWidth-element_Width-10;
	}

	void move_left(float ElapsedTime) {
		pos_x -= (speed * ElapsedTime); 
	}

	void move_right(float ElapsedTime) {
		pos_x += (speed * ElapsedTime);

	}

	olc::vi2d  get_Pos() {
		return {pos_x, pos_y};
	}

	

};

