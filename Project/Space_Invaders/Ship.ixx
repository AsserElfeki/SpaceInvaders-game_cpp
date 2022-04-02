module;

#include "olcPixelGameEngine.h"
export import Player; 
export module Ship; 
 
export class Alien_Ship : public Units_Interface {

private: 


public: 


	Alien_Ship() 
	{
	
	}

	void DrawSelf(olc::PixelGameEngine* pge, olc::vi2d ships_pos) {
		pge->FillCircle(ships_pos, get_Width(), olc::YELLOW);	
	}

};
