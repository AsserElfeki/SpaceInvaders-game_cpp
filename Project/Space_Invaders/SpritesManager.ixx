module;
#include "olcPixelGameEngine.h"
#include <filesystem>
#include <map>
#include <string>

export module SpritesManager;

export class SpriteManager {
private: 
	std::map <std::string, std::unique_ptr <olc::Sprite>> screenSprites_;
	std::map <std::string, std::unique_ptr <olc::Sprite>> entitySprites_;
	std::map <std::string, std::unique_ptr <olc::Sprite>> creditsSprites_;
	


	std::filesystem::path screens_path = "./sprites/screens/";
	std::filesystem::path entity_path = "./sprites/entity/";
	std::filesystem::path credits_path = "./sprites/credits/";

public: 
	SpriteManager() {

	}

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

	
};