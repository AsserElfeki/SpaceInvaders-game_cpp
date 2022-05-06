module;
#include "olcPixelGameEngine.h"
#include <filesystem>
#include <map>
#include <string>

namespace fs = std::filesystem; 

export module SpritesManager;

export class SpriteManager {
private: 
	std::map <std::string, std::unique_ptr <olc::Sprite>> screenSprites_;
	std::map <std::string, std::unique_ptr <olc::Sprite>> entitySprites_;
	std::map <std::string, std::unique_ptr <olc::Sprite>> creditsSprites_;
	


	fs::path screens_path = "./sprites/screens/";
	fs::path entity_path = "./sprites/entity/";
	fs::path credits_path = "./sprites/credits/";

public: 
	SpriteManager() {}

	std::unique_ptr <olc::Sprite>& screenSprite(std::string name)
	{
		if (!screenSprites_.count(name))
			screenSprites_.insert(std::make_pair(name, std::make_unique<olc::Sprite>(screens_path.string() + name + ".png")));

		return screenSprites_[name];
	}

	std::unique_ptr <olc::Sprite>& entitySprite(std::string name)
	{
		if (!entitySprites_.count(name))
			entitySprites_.insert(std::make_pair(name, std::make_unique<olc::Sprite>(entity_path.string() + name + ".png")));

		return entitySprites_[name];
	}

	std::unique_ptr <olc::Sprite>& creditSprite(std::string name)
	{
		if (!creditsSprites_.count(name))
			creditsSprites_.insert(std::make_pair(name, std::make_unique<olc::Sprite>(credits_path.string() + name + ".png")));

		return creditsSprites_[name];
	}
	

	bool checkAllSpritesExist()
	{
		fs::path intro = "./sprites/screens/intro.png";
		fs::path instructions = "./sprites/screens/instructions.png";
		fs::path lost = "./sprites/screens/lost.png";
		fs::path name = "./sprites/screens/name.png";
		fs::path pause = "./sprites/screens/pause.png";
		fs::path won = "./sprites/screens/won.png";

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

		fs::path background = "./sprites/credits/background.png";
		fs::path credits = "./sprites/credits/credits.png";
		fs::path credits_options = "./sprites/credits/credits_options.png";

		std::vector<fs::path> paths{intro, instructions, lost, name, pause, won, 
			alien_1,alien_2, alien_3, boss, bullet, health_1, health_2, health_3, player_1, player_2, player_3,
		background, credits, credits_options};

		for (auto& file : paths)
		{
			if (!fs::exists(file))
				return false;
		}

		return true; 
	}
};