#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Score;
import Bullets;
import Ships;
import Player; 



int main()
{
	SpaceInvaders demo;
	if (demo.Construct(512, 480, 2, 2))  
		demo.Start();

	return 0;
}