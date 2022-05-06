module;

#include "olcPixelGameEngine.h"
import SpritesManager;

export module Credits;

export class Credits {

private: 
	int ScreenWidth, ScreenHeight,
		pos_x, pos_y;
	int speed = 100;
	
	std::unique_ptr <SpriteManager> spritesManager;

public:

	Credits(int w, int h)
	{
		spritesManager = std::make_unique<SpriteManager>();

		ScreenWidth = w;
		ScreenHeight = h; 

		pos_x = 0;
		pos_y = h; 
	}

	int get_Pos() {return pos_y; }

	void run_Credits(olc::PixelGameEngine* pge, float time) 
	{
		pge->SetPixelMode(olc::Pixel::ALPHA);
		pge->DrawSprite(0, 0, spritesManager->creditSprite("background").get());
	

		if (get_Pos() > - ScreenHeight)
		{
			pos_y -= (time * speed);
			pge->DrawSprite(pos_x, pos_y, spritesManager->creditSprite("credits").get());
		}
		else
			pge->DrawSprite(pos_x, 0, spritesManager->creditSprite("credits_options").get());
	}

	void reset() {pos_y = 800;}
};