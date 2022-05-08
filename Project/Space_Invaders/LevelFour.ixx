module;

#include <string>

import Level;
export import LevelOne;
export import LevelTwo;
export import LevelThree;

export module LevelFour;

export class LevelFour : public Level {

protected:
	//the part where data is changed for each level 


public:
	LevelFour(int32_t w, int32_t h)
	{
		level_name = "Level 4";
		speed = 300;
		ships_health = 5;
		ships_positions =
		{
			{0,1,1,0},
			{1,0,0,1},
			{1,0,0,1},
			{0,1,1,0},
			{0,0,0,0}
		};
		set_Scale(w, h);
		Create_Ships();
	}
};