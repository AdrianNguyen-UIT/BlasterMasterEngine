#include "d3dpch.h"
#include "Scene.h"

Scene::Scene()
{
	mapRender = {0, 0, 0, 0};
	mapSize = {0.0f, 0.0f};
	backGround = NULL;
}

Scene::~Scene()
{
	backGround->Release();
	quadTree->Clear();
}

void Scene::UpdateScene()
{
	mapRender.left = (LONG)(camera->GetPosition().x);
	mapRender.top = (LONG)(mapSize.height - camera->GetPosition().y);
	mapRender.right = mapRender.left + (LONG)(camera->GetSize().width);
	mapRender.bottom = mapRender.top + (LONG)(camera->GetSize().height);
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

void Scene::AddPlayer(const std::shared_ptr<Object2D>& object)
{
	player = object;
}

void Scene::LoadXmlMap(char* filePath)
{
	xmlMap.ParseFile(filePath);
}

void  Scene::UpdateCollideableObjects()
{
	collideableObjects.clear();
	quadTree->GetObjectsCollideAble(collideableObjects, player);
}