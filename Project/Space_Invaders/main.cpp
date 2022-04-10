#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Score;
import Bullets;
import Ship;
import Player; 

std::string player_name;

int main()
{
	int w, h; 
	std::cout << "Please Enter your name:\n";
	std::cin >> player_name;
	std::cout << "please provide game window width:\n";
	std::cin >> w; 
	std::cout << "please provide game window height:\n";
	std::cin >> h;

	SpaceInvaders demo;
	if (demo.Construct(w, h, 1, 1, false, true))  
		demo.Start();

	return 0;
}