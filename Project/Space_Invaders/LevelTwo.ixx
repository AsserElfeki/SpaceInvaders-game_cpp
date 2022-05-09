module;

#include <string>

import Level;

export module LevelTwo;

export class LevelTwo : public Level {

protected:
	//the part where data is changed for each level 


public:
	LevelTwo(int32_t w, int32_t h)
	{
		level_name = "Level 2";
		speed = 150;
		ships_health = 2;
		ships_positions =
		{
			{1,0,0,1},
			{0,1,1,0},
			{0,1,1,0},
			{1,0,0,1},
			{0,0,0,0}
		};
		setScale(w, h);
		createShips();
	}
};