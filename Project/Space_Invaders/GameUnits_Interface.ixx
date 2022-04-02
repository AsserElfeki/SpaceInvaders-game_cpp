module;

#include "olcPixelGameEngine.h"



export module GameUnits_Interface;

export class Units_Interface {

private:
	int Width;
	olc::vi2d Pos;
	olc::vi2d Size;
	

public:
	Units_Interface(){
	}


	virtual void set_Width(int _width) {
		Width = _width;
	}

	int get_Width() {
		return Width;
	}

	void set_Pos(int _posx, int _posy) {
		Pos = { _posx / 2 - Size.x/2 , _posy - int (1.5*Size.y) } ;
	}

	olc::vi2d  get_Pos() {
		return Pos; 
	}

	void set_Size(int width, int height) {
		Size = { width, height };
	}

	olc::vi2d get_Size() {
		return Size;
	}

	

};

