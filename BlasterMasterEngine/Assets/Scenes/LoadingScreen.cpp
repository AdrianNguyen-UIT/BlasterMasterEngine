#include "d3dpch.h"
#include "LoadingScreen.h"
#include "Assets/Canvas/LoadingScreenText/LoadingScreenText.h"
void LoadingScreen::CreateScene()
{
	mapSize = { (float)BLACK_BACKGROUND_WIDTH, (float)BLACK_BACKGROUND_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, CAMERA_HEIGHT, CAMERA_WIDTH, CAMERA_HEIGHT);
	
	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(BLACK_BACKGROUND_PATH, 0);
	}
	
	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	//quadtree = std::make_unique<QuadTree>(0, mapBound);
	canvas = std::make_unique<Canvas>();
	{
		std::shared_ptr<UIElement> leftText = std::make_shared<LoadingScreenText>(mapSize.width / 2, mapSize.height / 2);
		leftText->CreateResources();
		canvas->AddUIElement(leftText);
	}
}