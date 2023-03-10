#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Constants.h"

import Game;
import ErrorHandler;



int main()
{
	
	ErrorHandler error;
	if (error.checkAllSpritesExist())
		//check if all sprites used in the "game" exist
		//if they exist, the game starts
	{
		Game spaceInvaders;
		std::string answer;
		bool choiceDone = false; 

		while (!choiceDone)
		{
			std::cout << "do you want to run the game in full screen? 'y' for yes and 'n' for no" << std::endl;
			std::cin >> answer;
			if (answer != "y" && answer != "n")
				std::cout << "invalid choice, try again" << std::endl;
			else
				choiceDone = true; 
		}
		
		if (answer == "y")
		{
			//demo.construct(window width, height, how many screen pixels for each pixel,, fullscreen?, vsync of the monitor?) 
			if (spaceInvaders.Construct(screenConsts::ScreenWidth, screenConsts::ScreenHeight, screenConsts::pixelSizeOnScreen, screenConsts::pixelSizeOnScreen, true, true))
				spaceInvaders.Start();
		}
		else if (answer == "n")
		{
			//demo.construct(window width, height, how many screen pixels for each pixel,, fullscreen?, vsync of the monitor?) 
			if (spaceInvaders.Construct(screenConsts::ScreenWidth, screenConsts::ScreenHeight, screenConsts::pixelSizeOnScreen, screenConsts::pixelSizeOnScreen, false, true))
				spaceInvaders.Start();
		}
		
	}

	//if at least one is not existing, an error window appears
	else
	{ 
		if (error.Construct(errorWindow::errorWindowWidth, errorWindow::errorWindowHeight, screenConsts::pixelSizeOnScreen, screenConsts::pixelSizeOnScreen, false, true))
			error.Start();
	}
	
	
		
	return 0;
}


