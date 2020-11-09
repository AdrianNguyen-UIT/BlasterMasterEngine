#include "d3dpch.h"
#include "SceneManager.h"
#include "Samples/MainScene.h"

std::list<std::shared_ptr<Scene>> SceneManager::scenes;
std::shared_ptr<Scene> SceneManager::activeScene;
std::shared_ptr<DeviceResources> SceneManager::m_DeviceResources;
std::list<std::shared_ptr<Object2D>> SceneManager::waitingObjects;
bool SceneManager::updateAfterDestroy = false;
bool SceneManager::updateAfterInstantiate = false;

SceneManager::SceneManager(std::shared_ptr<DeviceResources> p_DeviceResources)
{
	m_DeviceResources = p_DeviceResources;
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::CreateScenesResources()
{
	std::shared_ptr<Scene> mainScene = std::make_shared<MainScene>();
	if (mainScene == NULL)
	{
		__ASSERT(false, "Unable to create scene");
		DWORD dwError = GetLastError();
		return HRESULT_FROM_WIN32(dwError);
	}
	scenes.emplace_back(mainScene);
	return S_OK;
}

bool SceneManager::LoadScene(std::wstring p_Name)
{
	for (auto scene : scenes)
	{
		if (scene->name == p_Name)
		{
			scene->CreateScene(m_DeviceResources);
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
			scene->CreateScene(m_DeviceResources);
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

std::shared_ptr<Scene> SceneManager::GetSceneByName(std::wstring p_Name)
{
	for (auto scene : scenes)
	{
		if (scene->name == p_Name)
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
	for (auto object : activeScene->objects)
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			updateAfterDestroy = true;
			return;
		}
	}

	for (auto object : activeScene->objects)
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::UpdateScene()
{
	activeScene->UpdateScene();

	if (updateAfterDestroy)
	{
		for (auto it = activeScene->objects.begin(); it != activeScene->objects.end();)
		{
			if (CheckReadyToBeDestroy(*it))
			{
				it = activeScene->objects.erase(it);
				updateAfterDestroy = false;
			}
			else
			{
				++it;
			}
		}

		for (auto it = activeScene->objects.begin(); it != activeScene->objects.end();)
		{
			InnerUpdate(*it);
			++it;
		}
	}

	if (updateAfterInstantiate)
	{
		for (auto object : waitingObjects)
		{
			object->InnerStart(m_DeviceResources);
			activeScene->objects.emplace_back(object);
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
	p_Object->transform->position = location;
	waitingObjects.emplace_back(p_Object);
	updateAfterInstantiate = true;
}