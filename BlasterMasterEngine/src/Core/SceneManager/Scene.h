#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Core/XmlReader/XmlMap.h"
#include "Core/QuadTree/QuadTree.h"
class Scene
{
protected:
	std::string name;
	std::shared_ptr<OrthographicCamera> camera;
	std::shared_ptr<Object2D> player;
	std::list<std::shared_ptr<Object2D>> objects;
	std::list<std::shared_ptr<Object2D>> collideableObjects;
	LPDIRECT3DSURFACE9 backGround;
	RECT mapRender;
	Size mapSize;
	XmlMap xmlMap;
	std::unique_ptr<QuadTree> quadTree;
public:
	Scene();
	virtual ~Scene();
	void SetMapRectPosition(float left, float top);
	void AddMapRectPosition(float left, float top);
	std::shared_ptr<OrthographicCamera> GetActiceCamaera() { return camera; }
	void UpdateScene();
	std::string GetName() { return name; }
	void AddObject(const std::shared_ptr<Object2D>& object);
	void AddPlayer(const std::shared_ptr<Object2D>& object);
	std::list<std::shared_ptr<Object2D>> &GetObjectList() { return objects; }
	std::shared_ptr<Object2D>& GetPlayer() { return player; }
	LPDIRECT3DSURFACE9 GetBackground() { return backGround; }
	RECT GetMapRender() { return mapRender; }
	virtual void CreateScene() = 0;
	void LoadXmlMap(char* filePath);
	void UpdateCollideableObjects();
	std::list<std::shared_ptr<Object2D>> GetAllCollideableObjects() { return collideableObjects; }
};