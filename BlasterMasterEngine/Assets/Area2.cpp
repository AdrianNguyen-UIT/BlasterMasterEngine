#include "d3dpch.h"
#include "Area2.h"
#include "Characters/Sophia/Sophia.h"
#include "Characters/Jason/Jason.h"
#include "Terrains/Terrain.h"
void Area2::CreateScene()
{
	camera = std::make_shared<OrthographicCamera>(0.0f, 600.0f, WIDTH, HEIGHT);

	backGround = DeviceResources::LoadSurface(AREA2_MAP_PATH, 0);

	mapRectSize.width = 298;
	mapRectSize.height = 224;
	boundaryRect = { 0, 0, 2048, 2048 };
	leftInit = 1024;
	topInit = 1040;

	//{
	//	std::shared_ptr<Object2D> sophia = std::make_shared<Sophia>(300.0f, 400.0f);
	//	sophia->CreateResources();
	//	AddObject(sophia);
	//}
	{
		std::shared_ptr<Object2D> jason = std::make_shared<Jason>(300.0f, 400.0f);
		jason->CreateResources();
		AddObject(jason);
	}
	{
		std::shared_ptr<Object2D> terrain0 = std::make_shared<Terrain>(425.0f, 190.0f);
		terrain0->name = "terrain 0";
		terrain0->boxCollider->size = { 860.0f, 50.0f };
		objects.emplace_back(terrain0);
	}

	{
		std::shared_ptr<Object2D> terrain1 = std::make_shared<Terrain>(-50.0f, 300.0f);
		terrain1->name = "terrain 1";
		terrain1->boxCollider->size = { 100.0f, 600.0f };
		objects.emplace_back(terrain1);
	}

	{
		std::shared_ptr<Object2D> terrain2 = std::make_shared<Terrain>(1203.0f, 190.0f);
		terrain2->name = "terrain 2";
		terrain2->boxCollider->size = { 335.0f, 50.0f };
		objects.emplace_back(terrain2);
	}

	{
		std::shared_ptr<Object2D> terrain3 = std::make_shared<Terrain>(1720.0f, 190.0f);
		terrain3->name = "terrain 3";
		terrain3->boxCollider->size = { 335.0f, 50.0f };
		objects.emplace_back(terrain3);
	}

	{
		std::shared_ptr<Object2D> terrain4 = std::make_shared<Terrain>(2343.0f, 190.0f);
		terrain4->name = "terrain 3";
		terrain4->boxCollider->size = { 560.0f, 50.0f };
		objects.emplace_back(terrain4);
	}

	{
		std::shared_ptr<Object2D> terrain5 = std::make_shared<Terrain>(2660.0f, 300.0f);
		terrain5->name = "terrain 5";
		terrain5->boxCollider->size = { 100.0f, 600.0f };
		objects.emplace_back(terrain5);
	}
}