#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Ship;
import Player; 
import SpritesManager; 
import Error; 


int main()
{
	

	SpriteManager obj;
	if (obj.checkAllSpritesExist())
	{
		SpaceInvaders demo;
		if (demo.Construct(1200, 800, 1, 1, false, true))
			demo.Start();
	}

	else
	{
		Error error; 
		if (error.Construct(600, 200, 1, 1, false, true))
			error.Start();
	}
	
		
	return 0;
}