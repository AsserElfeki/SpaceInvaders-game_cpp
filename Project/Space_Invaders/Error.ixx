module; 

#include "olcPixelGameEngine.h"
#include <filesystem>
export module Error;

export class Error : public olc::PixelGameEngine
{
private: 
	std::unique_ptr<olc::Sprite> message;
	std::filesystem::path error_file = "./sprites/screens/error.png";


public: 

	Error() {
		sAppName = "Error";
	}

	bool OnUserCreate() override
	{
		message = std::make_unique<olc::Sprite>("./sprites/screens/error.png");
		return true; 
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		Clear(olc::WHITE);

		if (std::filesystem::exists(error_file))
			DrawSprite(0, 0, message.get());
		else
		{
			DrawLine(10, 10, ScreenWidth() - 10, 10, olc::BLACK); //upper HZ line
			DrawLine(10, 10, 10, ScreenHeight() - 10, olc::BLACK); // left V line 
			DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLACK); // right V line
			DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::BLACK); // bottom HZ line

			DrawString(120, 50, "Error loading gfx files.", olc::RED,2);
			DrawString(150, 120, "Press Enter to quit.", olc::RED,2);
		}

		if (GetKey(olc::Key::ENTER).bHeld)
			return false;

		return true; 
	}
};

/*X1: 165 & 260
* Y: 130 * 165
* X2: 335 & 430
* */