module;

#include "olcPixelGameEngine.h"



export module GameUnits_Interface;


export class Units_Interface {

private:
	float Width;
	float Pos; 
	olc::vf2d Size;
	//olc::vf2d DisplaySize;

public:

	virtual void set_Width(float width) {
		Width = width;
	}

	float get_Width() {
		return Width;
	}

	float get_Pos() {
		return Pos; 
	}

	void set_Size(float width, float height) {
		Size = { width, height };
	}

	olc::vf2d get_Size() {
		return Size;
	}

	//void set_DisplaySize(float w, float h) {
	//	DisplaySize = { w , h };
	//	//set_Width(DisplaySize.x);
	//}

	//olc::vf2d get_DisplaySize() {
	//	return DisplaySize;
	//}

};