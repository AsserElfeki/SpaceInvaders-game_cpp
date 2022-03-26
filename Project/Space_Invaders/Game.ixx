module;
#include "olcPixelGameEngine.h"

export module Game;

export class SpaceInvaders : public olc::PixelGameEngine
{
public:
	SpaceInvaders()
	{
		sAppName = "Space Invaders";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Erase previous frame
		Clear(olc::BLACK);

		// Draw Boundary
		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::BLUE); //upper HZ line
		DrawLine(10, 10, 10, ScreenHeight() - 10, olc::BLUE); // left V line 
		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // right V line 
		DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLUE); // bottom HZ line

		// placeholder for the player
		FillRect(int(PlayerPos), ScreenHeight() - 40, 20, 20, olc::GREEN);
		return true;
	}

private:
	float PlayerPos = 20.0f;
};