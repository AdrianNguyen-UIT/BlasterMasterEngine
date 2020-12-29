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

	InsertAllObjectInQuadtree();
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
	for (std::shared_ptr<Object2D> object : objects)
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

void  Scene::RetrieveCollidableObjects(std::list<std::shared_ptr<Object2D>> &list, std::shared_ptr<Object2D> &object)
{
	if (quadtree == NULL)
		return;

	list.clear();
	quadtree->Retrieve(list, object);
}

void Scene::RetrieveRenderableObjects(std::list<std::shared_ptr<Object2D>>& list)
{
	list.clear();
	for (std::shared_ptr<Object2D> object : objects)
	{
		if (object->boxCollider == NULL || !object->boxCollider->isEnable)
		{
			if ((object->transform->position.x >= camera->GetPosition().x &&
				object->transform->position.x <= (camera->GetPosition().x) + (camera->GetSize().width) &&
				object->transform->position.y <= camera->GetPosition().y &&
				object->transform->position.y >= (camera->GetPosition().y) - (camera->GetSize().height)))
			{
				list.emplace_back(object);
			}
		}
		else if (object->boxCollider->topLeft.x + object->boxCollider->size.width >= camera->GetPosition().x &&
			object->boxCollider->topLeft.x <= (camera->GetPosition().x) + (camera->GetSize().width) &&
			object->boxCollider->topLeft.y - object->boxCollider->size.height <= camera->GetPosition().y &&
			object->boxCollider->topLeft.y >= (camera->GetPosition().y) - (camera->GetSize().height))
		{
			list.emplace_back(object);
		}
	}
	std::stable_sort(list.begin(), list.end());
}

void Scene::InsertAllObjectInQuadtree()
{
	if (quadtree == NULL)
		return;

	quadtree->Clear();
	for (std::shared_ptr<Object2D> object : objects)
	{
		quadtree->Insert(object);
	}
}

void Scene::ClearScene()
{
	readyToLoad = false;
	objects.clear();
	collidableObjects.clear();
	if (canvas != NULL)
		canvas = NULL;
	if (camera != NULL)
		camera = NULL;
	if (quadtree != NULL)
		quadtree = NULL;
}