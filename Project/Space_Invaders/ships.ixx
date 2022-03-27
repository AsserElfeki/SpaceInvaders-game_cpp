module;

#include "olcPixelGameEngine.h"
//import Game;
import GameUnits_Interface;


export module Ships; 

export class Alien_ships : public Units_Interface {

private: 
	std::vector<olc::vf2d> ships_pos;


public: 
	
	void set_ShipsPos() {
		for (int i = 1; i < 5; i++) {
			ships_pos.push_back({ (i * this->get_Width() * 22 / 5) , 100.0f });
			ships_pos.push_back({ (i * this->get_Width() * 22 / 5) , 170.0f });
			ships_pos.push_back({ (i * this->get_Width() * 22 / 5) , 240.0f });
			ships_pos.push_back({ (i * this->get_Width() * 22 / 5) , 310.0f });
			ships_pos.push_back({ (i * this->get_Width() * 22 / 5) , 380.0f });

		}
	}
	
	std::vector<olc::vf2d> get_ships_pos_vec() {
		return ships_pos;
	}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
		for (auto a : ships_pos) {
			pge->FillCircle(a, this->get_Width() , olc::RED); // to define a 3px radius

		}
	}
};
