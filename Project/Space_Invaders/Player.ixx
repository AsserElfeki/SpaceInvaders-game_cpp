module;
#include "olcPixelGameEngine.h"

export import GameUnits_Interface;

export module Player;

export class Player : public Units_Interface {

private:
	


public:

	Player() {
		
	}

	

	void DrawSelf(olc::PixelGameEngine* pge)
	{
			pge->FillRect((get_Pos().x),  (get_Pos().y), get_Size().x, get_Size().y, olc::GREEN);

	}


};