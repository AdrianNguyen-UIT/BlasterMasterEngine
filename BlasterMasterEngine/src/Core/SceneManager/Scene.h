#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Core/XmlReader/XmlMap.h"
#include "Core/QuadTree/QuadTree.h"
class Scene
{
private:
	bool readyToLoad;

protected:
	std::string name;
	std::shared_ptr<OrthographicCamera> camera;
	std::list<std::shared_ptr<Object2D>> objects;
	std::list<std::shared_ptr<Object2D>> renderableObjects;
	LPDIRECT3DSURFACE9 backGround;
	RECT mapRender;
	Size mapSize;
	std::unique_ptr<XmlMap> xmlMap;

public:
	Scene();
	virtual ~Scene();
	void SetMapRectPosition(float left, float top);
	void AddMapRectPosition(float left, float top);
	std::shared_ptr<OrthographicCamera> GetActiceCamera() { return camera; }
	void UpdateScene();
	std::string GetName() { return name; }
	void AddObject(const std::shared_ptr<Object2D>& object);
	std::list<std::shared_ptr<Object2D>> &GetObjectList() { return objects; }
	LPDIRECT3DSURFACE9 GetBackground() { return backGround; }
	RECT GetMapRender() { return mapRender; }
	virtual void CreateScene() = 0;
	void LoadXmlMap(char* filePath);
	std::list<std::shared_ptr<Object2D>> GetAllRenderableObjects() { return renderableObjects; }
	Size GetMapSize() { return mapSize; }
	void ClearScene();
	void SetReadyToLoad(bool ready) { readyToLoad = ready; }
	bool GetReadyToLoad() { return readyToLoad; }
	std::shared_ptr<Object2D> FinObjectByName(std::string name);
private:
	void UpdateRenderableObjects();

};