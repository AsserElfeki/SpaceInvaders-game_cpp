module;
#include "olcPixelGameEngine.h"

export module Credits;

export class Credits {

private : 
	int ScreenWidth, ScreenHeight,
		pos_x, pos_y;
	int speed = 100;

	std::unique_ptr <olc::Sprite> creditsSpr;
	std::unique_ptr <olc::Sprite> credit_options_Spr;

public:

	Credits(int w, int h)
	{
		ScreenWidth = w;
		ScreenHeight = h; 

		pos_x = 0;
		pos_y = h; 
		 
		creditsSpr = std::make_unique<olc::Sprite>("./sprites/credits/credits.png");
		credit_options_Spr = std::make_unique<olc::Sprite>("./sprites/credits/credits_options.png");

	}

	int get_Pos() {return pos_y; }

	void run_Credits(olc::PixelGameEngine* pge, float time) 
	{
		if (get_Pos() > - ScreenHeight)
		{
			pos_y -= (time * speed);
			pge->DrawSprite(pos_x, pos_y, creditsSpr.get());
		}
		else
			pge->DrawSprite(pos_x, 0, credit_options_Spr.get());

	}

	void reset() {
		pos_y = 800;
	}
};