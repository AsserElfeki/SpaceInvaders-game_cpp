#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Ship;
import Player; 
import SpritesManager; 
import ErrorHandler; 


int main()
{
	

	ErrorHandler error;
	if (error.checkAllSpritesExist())
	{
		SpaceInvaders demo;
		if (demo.Construct(1200, 800, 1, 1, true, true))
			demo.Start();
	}

	else
	{ 
		if (error.Construct(600, 200, 1, 1, false, true))
			error.Start();
	}
	
		
	return 0;
}