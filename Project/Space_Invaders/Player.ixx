module;
#include "olcPixelGameEngine.h"
extern std::string player_name;
import Bullet;
import Entity;
export module Player;

export class Player : public Entity  {

private:
	int score;
	std::shared_ptr<olc::Sprite> player1Spr; //50 * 70
	std::shared_ptr<olc::Sprite> player2Spr; //50 * 70
	std::shared_ptr<olc::Sprite> player3Spr; //50 * 70

public:

	Player(){}


	Player(int32_t w, int32_t h) {
		element_Width = 50;
		element_Height = 70; 
		set_Scale(w, h);
		speed = 500.0f;
		exist = true;
		health = 3;
		player1Spr = std::make_shared<olc::Sprite>("./sprites/player_1.png");
		player2Spr = std::make_shared<olc::Sprite>("./sprites/player_2.png");
		player3Spr = std::make_shared<olc::Sprite>("./sprites/player_3.png");

	}

	void reload()
	{
		set_Player_Pos(ScreenWidth, ScreenHeight); 
		exist = true;
		health = 3;
	}

	void DrawSelf(olc::PixelGameEngine* pge)
	{
		std::string _health = std::to_string(health);
		if (exist)
		{
			pge->DrawString(ScreenWidth - 500, 10, "Health: " + _health, olc::WHITE, 2);
			pge->DrawString(float(get_Pos().x), float(get_Pos().y + get_Height()), player_name, olc::WHITE, 2);
			if (health == 3)
				pge->DrawSprite(get_Pos().x, get_Pos().y, player3Spr.get());

			else if (health == 2)
				pge->DrawSprite(get_Pos().x, get_Pos().y, player2Spr.get());

			else if (health == 1)
				pge->DrawSprite(get_Pos().x, get_Pos().y, player1Spr.get());
		}
	}

	void set_Scale(int32_t w, int32_t h) 
	{
		//set_Size(w / 10, h / 10);
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