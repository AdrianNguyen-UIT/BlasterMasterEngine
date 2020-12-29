#include "d3dpch.h"
#include "RollOutCutscene.h"
#include "Assets/Others/CutScenePlayer.h"
#include "Assets/Others/CutsceneBackground.h"
void RollOutCutscene::CreateScene()
{
	mapSize = { (float)BLACK_BACKGROUND_WIDTH, (float)BLACK_BACKGROUND_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, CAMERA_HEIGHT, CAMERA_WIDTH, CAMERA_HEIGHT);
	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(BLACK_BACKGROUND_PATH, 0);
	}

	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	quadtree = std::make_unique<QuadTree>(0, mapBound);

	std::shared_ptr<Object2D> cutscenePlayer = std::make_shared<CutScenePlayer>(camera->GetSize().width / 2.0f, camera->GetSize().height / 2.0f, CutsceneType::RollOut);
	cutscenePlayer->CreateResources();
	AddObject(cutscenePlayer);
}
