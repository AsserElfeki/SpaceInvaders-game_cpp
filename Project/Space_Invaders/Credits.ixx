module;

#include "olcPixelGameEngine.h"

export module Credits;

export class Credits {

private : 
	int ScreenWidth, ScreenHeight,
		pos_x, pos_y;
	int speed = 100;

	std::unique_ptr <olc::Sprite> spr_credits;
	std::unique_ptr <olc::Sprite> spr_credits_options;
	std::unique_ptr <olc::Sprite> spr_credits_background;
	std::unique_ptr <olc::Sprite> spr_credits_header;

	std::filesystem::path credits_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/sprites/credits/";

public:

	Credits(int w, int h)
	{
		ScreenWidth = w;
		ScreenHeight = h; 

		pos_x = 0;
		pos_y = h; 
		 
		spr_credits = std::make_unique<olc::Sprite>(credits_path.string() + "credits.png");
		spr_credits_options = std::make_unique<olc::Sprite>(credits_path.string() + "credits_options.png");
		spr_credits_background = std::make_unique<olc::Sprite>(credits_path.string() + "background.png");
		spr_credits_header = std::make_unique<olc::Sprite>(credits_path.string() + "header.png");
	}

	int get_Pos() {return pos_y; }

	void run_Credits(olc::PixelGameEngine* pge, float time) 
	{
		pge->SetPixelMode(olc::Pixel::ALPHA);
		pge->DrawSprite(0, 0, spr_credits_background.get());
		pge->DrawSprite(0, 0, spr_credits_header.get());

		if (get_Pos() > - ScreenHeight)
		{
			pos_y -= (time * speed);
			pge->DrawSprite(pos_x, pos_y, spr_credits.get());
		}
		else
			pge->DrawSprite(pos_x, 0, spr_credits_options.get());
	}

	void reset() {
		pos_y = 800;
	}
};