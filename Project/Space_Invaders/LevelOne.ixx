module;

#include <string>

import Level;

export module LevelOne;

export class LevelOne : public Level {

protected:
	//the part where data is changed for each level 


public:
	LevelOne(int32_t w, int32_t h)
	{
		level_name = "Level 1";
		speed = 100;
		ships_health = 1;
		ships_positions =
		{
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		};
		set_Scale(w, h);
		Create_Ships();
	}
};