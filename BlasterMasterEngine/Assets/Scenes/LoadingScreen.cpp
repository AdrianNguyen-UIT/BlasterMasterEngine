#include "d3dpch.h"
#include "LoadingScreen.h"

void LoadingScreen::CreateScene()
{
	mapSize = { (float)BLACK_BACKGROUND_WIDTH, (float)BLACK_BACKGROUND_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, CAMERA_HEIGHT, CAMERA_WIDTH, CAMERA_HEIGHT);
	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(BLACK_BACKGROUND_PATH, 0);
	}
	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
}