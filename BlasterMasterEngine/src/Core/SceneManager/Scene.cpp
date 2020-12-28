#include "d3dpch.h"
#include "Scene.h"

Scene::Scene()
{
	readyToLoad = false;
	mapRender = {0, 0, 0, 0};
	mapSize = {0.0f, 0.0f};
	backGround = NULL;
	xmlMap = NULL;
	canvas = NULL;
}

Scene::~Scene()
{
	ClearScene();
}

void Scene::UpdateScene()
{
	mapRender.left = (LONG)(camera->GetPosition().x);
	mapRender.top = (LONG)(mapSize.height - camera->GetPosition().y);
	mapRender.right = mapRender.left + (LONG)(camera->GetSize().width);
	mapRender.bottom = mapRender.top + (LONG)(camera->GetSize().height);

	CollectRenderableObjects();
}

void Scene::SetMapRectPosition(float left, float top)
{
	mapRender.left = (LONG)left;
	mapRender.top = (LONG)top;
	UpdateScene();
}

void Scene::AddMapRectPosition(float left, float top)
{
	mapRender.left += (LONG)left;
	mapRender.top += (LONG)top;
	UpdateScene();
}

void Scene::AddObject(const std::shared_ptr<Object2D>& object)
{
	objects.emplace_back(object);
}

void Scene::LoadXmlMap(char* filePath)
{
	xmlMap = std::make_unique<XmlMap>();
	xmlMap->ParseFile(filePath);
}

bool operator<(const std::shared_ptr<Object2D>& object1, const std::shared_ptr<Object2D>& object2)
{
	return object1->layer < object2->layer;
}

std::shared_ptr<Object2D> Scene::FinObjectByName(std::string name)
{
	for (std::shared_ptr<Object2D> object : renderableObjects)
	{
		if (object->name == name)
		{
			return object;
		}
	}
	return NULL;
}

void Scene::StartCanvas()
{
	if (canvas != NULL)
	{
		if (canvas->GetEnable())
		{
			canvas->Start();
		}
	}
}

void Scene::UpdateCanvas()
{
	if (canvas != NULL)
	{
		if (canvas->GetEnable())
		{
			canvas->Update();
		}
	}
}

void Scene::RenderCanvas(DWORD flags)
{
	if (canvas != NULL)
	{
		if (canvas->GetEnable())
		{
			canvas->Render(flags);
		}
	}
}

void  Scene::CollectRenderableObjects()
{
	renderableObjects.clear();
	for (std::shared_ptr<Object2D> object : objects)
	{
		if (object->boxCollider == NULL || !object->boxCollider->isEnable)
		{
			if ((object->transform->position.x >= camera->GetPosition().x - 30.0f &&
				object->transform->position.x <= (camera->GetPosition().x) + (camera->GetSize().width + 30.0f) &&
				object->transform->position.y <= camera->GetPosition().y + 30.0f &&
				object->transform->position.y >= (camera->GetPosition().y) - (camera->GetSize().height) - 30.0f))
			{
				renderableObjects.emplace_back(object);
			}
		}
		else if (object->boxCollider->topLeft.x + object->boxCollider->size.width >= camera->GetPosition().x - 30.0f && 
			object->boxCollider->topLeft.x <= (camera->GetPosition().x) + (camera->GetSize().width + 30.0f) &&
			object->boxCollider->topLeft.y - object->boxCollider->size.height <= camera->GetPosition().y + 30.0f&&
			object->boxCollider->topLeft.y >= (camera->GetPosition().y) - (camera->GetSize().height) - 30.0f)
		{
			renderableObjects.emplace_back(object);
		}
	}

	std::stable_sort(renderableObjects.begin(), renderableObjects.end());
}

void Scene::ClearScene()
{
	readyToLoad = false;
	objects.clear();
	renderableObjects.clear();
	if (canvas != NULL)
		canvas = NULL;
	if (camera != NULL)
		camera = NULL;
}