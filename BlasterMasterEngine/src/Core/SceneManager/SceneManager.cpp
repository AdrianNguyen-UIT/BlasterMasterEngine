#include "d3dpch.h"
#include "SceneManager.h"
#include "Samples/MainScene.h"
#include "Assets/Scenes/Area2.h"

std::list<std::shared_ptr<Scene>> SceneManager::scenes;
std::shared_ptr<Scene> SceneManager::activeScene;
std::list<std::shared_ptr<Object2D>> SceneManager::waitingObjects;
bool SceneManager::updateAfterDestroy = false;
bool SceneManager::updateAfterInstantiate = false;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::CreateScenesResources()
{
	std::shared_ptr<Scene> scene = std::make_shared<Area2>();
	if (scene == NULL)
	{
		__ASSERT(false, "Unable to create scene");
		DWORD dwError = GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}
	scenes.emplace_back(scene);
	return S_OK;
}

bool SceneManager::LoadScene(std::string p_Name)
{
	for (auto scene : scenes)
	{
		if (scene->GetName() == p_Name)
		{
			scene->CreateScene();
			activeScene = scene;
			return true;
		}
	}
	return false;
}

bool SceneManager::LoadScene(size_t index)
{
	size_t currentIndex = 0;
	for (auto scene : scenes)
	{
		if (currentIndex == index)
		{
			scene->CreateScene();
			activeScene = scene;
			return true;
		}
		++currentIndex;
	}
	return false;
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return activeScene;
}

std::shared_ptr<Scene> SceneManager::GetSceneByName(std::string p_Name)
{
	for (auto scene : scenes)
	{
		if (scene->GetName() == p_Name)
		{
			return scene;
		}
	}

	return NULL;
}

std::shared_ptr<Scene> SceneManager::GetSceneByIndex(size_t index)
{
	size_t currentIndex = 0;
	for (auto scene : scenes)
	{
		if (currentIndex == index)
		{
			return scene;
		}
		++currentIndex;
	}

	return NULL;
}

void SceneManager::DestroyObject(std::shared_ptr<Object2D> p_Object)
{
	for (auto object : activeScene->GetObjectList())
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			updateAfterDestroy = true;
			return;
		}
	}

	for (auto object : activeScene->GetObjectList())
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::UpdateScene()
{
	activeScene->UpdateScene();

	if (updateAfterDestroy)
	{
		for (auto it = activeScene->GetObjectList().begin(); it != activeScene->GetObjectList().end();)
		{
			if (CheckReadyToBeDestroy(*it))
			{
				it = activeScene->GetObjectList().erase(it);
				updateAfterDestroy = false;
			}
			else
			{
				++it;
			}
		}

		for (auto object : activeScene->GetObjectList())
		{
			InnerUpdate(object);
		}
	}

	if (updateAfterInstantiate)
	{
		for (auto object : waitingObjects)
		{
			object->InnerStart();
			activeScene->AddObject(object);
		}
		waitingObjects.clear();
		updateAfterInstantiate = false;
	}
}

bool SceneManager::CheckReadyToBeDestroy(std::shared_ptr<Object2D> p_Object)
{
	return p_Object->readyToBeDestroy;

}

void SceneManager::InnerUpdate(std::shared_ptr<Object2D> p_Object)
{
	for (auto it = p_Object->childObjects.begin(); it != p_Object->childObjects.end();)
	{
		if (CheckReadyToBeDestroy(*it))
		{
			it = p_Object->childObjects.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto it = p_Object->childObjects.begin(); it != p_Object->childObjects.end();)
	{
		InnerUpdate(*it);
		++it;
	}
}

void SceneManager::InnerDestroyObject(std::shared_ptr<Object2D> childIt, std::shared_ptr<Object2D> p_Object)
{
	for (auto object : childIt->childObjects)
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			return;
		}
	}

	for (auto object : childIt->childObjects)
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::Instantiate(std::shared_ptr<Object2D> p_Object, D3DXVECTOR3 location)
{
	static int index = 0;
	p_Object->name += std::to_string(index);
	p_Object->transform->position = location;
	waitingObjects.emplace_back(p_Object);
	updateAfterInstantiate = true;
}