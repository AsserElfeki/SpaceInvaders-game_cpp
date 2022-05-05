module;
#include "olcPixelGameEngine.h"
#include <chrono>
#include <time.h>

extern std::string player_name;
import Bullet;
import Entity;
export module Player;

export class Player : public Entity  {

private:
	clock_t time_of_last_hit;

	//paths
	std::filesystem::path entity_path = "D:/POLSL/Year II/CP4/Repo/Project/Space_Invaders/sprites/entity/";

	//sprites
	std::unique_ptr<olc::Sprite> player1Spr; //50 * 70
	std::unique_ptr<olc::Sprite> player2Spr; //50 * 70
	std::unique_ptr<olc::Sprite> player3Spr; //50 * 70
	std::unique_ptr<olc::Sprite> health1Spr; //20 * 20
	std::unique_ptr<olc::Sprite> health2Spr; //48 * 20
	std::unique_ptr<olc::Sprite> health3Spr; //76 * 20

public:

	Player(){}


	Player(int32_t w, int32_t h) 
	{
		element_Width = 50;
		element_Height = 70; 
		set_Scale(w, h);
		speed = 500.0f;
		exist = true;
		health = 3;
		player1Spr = std::make_unique<olc::Sprite>(entity_path.string() +"player_1.png");
		player2Spr = std::make_unique<olc::Sprite>(entity_path.string() +"player_2.png");
		player3Spr = std::make_unique<olc::Sprite>(entity_path.string() +"player_3.png");
		health1Spr = std::make_unique<olc::Sprite>(entity_path.string() +"health_1.png");
		health2Spr = std::make_unique<olc::Sprite>(entity_path.string() +"health_2.png");
		health3Spr = std::make_unique<olc::Sprite>(entity_path.string() +"health_3.png");
	}

	void reload()
	{
		set_Player_Pos(ScreenWidth, ScreenHeight); 
		exist = true;
		health = 3;
	}

	void DrawPlayer(olc::PixelGameEngine* pge)
	{
		if (exist)
		{
			pge->DrawString(500, 20, "Health:", olc::WHITE, 2);

			//total 200 pixels
			if (health == 3)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, player3Spr.get());
				pge->DrawSprite(620, 20, health3Spr.get());
			}

			//150
			else if (health == 2)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, player2Spr.get());
				pge->DrawSprite(620, 20, health2Spr.get());
			}

			//120
			else if (health == 1)
			{
				pge->DrawSprite(get_Pos().x, get_Pos().y, player1Spr.get());
				pge->DrawSprite(620, 20, health1Spr.get());
			}
		}
	}

	void set_Scale(int32_t w, int32_t h) 
	{
		set_Player_Pos(w, h);
		ScreenWidth = w;
		ScreenHeight = h;
	}

	void set_Player_Pos(int w, int h) 
	{
		pos_x = w / 2 - element_Width / 2;
		pos_y = h - 1.5 * element_Height;
	}

	void Pos_left() 
	{
		pos_x = 11;
	}

	void Pos_right() 
	{
		pos_x = ScreenWidth - element_Width - 11;
	}
		
	void playerGotHit()
	{
		if ((clock() - time_of_last_hit) / CLOCKS_PER_SEC > 1)
		{
			health--;
			time_of_last_hit = clock();
		}
		if (health == 0)
			Kill();
	}
};