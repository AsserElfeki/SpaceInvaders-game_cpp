#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Score;
import Bullets;
import Ship;
import Player; 



int main()
{
	SpaceInvaders demo;
	if (demo.Construct(800, 800, 1, 1))  
		demo.Start();

	return 0;
}