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
			pge->FillRect(float(get_Pos().x), float (get_Pos().y), get_Width(), get_Height(), olc::GREEN);

	}


};