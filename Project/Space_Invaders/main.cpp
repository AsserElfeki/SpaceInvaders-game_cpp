#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Ship;
import Player; 
import SpritesManager; 
import ErrorHandler; 
import FileHandler; 

int main()
{
	
	FileHandler fileHandler; 

	std::cout << "Level 4 Health: " << fileHandler.readAlienHealth("Level 4") << " (5) was expected.." << std::endl;
	std::cout << "Level 3 speed: " << fileHandler.readAlienSpeed("Level 3") << " (200) was expected.." << std::endl;
	
	std::vector<std::vector<int>> bla = fileHandler.readAlienPos("Level 1"); 

	std::cout << "level 1 pos: \n";
	for (auto& shipsrow : bla)
		std::cout << "{ " << shipsrow[0] << " , " << shipsrow[1] << " , " << shipsrow[2] << " , " << shipsrow[3] << " , " << shipsrow[4] <<  " }" << std::endl; 

	/*ErrorHandler error;
	if (error.checkAllSpritesExist())
	{
		SpaceInvaders demo;
		if (demo.Construct(1200, 800, 1, 1, false, true))
			demo.Start();
	}

	else
	{ 
		if (error.Construct(600, 200, 1, 1, false, true))
			error.Start();
	}*/
	
	
		
	return 0;
}