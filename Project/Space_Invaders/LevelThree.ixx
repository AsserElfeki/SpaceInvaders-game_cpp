module;

#include <string>

import Level;

export module LevelThree;

export class LevelThree : public Level {

protected:
	//the part where data is changed for each level 


public:
	LevelThree(int32_t w, int32_t h)
	{
		level_name = "Level 3";
		speed = 200;
		ships_health = 3;
		ships_positions =
		{
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1},
			{1,1,1,1}
		};
		set_Scale(w, h);
		Create_Ships();
	}
};