#pragma once
#include "Scene.h"

class SceneManager
{
private:
	static std::list<std::shared_ptr<Scene>> scenes;
	static std::shared_ptr<Scene> activeScene;
	static std::list<std::shared_ptr<Object2D>> waitingObjects;
	static bool updateAfterDestroy;
	static bool updateAfterInstantiate;
public:
	SceneManager();
	~SceneManager();
	HRESULT CreateScenesResources();
	static bool LoadScene(std::string p_Name);
	static bool LoadScene(size_t index);

	static std::shared_ptr<Scene> GetActiveScene();
	static std::shared_ptr<Scene> GetSceneByName(std::string p_Name);
	static std::shared_ptr<Scene> GetSceneByIndex(size_t index);
	static void DestroyObject(std::shared_ptr<Object2D> p_Object);
	static void Instantiate(std::shared_ptr<Object2D> p_Object, D3DXVECTOR3 location = {0.0f, 0.0f, 0.0f});
	static void UpdateScene();

private:
	static bool CheckReadyToBeDestroy(std::shared_ptr<Object2D> p_Object);
	static void InnerUpdate(std::shared_ptr<Object2D> p_Object);
	static void InnerDestroyObject(std::shared_ptr<Object2D> childIt, std::shared_ptr<Object2D> p_Object);
};