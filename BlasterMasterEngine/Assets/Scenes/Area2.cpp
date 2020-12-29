#include "d3dpch.h"
#include "Area2.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Terrains/Terrain.h"
#include "Assets/CameraBound.h"
#include "Assets/Checkpoint/CheckPoint.h"
#include "Assets/Trap/Trap.h"
#include "Assets/Ladder/Ladder.h"
#include "Assets/Canvas/HealthBar/HealthBar.h"
#include "Assets/Characters/PlayerHealth.h"
#include "Assets/Characters/Enemy/EnemyList.h"
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

	RECT mapBound = { 0, 0, (LONG)mapSize.width + 20, (LONG)mapSize.height + 20 };
	quadtree = std::make_unique<QuadTree>(0, mapBound);

	PlayerHealth::ResetHealth();

	{
		std::shared_ptr<Object2D> sophia = std::make_shared<Sophia>(55.0f, mapSize.height - 2956.0f);
		sophia->CreateResources();
		AddObject(sophia);
	}
	
		//ZONE 1
		//
		//
		//
		std::shared_ptr<Object2D> worm2 = std::make_shared<EnemyWorm>(155.0f, mapSize.height - 2865.0f);
		worm2->name = "worm2";
		worm2->CreateResources();
		AddObject(worm2);

		std::shared_ptr<Object2D> worm1 = std::make_shared<EnemyWorm>(220.0f, mapSize.height - 2865.0f);
		worm1->name = "worm1";
		worm1->CreateResources();
		AddObject(worm1);

		std::shared_ptr<Object2D> bulletHead1 = std::make_shared<EnemyBulletHead>(265.0f, mapSize.height - 2970.0f);
		bulletHead1->name = "bulletHead1";
		bulletHead1->CreateResources();
		AddObject(bulletHead1);

		std::shared_ptr<Object2D> bulletHead2 = std::make_shared<EnemyBulletHead>(295.6f, mapSize.height - 2860.0f);
		bulletHead2->name = "bulletHead2";
		bulletHead2->CreateResources();
		AddObject(bulletHead2);

		std::shared_ptr<Object2D> worm3 = std::make_shared<EnemyWorm>(475.0f, mapSize.height - 2865.0f);
		worm3->name = "worm3";
		worm3->CreateResources();
		AddObject(worm3);

		std::shared_ptr<Object2D> crab1 = std::make_shared<EnemyCrab>(604.0f, mapSize.height - 2894.0f, -70.0f, 0.0f);
		crab1->name = "crab1";
		crab1->CreateResources();
		AddObject(crab1);

		std::shared_ptr<Object2D> worm4 = std::make_shared<EnemyWorm>(861.0f, mapSize.height - 2865.0f);
		worm4->name = "worm4";
		worm4->CreateResources();
		AddObject(worm4);

		std::shared_ptr<Object2D> crab2 = std::make_shared<EnemyCrab>(854.0f, mapSize.height - 2906.0f, 50.0f, -50.0f);
		crab2->name = "crab2";
		crab2->CreateResources();
		AddObject(crab2);

		std::shared_ptr<Object2D> worm5 = std::make_shared<EnemyWorm>(924.0f, mapSize.height - 2865.0f);
		worm5->name = "worm5";
		worm5->CreateResources();
		AddObject(worm5);

		std::shared_ptr<Object2D> crab3 = std::make_shared<EnemyCrab>(930.0f, mapSize.height - 2898.0f, -50.0f, 50.0f);
		crab3->name = "crab3";
		crab3->CreateResources();
		AddObject(crab3);
	//	//
	//	//
	//	//
	//	//ZONE 2
	//	//
	//	//
	//	//
	//	std::shared_ptr<Object2D> crab4 = std::make_shared<EnemyCrab>(1137.0f, mapSize.height - 2938.0f, 50.0f, -50.0f, 0.0f);
	//	crab4->name = "crab4";
	//	crab4->CreateResources();
	//	AddObject(crab4);

	//	std::shared_ptr<Object2D> crab5 = std::make_shared<EnemyCrab>(1170.0f, mapSize.height - 2894.0f, 50.0f, -50.0f, 600.0f);
	//	crab5->name = "crab5";
	//	crab5->CreateResources();
	//	AddObject(crab5);

	//	std::shared_ptr<Object2D> crab6 = std::make_shared<EnemyCrab>(1156.0f, mapSize.height - 2962.0f, -50.0f, 50.0f, 1200.0f);
	//	crab6->name = "crab6";
	//	crab6->CreateResources();
	//	AddObject(crab6);

	//	std::shared_ptr<Object2D> bulletHead3 = std::make_shared<EnemyBulletHead>(1310.0f, mapSize.height - 2970.0f);
	//	bulletHead3->name = "bulletHead3";
	//	bulletHead3->CreateResources();
	//	AddObject(bulletHead3);

	//	std::shared_ptr<Object2D> legRobot1 = std::make_shared<EnemyLegRobot>(1077.0f, mapSize.height - 2770.0f, false, 58.0f);
	//	legRobot1->name = "legRobot1";
	//	legRobot1->CreateResources();
	//	AddObject(legRobot1);

	//	std::shared_ptr<Object2D> bee1 = std::make_shared<EnemyBee>(1376.0f, mapSize.height - 2518.0f);
	//	bee1->name = "bee1";
	//	bee1->CreateResources();
	//	AddObject(bee1);

	//	std::shared_ptr<Object2D> bee2 = std::make_shared<EnemyBee>(1367.0f, mapSize.height - 2384.0f);
	//	bee2->name = "bee2";
	//	bee2->CreateResources();
	//	AddObject(bee2);

	//	std::shared_ptr<Object2D> bee3 = std::make_shared<EnemyBee>(1430.0f, mapSize.height - 2267.0f);
	//	bee3->name = "bee3";
	//	bee3->CreateResources();
	//	AddObject(bee3);

	//	std::shared_ptr<Object2D> crazyLadyBug1 = std::make_shared<EnemyCrazyLadybug>(1180.0f, mapSize.height - 2255.0f, 80.0f, 80.0f);
	//	crazyLadyBug1->name = "crazyLadyBug1";
	//	crazyLadyBug1->CreateResources();
	//	AddObject(crazyLadyBug1);

	//	std::shared_ptr<Object2D> crazyLadyBug2 = std::make_shared<EnemyCrazyLadybug>(1073.0f, mapSize.height - 2127.0f, 100.0f, 100.0f);
	//	crazyLadyBug2->name = "crazyLadyBug2";
	//	crazyLadyBug2->CreateResources();
	//	AddObject(crazyLadyBug2);

	//	std::shared_ptr<Object2D> crazyLadyBug3 = std::make_shared<EnemyCrazyLadybug>(1343.0f, mapSize.height - 2127.0f, 40.0f, 130.0f);
	//	crazyLadyBug3->name = "crazyLadyBug3";
	//	crazyLadyBug3->CreateResources();
	//	AddObject(crazyLadyBug3);

	//	std::shared_ptr<Object2D> worm6 = std::make_shared<EnemyWorm>(1230.0f, mapSize.height - 2055.0f);
	//	worm6->name = "worm6";
	//	worm6->CreateResources();
	//	AddObject(worm6);

	//	std::shared_ptr<Object2D> worm7 = std::make_shared<EnemyWorm>(1152.0f, mapSize.height - 2055.0f);
	//	worm7->name = "worm7";
	//	worm7->CreateResources();
	//	AddObject(worm7);

	//	std::shared_ptr<Object2D> bulletHead4 = std::make_shared<EnemyBulletHead>(1205.0f, mapSize.height - 1864.0f);
	//	bulletHead4->name = "bulletHead4";
	//	bulletHead4->CreateResources();
	//	AddObject(bulletHead4);

	//	std::shared_ptr<Object2D> bulletHead5 = std::make_shared<EnemyBulletHead>(1269.0f, mapSize.height - 1864.0f);
	//	bulletHead5->name = "bulletHead5";
	//	bulletHead5->CreateResources();
	//	AddObject(bulletHead5);

	//	std::shared_ptr<Object2D> bulletHead6 = std::make_shared<EnemyBulletHead>(1357.0f, mapSize.height - 1874.0f);
	//	bulletHead6->name = "bulletHead6";
	//	bulletHead6->CreateResources();
	//	AddObject(bulletHead6);
	//	//
	//	//
	//	//
	//	//ZONE 3
	//	//
	//	//
	//	//
	//	std::shared_ptr<Object2D> skull1 = std::make_shared<EnemySkull>(1760.0f, mapSize.height - 1914.0f);
	//	skull1->name = "skull1";
	//	skull1->CreateResources();
	//	AddObject(skull1);

	//	std::shared_ptr<Object2D> skull2 = std::make_shared<EnemySkull>(1860.0f, mapSize.height - 1914.0f);
	//	skull2->name = "skull2";
	//	skull2->CreateResources();
	//	AddObject(skull2);

	//	std::shared_ptr<Object2D> skull3 = std::make_shared<EnemySkull>(2006.0f, mapSize.height - 1914.0f);
	//	skull3->name = "skull3";
	//	skull3->CreateResources();
	//	AddObject(skull3);
	//	//
	//	//
	//	//
	//	//ZONE 4
	//	//
	//	//
	//	//
	//	std::shared_ptr<Object2D> worm8 = std::make_shared<EnemyWorm>(2241.0f, mapSize.height - 1832.0f);
	//	worm8->name = "worm8";
	//	worm8->CreateResources();
	//	AddObject(worm8);

	//	std::shared_ptr<Object2D> worm9 = std::make_shared<EnemyWorm>(2307.0f, mapSize.height - 1768.0f);
	//	worm9->name = "worm9";
	//	worm9->CreateResources();
	//	AddObject(worm9);

	//	std::shared_ptr<Object2D> ladyBug1 = std::make_shared<EnemyLadybug>(2176.0f, mapSize.height - 1575.0f);
	//	ladyBug1->name = "ladyBug1";
	//	ladyBug1->CreateResources();
	//	AddObject(ladyBug1);

	//	std::shared_ptr<Object2D> ladyBug2 = std::make_shared<EnemyLadybug>(2176.0f, mapSize.height - 1592.0f, -45.0f);
	//	ladyBug2->name = "ladyBug2";
	//	ladyBug2->CreateResources();
	//	AddObject(ladyBug2);

	//	std::shared_ptr<Object2D> worm10 = std::make_shared<EnemyWorm>(2180.0f, mapSize.height - 1383.0f);
	//	worm10->name = "worm10";
	//	worm10->CreateResources();
	//	AddObject(worm10);

	//	std::shared_ptr<Object2D> worm11 = std::make_shared<EnemyWorm>(2244.0f, mapSize.height - 1320.0f);
	//	worm11->name = "worm11";
	//	worm11->CreateResources();
	//	AddObject(worm11);

	//	std::shared_ptr<Object2D> worm12 = std::make_shared<EnemyWorm>(2180.0f, mapSize.height - 1252.0f);
	//	worm12->name = "worm12";
	//	worm12->CreateResources();
	//	AddObject(worm12);
	//	//
	//	//
	//	//
	//	//ZONE 5
	//	//
	//	//
	//	//
	//	std::shared_ptr<Object2D> bee4 = std::make_shared<EnemyBee>(1953.0f, mapSize.height - 1063.0f, 40.0f);
	//	bee4->name = "bee4";
	//	bee4->CreateResources();
	//	AddObject(bee4);

	//	std::shared_ptr<Object2D> bee5 = std::make_shared<EnemyBee>(1794.0f, mapSize.height - 1172.0f);
	//	bee5->name = "bee5";
	//	bee5->CreateResources();
	//	AddObject(bee5);

	//	std::shared_ptr<Object2D> bee6 = std::make_shared<EnemyBee>(1797.0f, mapSize.height - 928.0f);
	//	bee6->name = "bee6";
	//	bee6->CreateResources();
	//	AddObject(bee6);

	//	std::shared_ptr<Object2D> skull4 = std::make_shared<EnemySkull>(1940.0f, mapSize.height - 640.0f);
	//	skull4->name = "skull4";
	//	skull4->CreateResources();
	//	AddObject(skull4);

	//	std::shared_ptr<Object2D> skull5 = std::make_shared<EnemySkull>(1570.0f, mapSize.height - 525.0f);
	//	skull5->name = "skull5";
	//	skull5->CreateResources();
	//	AddObject(skull5);

	//	std::shared_ptr<Object2D> bee7 = std::make_shared<EnemyBee>(1842.0f, mapSize.height - 397.0f);
	//	bee7->name = "bee7";
	//	bee7->CreateResources();
	//	AddObject(bee7);

	//	std::shared_ptr<Object2D> bee8 = std::make_shared<EnemyBee>(1981.0f, mapSize.height - 397.0f);
	//	bee8->name = "bee8";
	//	bee8->CreateResources();
	//	AddObject(bee8);

	//	std::shared_ptr<Object2D> legRobot2 = std::make_shared<EnemyLegRobot>(1984.0f, mapSize.height - 332.0f, true, 25.0f);
	//	legRobot2->name = "legRobot2";
	//	legRobot2->CreateResources();
	//	AddObject(legRobot2);

	//	std::shared_ptr<Object2D> legRobot3 = std::make_shared<EnemyLegRobot>(1817.0f, mapSize.height - 332.0f, true, 60.0f);
	//	legRobot3->name = "legRobot3";
	//	legRobot3->CreateResources();
	//	AddObject(legRobot3);

	//	std::shared_ptr<Object2D> ladyBug3 = std::make_shared<EnemyLadybug>(1665.0f, mapSize.height - 294.0f);
	//	ladyBug3->name = "ladyBug3";
	//	ladyBug3->CreateResources();
	//	AddObject(ladyBug3);

	//	std::shared_ptr<Object2D> ladyBug4 = std::make_shared<EnemyLadybug>(1665.0f, mapSize.height - 311.0f, -45.0f);
	//	ladyBug4->name = "ladyBug4";
	//	ladyBug4->CreateResources();
	//	AddObject(ladyBug4);

	//	std::shared_ptr<Object2D> legRobot4 = std::make_shared<EnemyLegRobot>(1888.0f, mapSize.height - 205.0f, false, 55.0f);
	//	legRobot4->name = "legRobot4";
	//	legRobot4->CreateResources();
	//	AddObject(legRobot4);
	//	//
	//	//
	//	//
	//	//ZONE 6
	//	//
	//	//
	//	//
	//	std::shared_ptr<Object2D> crazyLadyBug4 = std::make_shared<EnemyCrazyLadybug>(2352.0f, mapSize.height - 74.0f, 25.0f, 130.0f);
	//	crazyLadyBug4->name = "crazyLadyBug4";
	//	crazyLadyBug4->CreateResources();
	//	AddObject(crazyLadyBug4);

	//	std::shared_ptr<Object2D> crazyLadyBug5 = std::make_shared<EnemyCrazyLadybug>(2377.0f, mapSize.height - 74.0f, 25.0f, 130.0f);
	//	crazyLadyBug5->name = "crazyLadyBug5";
	//	crazyLadyBug5->CreateResources();
	//	AddObject(crazyLadyBug5);

	//	std::shared_ptr<Object2D> crazyLadyBug6 = std::make_shared<EnemyCrazyLadybug>(2402.0f, mapSize.height - 74.0f, 70.0f, 130.0f);
	//	crazyLadyBug6->name = "crazyLadyBug6";
	//	crazyLadyBug6->CreateResources();
	//	AddObject(crazyLadyBug6);
	//	//
	//	//
	//	//
	//	//ZONE 7
	//	//
	//	//
	//	//
	//	//Scene::SetTopRangeSpawningAdjustmentFactor(10.0f); //cang tang range top cang tang
	//	//Scene::SetLeftRangeSpawningAdjustmentFactor(-90.0f); //cang giam range left cang tang
	//	//Scene::SetRightRangeSpawningAdjustmentFactor(90.0f); //cang tang range right cang tang
	//	std::shared_ptr<Object2D> legRobot5 = std::make_shared<EnemyLegRobot>(2703.0f, mapSize.height - 97.0f, true, 10.0f);
	//	legRobot5->name = "legRobot5";
	//	legRobot5->CreateResources();
	//	AddObject(legRobot5);

	//	std::shared_ptr<Object2D> legRobot6 = std::make_shared<EnemyLegRobot>(2671.0f, mapSize.height - 162.0f, true, 10.0f, 30.0f, 30.0f);
	//	legRobot6->name = "legRobot6";
	//	legRobot6->CreateResources();
	//	AddObject(legRobot6);

	//	std::shared_ptr<Object2D> crab7 = std::make_shared<EnemyCrab>(2713.0f, mapSize.height - 81.0f, -5.0f, 70.0f);
	//	crab7->name = "crab7";
	//	crab7->CreateResources();
	//	AddObject(crab7);

	//	std::shared_ptr<Object2D> crab8 = std::make_shared<EnemyCrab>(2815.0f, mapSize.height - 85.0f, -60.0f, 40.0f);
	//	crab8->name = "crab8";
	//	crab8->CreateResources();
	//	AddObject(crab8);

	//	std::shared_ptr<Object2D> crab9 = std::make_shared<EnemyCrab>(2908.0f, mapSize.height - 85.0f, -50.0f, -50.0f);
	//	crab9->name = "crab9";
	//	crab9->CreateResources();
	//	AddObject(crab9);

	//	std::shared_ptr<Object2D> crab10 = std::make_shared<EnemyCrab>(2915.0f, mapSize.height - 48.0f, 50.0f, -50.0f);
	//	crab10->name = "crab10";
	//	crab10->CreateResources();
	//	AddObject(crab10);

	//	std::shared_ptr<Object2D> ladyBug5 = std::make_shared<EnemyLadybug>(2986.0f, mapSize.height - 94.0f, 45.0f);
	//	ladyBug5->name = "ladyBug5";
	//	ladyBug5->CreateResources();
	//	AddObject(ladyBug5);

	//	std::shared_ptr<Object2D> ladyBug6 = std::make_shared<EnemyLadybug>(2986.0f, mapSize.height - 152.0f, 45.0f);
	//	ladyBug6->name = "ladyBug6";
	//	ladyBug6->CreateResources();
	//	AddObject(ladyBug6);

	//	std::shared_ptr<Object2D> ladyBug7 = std::make_shared<EnemyLadybug>(3026.0f, mapSize.height - 216.0f, -45.0f);
	//	ladyBug7->name = "ladyBug7";
	//	ladyBug7->CreateResources();
	//	AddObject(ladyBug7);

	//	std::shared_ptr<Object2D> ladyBug8 = std::make_shared<EnemyLadybug>(3026.0f, mapSize.height - 276.0f, -45.0f);
	//	ladyBug8->name = "ladyBug8";
	//	ladyBug8->CreateResources();
	//	AddObject(ladyBug8);

	//	std::shared_ptr<Object2D> legRobot7 = std::make_shared<EnemyLegRobot>(2991.0f, mapSize.height - 349.0f, false, 10.0f);
	//	legRobot7->name = "legRobot7";
	//	legRobot7->CreateResources();
	//	AddObject(legRobot7);

	//	std::shared_ptr<Object2D> legRobot8 = std::make_shared<EnemyLegRobot>(2751.0f, mapSize.height - 464.0f, true, 42.0f);
	//	legRobot8->name = "legRobot8";
	//	legRobot8->CreateResources();
	//	AddObject(legRobot8);

	//}
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

	canvas = std::make_unique<Canvas>();
	{
		std::shared_ptr<UIElement> healthBar = std::make_shared<HealthBar>(65.0f, 395.0f);
		healthBar->CreateResources();
		canvas->AddUIElement(healthBar);
	}
}