#include "d3dpch.h"
#include "Credit.h"
#include "Core/Canvas/UIElement/ImageUI.h"
#include "Assets/Canvas/CreditPanel.h"
void Credit::CreateScene()
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
		RECT rect = {233, 3, 427, 243};
		std::shared_ptr<UIElement> badge = std::make_shared<ImageUI>(mapSize.width / 2 - 200, mapSize.height / 2, "Badge_Texture", rect);
		badge->CreateResources();
		canvas->AddUIElement(badge);
	}

	{
		RECT rect = { 428, 3, 478, 243 };
		std::shared_ptr<UIElement> topRibbon = std::make_shared<ImageUI>(mapSize.width / 2 - 200, mapSize.height / 2 + 240, "Badge_Texture", rect);
		topRibbon->CreateResources();
		canvas->AddUIElement(topRibbon);
	}

	{
		RECT rect = { 428, 3, 478, 243 };
		std::shared_ptr<UIElement> downRibbon = std::make_shared<ImageUI>(mapSize.width / 2 - 200, mapSize.height / 2 - 240, "Badge_Texture", rect);
		downRibbon->CreateResources();
		canvas->AddUIElement(downRibbon);
	}

	{
		std::shared_ptr<UIElement> creditPanel = std::make_shared<CreditPanel>(mapSize.width / 2 + 50, mapSize.height / 2);
		creditPanel->CreateResources();
		canvas->AddUIElement(creditPanel);
	}
}
