#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Ship;
import Player; 
import SpritesManager; 
import ErrorHandler; 
import FileHandler; 
import LevelManager;

int main()
{
	
	LevelManager levelManager; 

	std::cout << "Level 4 Health: " << levelManager.getHealth("Level 4") << " (5) was expected.." << std::endl;
	std::cout << "Level 3 speed: " << levelManager.getSpeed("Level 3") << " (200) was expected.." << std::endl;
	
	/*std::vector<std::vector<bool>> bla;
	levelManager.readAlienPos("Level 2");*/

	std::cout << "level 2 pos: \n";
	for (int i = 0 ; i < 5; i++)
			std::cout << "{ " << levelManager.readAlienPos("Level 2")[i][0] << " , " << levelManager.readAlienPos("Level 2")[i][1] <<
		" , " << levelManager.readAlienPos("Level 2")[i][2] << " , " << levelManager.readAlienPos("Level 2")[i][3] <<  " }" << std::endl;

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


/*
Questions:
1- Grades? (as is) 
3- what to be improved? 
*/