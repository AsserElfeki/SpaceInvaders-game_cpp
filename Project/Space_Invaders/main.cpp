#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import ErrorHandler;


int main()
{
	
	ErrorHandler error;
	if (error.checkAllSpritesExist())
		//check if all sprites used in the "game" exist
		//if they exist, the game starts
	{
		SpaceInvaders demo;
		//demo.construct(window width, height, how many screen pixels for each pixel,, fullscreen?, vsync of the monitor?) 
		if (demo.Construct(1200, 800, 1, 1, true, true))
			demo.Start();
	}

	//if at least one is not existing, an error window appears
	else
	{ 
		if (error.Construct(600, 200, 1, 1, false, true))
			error.Start();
	}
	
	
		
	return 0;
}


