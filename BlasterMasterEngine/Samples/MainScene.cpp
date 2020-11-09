#include "d3dpch.h"
#include "MainScene.h"
#include "Samples/Player.h"
#include "Samples/Dummy.h"
#include "Core/Core.h"

void MainScene::CreateScene(std::shared_ptr<DeviceResources> deviceResources)
{
	camera = std::make_shared<OrthographicCamera>(0.0f, 600.0f, WIDTH, HEIGHT);

	backGround = deviceResources->LoadSurface(BITMAP_PATH, 0);

	mapRectSize.width = 240;
	mapRectSize.height = 215;
	boundaryRect = {0, 0, 2048, 2048};
	leftInit = 268;
	topInit = 790;

	{
		std::shared_ptr<Object2D> player = std::make_shared<Player>(600.0f, 300.0f);
		player->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 0);
		player->CreateResources();
		objects.emplace_back(player);
	}

	{
		std::shared_ptr<Object2D> dummy = std::make_shared<Dummy>(800.0f, 100.0f);
		dummy->name = "Dummy 1";
		dummy->boxCollider->size = { 1600.0f, 50.0f };
		//dummy->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 0);
		dummy->CreateResources();
		objects.emplace_back(dummy);
	}

	{
		std::shared_ptr<Object2D> dummy2 = std::make_shared<Dummy>(0.0f, 100.0f);
		dummy2->name = "Dummy 2";
		dummy2->boxCollider->size = { 100.0f, 200.0f };
		//dummy2->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 0);
		dummy2->CreateResources();
		objects.emplace_back(dummy2);
	}

	{
		std::shared_ptr<Object2D> dummy3 = std::make_shared<Dummy>(1650.0f, 300.0f);
		dummy3->name = "Dummy 3";
		dummy3->boxCollider->size = { 100.0f, 600.0f };
		//dummy3->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 0);
		dummy3->CreateResources();
		objects.emplace_back(dummy3);
	}

	{
		std::shared_ptr<Object2D> dummy4 = std::make_shared<Dummy>(300.0f, 100.0f);
		dummy4->name = "Dummy 4";
		dummy4->boxCollider->size = { 300.0f, 100.0f };
		//dummy4->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 1);
		dummy4->CreateResources();
		objects.emplace_back(dummy4);
	}

	{
		std::shared_ptr<Object2D> dummy5 = std::make_shared<Dummy>(1500.0f, 100.0f);
		dummy5->name = "Dummy 5";
		dummy5->boxCollider->size = { 100.0f, 200.0f };
		//dummy4->spriteRenderer->sprite = deviceResources->LoadTexture(TEXTURE_PATH, 1);
		dummy5->CreateResources();
		objects.emplace_back(dummy5);
	}
}