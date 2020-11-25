#include "d3dpch.h"
#include "Area2.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Terrains/Terrain.h"
void Area2::CreateScene()
{
	mapSize = { (float)AREA2_MAP_WIDTH, (float)AREA2_MAP_HEIGHT };
	camera = std::make_shared<OrthographicCamera>(0.0f, mapSize.height - 2832.0f, CAMERA_WIDTH, CAMERA_HEIGHT);
	backGround = DeviceResources::LoadSurface(AREA2_MAP_PATH, 0);

	LoadXmlMap(OBJECTS_TMX);
	RECT mapBound = {0, 0, (LONG)mapSize.width, (LONG)mapSize.height };
	quadTree = std::make_unique<QuadTree>(1, mapBound, mapBound);

	{
		std::shared_ptr<Object2D> sophia = std::make_shared<Sophia>(55.0f, mapSize.height - 2919.0f);
		sophia->CreateResources();
		AddPlayer(sophia);
	}

	for (auto objectGroup : xmlMap.GetObjectGroups())
	{
		if (objectGroup.GetName() == "object")
		{
			for (size_t jIndex = 0; jIndex < objectGroup.GetNumObjects(); ++jIndex)
			{
				XmlObject object = objectGroup.GetObjects().at(jIndex);
				float xPos = (float)object.GetX() + (float)object.GetWidth() / 2;
				float yPos = (float)mapSize.height - (float)(object.GetY() + object.GetHeight() / 2.0f);
				std::shared_ptr<Object2D> terrain = std::make_shared<Terrain>(xPos, yPos);
				terrain->name = "terrain ";
				terrain->name += std::to_string(jIndex);
				terrain->boxCollider->size = { (float)object.GetWidth(), (float)object.GetHeight() };
				objects.emplace_back(terrain);

				quadTree->InsertObject(terrain);
			}
			return;
		}
	}


}