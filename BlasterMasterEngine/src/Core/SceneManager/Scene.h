#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"

class Scene
{
protected:
	std::wstring name;
	std::shared_ptr<OrthographicCamera> camera;
	std::list<std::shared_ptr<Object2D>> objects;
	LPDIRECT3DSURFACE9 backGround;
	float leftInit;
	float topInit;
	RECT mapRect;
	Size  mapRectSize;
	RECT boundaryRect;

public:
	friend class SceneManager;
	friend class Renderer;

	Scene();
	virtual ~Scene();
	virtual void SetMapRectPosition(float left, float top);
	virtual void AddMapRectPosition(float left, float top);
	virtual std::shared_ptr<OrthographicCamera> GetActiceCamaera() { return camera; }
	virtual void UpdateScene();
	virtual void CreateScene(std::shared_ptr<DeviceResources> deviceResources) = 0;
};