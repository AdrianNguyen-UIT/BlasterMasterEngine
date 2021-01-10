#include "d3dpch.h"
#include "EndingCutscene.h"
#include "Assets/Others/EndingCutscene/Volcano.h"
#include "Assets/Others/EndingCutscene/Sky.h"
#include "Assets/Others/EndingCutscene/Ground.h"
#include "Assets/Others/CutScenePlayer.h"
#include "Assets/Others/EndingCutscene/Head.h"
#include "Assets/Others/EndingCutscene/Frog.h"
void EndingCutscene::CreateScene()
{
	mapSize = { (float)ENDING_MAP_WIDTH, (float)ENDING_MAP_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(2.0f, mapSize.height - 2.0f, CAMERA_WIDTH, CAMERA_HEIGHT);
	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(ENDING_MAP_PATH, 0);
	}

	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	//quadtree = std::make_unique<QuadTree>(0, mapBound);

	std::shared_ptr<Object2D> sky = std::make_shared<Sky>(128.0f, mapSize.height - 70.0f);
	sky->CreateResources();
	AddObject(sky);

	std::shared_ptr<Object2D> volcano = std::make_shared<Volcano>(134.0f, mapSize.height - 126.0f);
	volcano->CreateResources();
	AddObject(volcano);

	std::shared_ptr<Object2D> ground = std::make_shared<Ground>(128.0f, mapSize.height - 184.0f);
	ground->CreateResources();
	AddObject(ground);

	std::shared_ptr<Object2D> cutscenePlayer = std::make_shared<CutScenePlayer>(camera->GetSize().width / 2.0f, camera->GetSize().height / 2.0f, CutsceneType::Ending);
	cutscenePlayer->CreateResources();
	AddObject(cutscenePlayer);

	std::shared_ptr<Object2D> head = std::make_shared<Head>(419.0f, mapSize.height - 100.0f);
	head->CreateResources();
	AddObject(head);

	std::shared_ptr<Object2D> frog = std::make_shared<Frog>(433.0f, mapSize.height - 117.0f);
	frog->CreateResources();
	AddObject(frog);
}