module;

#include "olcPixelGameEngine.h"

export module Presentation;
			  
export class  Presentation{

private:
	
	std::unique_ptr<olc::Sprite> presentation_1;
	std::unique_ptr<olc::Sprite> presentation_2;
	std::unique_ptr<olc::Sprite> presentation_3;
	std::unique_ptr<olc::Sprite> presentation_4;
	std::unique_ptr<olc::Sprite> presentation_5;
	std::unique_ptr<olc::Sprite> presentation_6;
	std::unique_ptr<olc::Sprite> presentation_7;
	std::unique_ptr<olc::Sprite> presentation_8;

	enum slide {
		slide1 =1 , slide2, slide3, slide4, slide5, slide6
	};

	int current_slide = 1;

public:

	Presentation(){
		presentation_1 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_1.png");
		presentation_2 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_2.png");
		presentation_3 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_3.png");
		presentation_4 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_4.png");
		presentation_5 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_5.png");
		presentation_6 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_6.png");
		presentation_7 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_7.png");
		presentation_8 = std::make_unique<olc::Sprite>("./sprites/presentation/presentation_8.png");
	}

	void runPresentation(olc::PixelGameEngine* pge) {
		//pge->SetPixelMode(olc::Pixel::NORMAL);

		if (current_slide == 1)
			pge->DrawSprite(0, 0, presentation_1.get());

		else if (current_slide == 2)
			pge->DrawSprite(0, 0, presentation_2.get());

		else if (current_slide == 3)
			pge->DrawSprite(0, 0, presentation_3.get());
		
		else if (current_slide == 4)
			pge->DrawSprite(0, 0, presentation_4.get());
		
		else if (current_slide == 5)
			pge->DrawSprite(0, 0, presentation_5.get());
		
		else if (current_slide == 6)
			pge->DrawSprite(0, 0, presentation_6.get());
		
		else if (current_slide == 7)
			pge->DrawSprite(0, 0, presentation_7.get());

		else if (current_slide == 8)
			pge->DrawSprite(0, 0, presentation_8.get());

		if (pge->GetKey(olc::Key::RIGHT).bPressed && current_slide < 8)
			current_slide += 1; 

		if (pge->GetKey(olc::Key::LEFT).bPressed && current_slide > 1)
			current_slide -= 1;
	}
};