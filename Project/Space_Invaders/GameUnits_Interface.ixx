module;

#include "olcPixelGameEngine.h"



export module GameUnits_Interface;

export class Units_Interface {

private:
	float Width;
	olc::vf2d Pos;
	olc::vf2d Size;
	

public:
	Units_Interface(){
	}


	virtual void set_Width(float _width) {
		Width = _width;
	}

	float get_Width() {
		return Width;
	}

	void set_Pos(float _posx, float _posy) {
		Pos = { _posx / 2 - Size.x/2 , _posy - float(1.5*Size.y) } ;
	}

	olc::vf2d  get_Pos() {
		return Pos; 
	}

	void set_Size(float width, float height) {
		Size = { width, height };
	}

	olc::vf2d get_Size() {
		return Size;
	}

	

};

