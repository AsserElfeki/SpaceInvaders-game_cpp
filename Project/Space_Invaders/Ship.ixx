module;

#include "olcPixelGameEngine.h"
import Entity; 
export module Ship; 
 
export class Alien_Ship : public Entity
{

private: 
	

public: 

	Alien_Ship() = delete; 

	Alien_Ship(olc::vi2d pos, int w, int h, bool _exist) 
	{
		speed = 250.0f;
		pos_x = pos.x;
		pos_y = pos.y;
		ScreenWidth = w; 
		ScreenHeight = h; 
		element_Width = w / 25; 
		
		exist = _exist;

	}

	void DrawSelf(olc::PixelGameEngine* pge) {
		if (exist)
		pge->FillCircle(get_Pos(), get_Width(), olc::YELLOW);
	}

	void set_Ship_Pos(int w, int h)
	{
		pos_x = w;
		pos_y = h;
	}

	
};
