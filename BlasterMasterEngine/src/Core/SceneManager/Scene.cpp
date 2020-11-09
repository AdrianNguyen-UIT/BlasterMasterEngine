#include "d3dpch.h"
#include "Scene.h"

Scene::Scene()
{
	backGround = NULL;
}

Scene::~Scene()
{
	backGround->Release();
}

void Scene::UpdateScene()
{
	mapRect.left = (LONG)(leftInit + camera->GetPosition().x * (mapRectSize.width / camera->GetSize().width));
	mapRect.top = (LONG)(topInit - (camera->GetPosition().y - 600.0f) * (mapRectSize.height / camera->GetSize().height));

	if (mapRect.left < boundaryRect.left)
	{
		mapRect.left = boundaryRect.left;
	}
	else if (mapRect.left > boundaryRect.right - mapRectSize.width)
	{
		mapRect.left = boundaryRect.right - (LONG)mapRectSize.width;
	}

	if (mapRect.top < boundaryRect.top)
	{
		mapRect.top = boundaryRect.top;
	}
	else if (mapRect.top > boundaryRect.bottom - mapRectSize.height)
	{
		mapRect.top = boundaryRect.bottom - (LONG)mapRectSize.height;
	}

	mapRect.right = mapRect.left + (LONG)mapRectSize.width;
	mapRect.bottom = mapRect.top + (LONG)mapRectSize.height;
}

void Scene::SetMapRectPosition(float left, float top)
{
	mapRect.left = (LONG)left;
	mapRect.top = (LONG)top;
	UpdateScene();
}

void Scene::AddMapRectPosition(float left, float top)
{
	mapRect.left += (LONG)left;
	mapRect.top += (LONG)top;
	UpdateScene();
}