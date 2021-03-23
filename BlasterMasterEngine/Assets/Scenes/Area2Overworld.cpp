#include "d3dpch.h"
#include "Area2Overworld.h"
#include "Assets/Others/Terrains/Terrain.h"
#include "Assets/CameraBound.h"
#include "Assets/Others/Checkpoint/CheckPoint.h"
#include "Assets/Canvas/HealthBar/HealthBar.h"
#include "Assets/Characters/Jason/OverworldJason.h"
#include "Assets/Characters/Enemy/Area2OverworldEnemyList.h"
#include "Assets/Others/BossRoomArea2.h"
#include "Assets/Characters/PlayerHealth.h"
#include "Assets/Others/Checkpoint/Background.h"
#include "Assets/Others/Checkpoint/IndoorHorizontalCheckpoint.h"
#include "Assets/Others/Checkpoint/IndoorVerticalCheckpoint.h"
#include "Assets/Others/Checkpoint/MainWorldGate.h"
#include "Assets/Others/Terrains/Punji.h"


void Area2Overworld::CreateScene()
{
	mapSize = { (float)AREA2OVERWORLD_MAP_WIDTH, (float)AREA2OVERWORLD_MAP_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(901.0f, mapSize.height - 661.0f, CAMERA_WIDTH, CAMERA_HEIGHT);

	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(AREA2OVERWORLD_MAP_PATH, 0);
	}

	if (xmlMap == NULL)
	{
		LoadXmlMap(AREA2OVERWORLD_OBJECTS_TMX);
	}

	RECT mapBound = { 0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	quadtree = std::make_unique<QuadTree>(0, mapBound);

	PlayerHealth::ResetHealth();

	{
		std::shared_ptr<Object2D> overworldJason = std::make_shared<OverworldJason>(901.0f, mapSize.height - 661.0f);
		overworldJason->CreateResources();
		AddObject(overworldJason);
	}

	{
		std::shared_ptr<Object2D> eyeball_1 = std::make_shared<Eyeball>(320.0f, mapSize.height - 1843.0f);
		eyeball_1->CreateResources();
		eyeball_1->name = "eb 1";
		AddObject(eyeball_1);

		std::shared_ptr<Object2D> eyeball_2 = std::make_shared<Eyeball>(320.0f, mapSize.height - 1964.0f);
		eyeball_2->CreateResources();
		eyeball_2->name = "eb 2";
		AddObject(eyeball_2);

		std::shared_ptr<Object2D> eyeball_3 = std::make_shared<Eyeball>(595, mapSize.height - 1428.0f);
		eyeball_3->CreateResources();
		eyeball_3->name = "eb 3";
		AddObject(eyeball_3);

		std::shared_ptr<Object2D> eyeball_4 = std::make_shared<Eyeball>(692, mapSize.height - 1356.0f);
		eyeball_4->CreateResources();
		eyeball_4->name = "eb 4";
		AddObject(eyeball_4);

		std::shared_ptr<Object2D> eyeball_5 = std::make_shared<Eyeball>(175.0f, mapSize.height - 848);
		eyeball_5->CreateResources();
		eyeball_5->name = "eb 5";
		AddObject(eyeball_5);

		std::shared_ptr<Object2D> eyeball_6 = std::make_shared<Eyeball>(320.0f, mapSize.height - 821);
		eyeball_6->CreateResources();
		eyeball_6->name = "eb 6";
		AddObject(eyeball_6);

		std::shared_ptr<Object2D> eyeball_7 = std::make_shared<Eyeball>(449, mapSize.height - 827);
		eyeball_7->CreateResources();
		eyeball_7->name = "eb 7";
		AddObject(eyeball_7);

		std::shared_ptr<Object2D> eyeball_8 = std::make_shared<Eyeball>(424.0f, mapSize.height - 927.0f);
		eyeball_8->CreateResources();
		eyeball_8->name = "eb 8";
		AddObject(eyeball_8);

		std::shared_ptr<Object2D> eyeball_9 = std::make_shared<Eyeball>(576.0f, mapSize.height - 834);
		eyeball_9->CreateResources();
		eyeball_9->name = "eb 9";
		AddObject(eyeball_9);

		std::shared_ptr<Object2D> eyeball_10 = std::make_shared<Eyeball>(690, mapSize.height - 925);
		eyeball_10->CreateResources();
		eyeball_10->name = "eb 10";
		AddObject(eyeball_10);

		std::shared_ptr<Object2D> eyeball_11 = std::make_shared<Eyeball>(692.0f, mapSize.height - 839.0f);
		eyeball_11->CreateResources();
		eyeball_11->name = "eb 11";
		AddObject(eyeball_11);

		std::shared_ptr<Object2D> cannon_1 = std::make_shared<Cannon>(563.0f, mapSize.height - 1644.0f);
		cannon_1->CreateResources();
		cannon_1->name = "cn 1";
		AddObject(cannon_1);

		std::shared_ptr<Object2D> cannon_2 = std::make_shared<Cannon>(391.0f, mapSize.height - 1398.0f);
		cannon_2->CreateResources();
		cannon_2->name = "cn 2";
		AddObject(cannon_2);

		std::shared_ptr<Object2D> cannon_3 = std::make_shared<Cannon>(128.0f, mapSize.height - 910.0f);
		cannon_3->CreateResources();
		cannon_3->name = "cn 3";
		AddObject(cannon_3);

		std::shared_ptr<Object2D> tele_1 = std::make_shared<Teleporter>(335.0f, mapSize.height - 1078.0f);
		tele_1->CreateResources();
		tele_1->name = "tl 1";
		AddObject(tele_1);

		std::shared_ptr<Object2D> tele_2 = std::make_shared<Teleporter>(426.0f, mapSize.height - 1185.0f);
		tele_2->CreateResources();
		tele_2->name = "tl 2";
		AddObject(tele_2);

		std::shared_ptr<Object2D> tele_3 = std::make_shared<Teleporter>(314.0f, mapSize.height - 1181.0f);
		tele_3->CreateResources();
		tele_3->name = "tl 3";
		AddObject(tele_3);

		std::shared_ptr<Object2D> tele_4 = std::make_shared<Teleporter>(123.0f, mapSize.height - 1130.0f);
		tele_4->CreateResources();
		tele_4->name = "tl 4";
		AddObject(tele_4);

		//zone16
		std::shared_ptr<Object2D> cannon_4 = std::make_shared<Cannon>(943.0f, mapSize.height - 845.0f);
		cannon_4->CreateResources();
		cannon_4->name = "cn 4";
		AddObject(cannon_4);
	}

	for (auto objectGroup : xmlMap->GetObjectGroups())
	{
		if (objectGroup.GetName() == "object")
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);

				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> terrain = std::make_shared<Terrain>(xPos, yPos);
				terrain->name = "Terrain ";
				terrain->name += std::to_string(jIndex);
				terrain->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(terrain);
			}

		}

		if (objectGroup.GetName() == "punji")
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);

				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> terrain = std::make_shared<Punji>(xPos, yPos);
				terrain->name = "Punji";
				terrain->name += std::to_string(jIndex);
				terrain->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(terrain);
			}
		}

		if ((objectGroup.GetName() == "checkpoint"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> checkPoint = std::make_shared<IndoorHorizontalCheckpoint>(xPos, yPos);
				checkPoint->name = "CheckPoint ";
				checkPoint->name += std::to_string(jIndex);
				checkPoint->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(checkPoint);
			}
		}

		if ((objectGroup.GetName() == "vertical checkpoint"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> verticalCheckpoint = std::make_shared<IndoorVerticalCheckpoint>(xPos, yPos);
				verticalCheckpoint->name = "vertical Checkpoint";
				verticalCheckpoint->name += std::to_string(jIndex);
				verticalCheckpoint->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(verticalCheckpoint);
			}
		}

		if ((objectGroup.GetName() == "static background"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> nonChangeBackground = std::make_shared<Background>(xPos, yPos);
				nonChangeBackground->name = "non change back ground";
				nonChangeBackground->name += std::to_string(jIndex);
				nonChangeBackground->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				nonChangeBackground->spriteRenderer->rect = { object.GetX(), object.GetY(),
					object.GetX() + object.GetWidth() + 1, object.GetY() + object.GetHeight() + 1 };
				nonChangeBackground->CreateResources();
				AddObject(nonChangeBackground);
			}
		}

		if ((objectGroup.GetName() == "camera zone"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				RECT region = { object.GetX(), object.GetY(), object.GetX() + object.GetWidth(), object.GetY() + object.GetHeight() };
				CameraBound::AddBound(region);
			}
		}

		if ((objectGroup.GetName() == "main gate"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> verticalCheckpoint = std::make_shared<MainWorldGate>(xPos, yPos);
				verticalCheckpoint->name = "Main Gate";
				verticalCheckpoint->name += std::to_string(jIndex);
				verticalCheckpoint->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(verticalCheckpoint);
			}
		}
	}

	canvas = std::make_unique<Canvas>();
	{
		std::shared_ptr<UIElement> healthBar = std::make_shared<HealthBar>(65.0f, 395.0f);
		healthBar->CreateResources();
		canvas->AddUIElement(healthBar);
	}

	std::shared_ptr<Object2D> bossRoom = std::make_shared<BossRoomArea2>(895.0f, mapSize.height - 612.0f);
	bossRoom->CreateResources();
	bossRoom->name = "boss room";
	AddObject(bossRoom);
}