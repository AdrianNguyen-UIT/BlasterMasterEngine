#include "d3dpch.h"
#include "Area2.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Terrains/Terrain.h"
#include "Assets/CameraBound.h"
#include "Assets/Checkpoint/CheckPoint.h"
#include "Assets/Trap/Trap.h"
#include "Assets/Bullets/Enemy/EnemyBullet.h"
#include "Assets/Ladder/Ladder.h"

#include "Assets/Characters/Enemy/Crab.h"

void Area2::CreateScene()
{
	mapSize = { (float)AREA2_MAP_WIDTH, (float)AREA2_MAP_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, mapSize.height - 2832.0f, CAMERA_WIDTH, CAMERA_HEIGHT);
	
	if (backGround == NULL)
	{
		backGround = DeviceResources::LoadSurface(AREA2_MAP_PATH, 0);
	}

	if (xmlMap == NULL)
	{
		LoadXmlMap(OBJECTS_TMX);
	}

	RECT mapBound = {0, 0, (LONG)mapSize.width, (LONG)mapSize.height };

	{
		std::shared_ptr<Object2D> crab = std::make_shared<Crab>(55.0f, mapSize.height - 2919.0f);
		crab->CreateResources();
		AddObject(crab);
	}


	{
		std::shared_ptr<Object2D> sophia = std::make_shared<Sophia>(55.0f, mapSize.height - 2956.0f);
		sophia->CreateResources();
		AddObject(sophia);
	}

	//{
	//	std::shared_ptr<Object2D> bullet = std::make_shared<EnemyBullet>(120.0f, mapSize.height - 2956.0f, true, false);
	//	bullet->name = "1";
	//	bullet->CreateResources();
	//	AddObject(bullet);
	//}

	//{
	//	std::shared_ptr<Object2D> bullet = std::make_shared<EnemyBullet>(220.0f, mapSize.height - 2956.0f, true, false);
	//	bullet->CreateResources();
	//	bullet->name = "2";
	//	AddObject(bullet);
	//}

	for (XmlObjectGroup objectGroup : xmlMap->GetObjectGroups())
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

		if ((objectGroup.GetName() == "checkpoint"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> checkPoint = std::make_shared<CheckPoint>(xPos, yPos);
				checkPoint->name = "CheckPoint ";
				checkPoint->name += std::to_string(jIndex);
				checkPoint->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				checkPoint->spriteRenderer->rect = { object.GetX(), object.GetY(), 
					object.GetX() + object.GetWidth() + 1, object.GetY() + object.GetHeight() + 1};
				checkPoint->CreateResources();
				AddObject(checkPoint);
			}
		}

		if ((objectGroup.GetName() == "trap"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> trap = std::make_shared<Trap>(xPos, yPos);
				trap->name = "Trap ";
				trap->name += std::to_string(jIndex);
				trap->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				trap->CreateResources();
				AddObject(trap);
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

		if ((objectGroup.GetName() == "ladder"))
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> ladder = std::make_shared<Ladder>(xPos, yPos);
				ladder->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				AddObject(ladder);
			}
		}
	}
}