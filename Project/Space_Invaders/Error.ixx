module; 

#include "olcPixelGameEngine.h"
#include <filesystem>

namespace fs = std::filesystem;

export module ErrorHandler;

export class ErrorHandler : public olc::PixelGameEngine
{
private: 
	std::unique_ptr<olc::Sprite> message;
	std::filesystem::path error_file = "./sprites/screens/error.png";

public: 

	ErrorHandler() {sAppName = "Error";}

	bool OnUserCreate() override
	{
		message = std::make_unique<olc::Sprite>("./sprites/screens/error.png");
		return true; 
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		Clear(olc::WHITE);

		if (std::filesystem::exists(error_file)) //if the error sprite exists draw it
			DrawSprite(0, 0, message.get());
		else
		{
			DrawLine(10, 10, ScreenWidth() - 10, 10, olc::BLACK); //upper HZ line the (-10 px) is just to add some padding
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

	bool checkAllSpritesExist()
	{
		//game states sprites
		fs::path intro = "./sprites/screens/intro.png";
		fs::path instructions = "./sprites/screens/instructions.png";
		fs::path lost = "./sprites/screens/lost.png";
		fs::path name = "./sprites/screens/name.png";
		fs::path pause = "./sprites/screens/pause.png";
		fs::path won = "./sprites/screens/won.png";

		//game units sprites 
		fs::path alien_1 = "./sprites/entity/alien_1.png";
		fs::path alien_2 = "./sprites/entity/alien_2.png";
		fs::path alien_3 = "./sprites/entity/alien_3.png";
		fs::path boss = "./sprites/entity/boss.png";
		fs::path bullet = "./sprites/entity/bullet.png";
		fs::path health_1 = "./sprites/entity/health_1.png";
		fs::path health_2 = "./sprites/entity/health_2.png";
		fs::path health_3 = "./sprites/entity/health_3.png";
		fs::path player_1 = "./sprites/entity/player_1.png";
		fs::path player_2 = "./sprites/entity/player_2.png";
		fs::path player_3 = "./sprites/entity/player_3.png";

		//credits sprites
		fs::path background = "./sprites/credits/background.png";
		fs::path credits = "./sprites/credits/credits.png";
		fs::path credits_options = "./sprites/credits/credits_options.png";

		std::vector<fs::path> paths{ intro, instructions, lost, name, pause, won,
			alien_1,alien_2, alien_3, boss, bullet, health_1, health_2, health_3, player_1, player_2, player_3,
		background, credits, credits_options };

		for (auto& file : paths)
		{
			if (!fs::exists(file))
				return false;
		}

		return true;
	}
};
