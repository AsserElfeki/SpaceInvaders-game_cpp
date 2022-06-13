#pragma once

namespace screenConsts {

	constexpr int ScreenWidth = 1200;
	constexpr int ScreenHeight = 800;
	constexpr int rightBoundary = 1180;
	constexpr int leftBoundary = 20;
	constexpr int topBoundary = 50;
	constexpr int bottomBoundary = 780;

	constexpr int horizontalSeg_count = 5;
	constexpr int verticalSeg_count = 7;

	constexpr int playerWidth = 50;
	constexpr int playerHeight = 70;
	constexpr int alienWidth = 60;
	constexpr int alienHeight = 50;
	constexpr int bossWidth = 100;
	constexpr int bossHeight = 100;
	constexpr int bulletHeight = 10;
	constexpr int playerPos_y = 700;

	constexpr int maxRightPlayerPos = 1140;
	constexpr int maxLeftPlayerPos = 10;
	
	constexpr float verticalMovementFactor = 10; 

	constexpr int playAreaBorder_hzPadding = 10;
	constexpr int playAreaBorder_vrPadding = 50;
	constexpr int levelInfo_vrPadding = 20;
	constexpr int healthText_hzPadding = 500;
	constexpr int healthSpr_hzPadding = 620;
	constexpr int scoreText_hzPadding = 1000;
	constexpr int enteredName_hzPadding = 737;
	constexpr int enteredName_vrPadding = 445;

	constexpr int fontScale = 2;

	constexpr int pixelSizeOnScreen = 1;

	constexpr int errorWindowWidth = 600;
	constexpr int errorWindowHeight = 200;
}

namespace speedConsts {
	constexpr float playerSpeed = 500.0f;
	constexpr float bulletSpeed = 500.0f;

}


namespace healthConsts {
	constexpr int playerInitHealth = 3;
	constexpr int playerHealthTwo = 2;
	constexpr int playerHealthOne = 1;
	constexpr int alien1InitHealth = 1;
	constexpr int alien2InitHealth = 2;
	constexpr int alien3InitHealth = 3;
	constexpr int bossInitHealth = 5;
	constexpr int bulletHealth = 1;
}

namespace otherConsts {
	constexpr int randGenSeed = 50000;
	constexpr int shipsPosStartCellIndex = 3;
}

namespace shipsMatrixCount {
	constexpr int rows = 5;
	constexpr int colomns = 4;
}

namespace shipsOnBorder {
	constexpr int rightBorder = 3;
	constexpr int left_and_upBorder = 0;
};