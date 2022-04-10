module;
#include "olcPixelGameEngine.h"
extern std::string player_name;

import Entity;
export module Player;

export class Player : public Entity  {

private:
	int score;

public:

	Player() {
		speed = 500.0f;
		exist = true;
	}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
		if (exist)
		{
			pge->FillRect(float(get_Pos().x), float(get_Pos().y), get_Width(), get_Height(), olc::GREEN);

			pge->DrawString(float(get_Pos().x), float(get_Pos().y + get_Height()), player_name, olc::WHITE, 2);

		}
	}

	void set_Scale(int32_t w, int32_t h) 
	{
		set_Size(w / 10, h / 10);
		set_Player_Pos(w, h);
		ScreenWidth = w;
		ScreenHeight = h;
	}

	void set_Player_Pos(int w, int h) {
		pos_x = w / 2 - element_Width / 2;
		pos_y = h - 1.5 * element_Height;
	}

	void Pos_left() {
		pos_x = 11;
	}

	void Pos_right() {
		pos_x = ScreenWidth - element_Width - 11;
	}
};