#include "d3dpch.h"
#include "GameOverScreen.h"
#include "Core/Canvas/UIElement/TextUI.h"
#include "Assets/Others/ChooseWheel.h"
void GameOverScreen::CreateScene()
{
	mapSize = { (float)BLACK_BACKGROUND_WIDTH, (float)BLACK_BACKGROUND_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, CAMERA_HEIGHT, CAMERA_WIDTH, CAMERA_HEIGHT);

	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(BLACK_BACKGROUND_PATH, 0);
	}

	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	quadtree = std::make_unique<QuadTree>(0, mapBound);

	canvas = std::make_unique<Canvas>();
	{
		std::shared_ptr<UIElement> continueText = std::make_shared<TextUI>(mapSize.width / 2, mapSize.height / 2 - 50, "CONTINUE", "Health Bar Font");
		continueText->CreateResources();
		canvas->AddUIElement(continueText);
	}

	{
		std::shared_ptr<UIElement> endText = std::make_shared<TextUI>(mapSize.width / 2, mapSize.height / 2 + 50, "END", "Health Bar Font");
		endText->CreateResources();
		canvas->AddUIElement(endText);
	}

	{
		std::shared_ptr<Object2D> chooseWheel = std::make_shared<ChooseWheel>();
		chooseWheel->CreateResources();
		AddObject(chooseWheel);
	}
}