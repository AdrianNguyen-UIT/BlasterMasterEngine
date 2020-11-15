#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"

class Scene
{
protected:
	std::string name;
	std::shared_ptr<OrthographicCamera> camera;
	std::list<std::shared_ptr<Object2D>> objects;
	LPDIRECT3DSURFACE9 backGround;
	float leftInit;
	float topInit;
	RECT mapRect;
	Size  mapRectSize;
	RECT boundaryRect;

public:
	Scene();
	virtual ~Scene();
	void SetMapRectPosition(float left, float top);
	void AddMapRectPosition(float left, float top);
	std::shared_ptr<OrthographicCamera> GetActiceCamaera() { return camera; }
	void UpdateScene();
	std::string GetName() { return name; }
	void AddObject(const std::shared_ptr<Object2D>& object);
	std::list<std::shared_ptr<Object2D>> GetObjectList() { return objects; }
	LPDIRECT3DSURFACE9 GetBackground() { return backGround; }
	RECT GetMapRect() { return mapRect; }
	virtual void CreateScene() = 0;
};