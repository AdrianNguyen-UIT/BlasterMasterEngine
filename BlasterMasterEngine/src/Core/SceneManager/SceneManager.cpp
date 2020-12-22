#include "d3dpch.h"
#include "SceneManager.h"
#include "Samples/MainScene.h"
#include "Assets/Scenes/Area2.h"
#include "Assets/Scenes/LoadingScreen.h"
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
	std::shared_ptr<Scene> area2 = std::make_shared<Area2>();
	std::shared_ptr<Scene> loadingScreen = std::make_shared<LoadingScreen>();

	scenes.emplace_back(area2);
	scenes.emplace_back(loadingScreen);

	LoadInitScene(0);

	return S_OK;
}

void SceneManager::LoadScene(std::string p_Name)
{
	std::thread thread([=]
		{
			for (std::shared_ptr<Scene> scene : scenes)
			{
				if (scene->GetName() == p_Name)
				{
					scene->ClearScene();
					scene->CreateScene();
					scene->SetReadyToLoad(true);
				}
			}
		});

	if (thread.joinable())
	{
		thread.detach();
	}
}

void SceneManager::LoadScene(size_t index)
{
	std::thread thread([&index]
		{
			size_t currentIndex = 0;
			for (std::shared_ptr<Scene> scene : scenes)
			{
				if (currentIndex == index)
				{
					scene->ClearScene();
					scene->CreateScene();
					scene->SetReadyToLoad(true);
				}
				++currentIndex;
			}
		});

	if (thread.joinable())
	{
		thread.detach();
	}
}

std::shared_ptr<Scene> SceneManager::GetActiveScene()
{
	return activeScene;
}

std::shared_ptr<Scene> SceneManager::GetSceneByName(std::string p_Name)
{
	for (std::shared_ptr<Scene> scene : scenes)
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
	for (std::shared_ptr<Scene> scene : scenes)
	{
		if (currentIndex == index)
		{
			return scene;
		}
		++currentIndex;
	}

	return NULL;
}

void SceneManager::DestroyObject(std::shared_ptr<Object2D> &p_Object)
{
	for (std::shared_ptr<Object2D> object : activeScene->GetObjectList())
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			updateAfterDestroy = true;
			return;
		}
	}

	for (std::shared_ptr<Object2D> object : activeScene->GetObjectList())
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::UpdateScene()
{
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

		for (std::shared_ptr<Object2D> object : activeScene->GetObjectList())
		{
			InnerUpdate(object);
		}
	}

	if (updateAfterInstantiate)
	{
		for (std::shared_ptr<Object2D> object : waitingObjects)
		{
			object->InnerStart();
			activeScene->AddObject(object);
		}
		waitingObjects.clear();
		updateAfterInstantiate = false;
	}

	activeScene->UpdateScene();
}

bool SceneManager::CheckReadyToBeDestroy(std::shared_ptr<Object2D> &p_Object)
{
	return p_Object->readyToBeDestroy;

}

void SceneManager::InnerUpdate(std::shared_ptr<Object2D> &p_Object)
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

void SceneManager::InnerDestroyObject(std::shared_ptr<Object2D> &childIt, std::shared_ptr<Object2D> &p_Object)
{
	for (std::shared_ptr<Object2D> object : childIt->childObjects)
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			return;
		}
	}

	for (std::shared_ptr<Object2D> object : childIt->childObjects)
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::Instantiate(std::shared_ptr<Object2D> &p_Object, D3DXVECTOR3 location)
{
	static int index = 0;
	p_Object->name += std::to_string(index);
	++index;
	p_Object->transform->position = location;

	waitingObjects.emplace_back(p_Object);
	updateAfterInstantiate = true;
}

void SceneManager::LoadInitScene(std::string p_Name)
{
	for (std::shared_ptr<Scene> scene : scenes)
	{
		if (scene->GetName() == p_Name)
		{
			scene->ClearScene();
			scene->CreateScene();
			activeScene = scene;
			break;
		}
	}
}

void SceneManager::LoadInitScene(size_t index)
{
	size_t currentIndex = 0;
	for (std::shared_ptr<Scene> scene : scenes)
	{
		if (currentIndex == index)
		{
			scene->ClearScene();
			scene->CreateScene();
			activeScene = scene;
			break;
		}
		++currentIndex;
	}
}

bool SceneManager::LoadActiveScene()
{
	for (std::shared_ptr<Scene> scene : scenes)
	{
		if (scene->GetReadyToLoad() == true)
		{
			scene->SetReadyToLoad(false);
			activeScene = scene;
			return true;
			break;
		}
	}
	return false;
}