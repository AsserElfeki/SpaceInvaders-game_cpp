#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

import Game;
import Level; 
import Ship;
import Player; 

std::string player_name;

int main()
{
	//int w, h; 
	/*std::cout << "please enter your name:\n";
	std::cin >> player_name;*/
	/*std::cout << "please provide game window width:\n";
	std::cin >> w; 
	std::cout << "please provide game window height:\n";
	std::cin >> h;*/

	SpaceInvaders demo;
	if (demo.Construct(1200, 800, 1, 1, false, true))  
		demo.Start();

	return 0;
}