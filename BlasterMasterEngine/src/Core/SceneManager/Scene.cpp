#include "d3dpch.h"
#include "Scene.h"

Scene::Scene()
{
	readyToLoad = false;
	mapRender = {0, 0, 0, 0};
	mapSize = {0.0f, 0.0f};
	backGround = NULL;
	xmlMap = NULL;
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

	UpdateRenderableObjects();
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

void  Scene::UpdateRenderableObjects()
{
	renderableObjects.clear();
	for (std::shared_ptr<Object2D> object : objects)
	{
		if (object->boxCollider == NULL || !object->boxCollider->isEnable)
		{
			if ((object->transform->position.x >= camera->GetPosition().x - 100.0f &&
				object->transform->position.x <= (camera->GetPosition().x - 100.0f) + (camera->GetSize().width + 100.0f * 2) &&
				object->transform->position.y <= camera->GetPosition().y + 100.0f &&
				object->transform->position.y >= (camera->GetPosition().y + 100.0f) - (camera->GetSize().height + 100.0f * 2)))
			{
				renderableObjects.emplace_back(object);
			}
		}
		else if (object->boxCollider->topLeft.x + object->boxCollider->size.width >= camera->GetPosition().x - 100.0f && 
			object->boxCollider->topLeft.x <= (camera->GetPosition().x - 100.0f) + (camera->GetSize().width + 100.0f * 2) &&
			object->boxCollider->topLeft.y - object->boxCollider->size.height <= camera->GetPosition().y + 100.0f &&
			object->boxCollider->topLeft.y >= (camera->GetPosition().y + 100.0f) - (camera->GetSize().height + 100.0f * 2))
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

	if (camera != NULL)
		camera = NULL;
}