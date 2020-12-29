#pragma once
#include "Object/Object.h"
#include "Object/OrthographicCamera/OrthographicCamera.h"
#include "Core/XmlReader/XmlMap.h"
#include "Core/Canvas/Canvas.h"
#include "Core/QuadTree/QuadTree.h"
class Scene
{
private:
	bool readyToLoad;

protected:
	std::string name;
	std::shared_ptr<OrthographicCamera> camera;
	std::list<std::shared_ptr<Object2D>> objects;
	std::list<std::shared_ptr<Object2D>> collidableObjects;
	std::unique_ptr<Canvas> canvas;
	LPDIRECT3DSURFACE9 backGround;
	RECT mapRender;
	Size mapSize;
	std::unique_ptr<XmlMap> xmlMap;
	std::unique_ptr<QuadTree> quadtree;

public:
	Scene();
	virtual ~Scene();
	virtual void CreateScene() = 0;

public:
	void SetMapRectPosition(float left, float top);
	void AddMapRectPosition(float left, float top);
	void UpdateScene();
	void AddObject(const std::shared_ptr<Object2D>& object);
	void LoadXmlMap(char* filePath);
	void ClearScene();
	std::shared_ptr<Object2D> FinObjectByName(std::string name);
	void StartCanvas();
	void UpdateCanvas();
	void RenderCanvas(DWORD flags);
	void RetrieveCollidableObjects(std::list<std::shared_ptr<Object2D>> &list, std::shared_ptr<Object2D> &object);
	void RetrieveRenderableObjects(std::list<std::shared_ptr<Object2D>>& list);
public:
	std::shared_ptr<OrthographicCamera> GetActiceCamera() { return camera; }
	std::string GetName() { return name; }
	std::list<std::shared_ptr<Object2D>> &GetAllObjects() { return objects; }
	LPDIRECT3DSURFACE9 GetBackground() { return backGround; }
	RECT GetMapRender() { return mapRender; }
	std::list<std::shared_ptr<Object2D>> GetCollidableObjects() { return collidableObjects; }
	Size GetMapSize() { return mapSize; }
	void SetReadyToLoad(bool ready) { readyToLoad = ready; }
	bool GetReadyToLoad() { return readyToLoad; }
	
private:

	void InsertAllObjectInQuadtree();

};