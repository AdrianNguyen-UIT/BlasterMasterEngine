#include "d3dpch.h"
#include "SceneManager.h"
#include "Samples/MainScene.h"
#include "Assets/Scenes/Area2.h"
#include "Assets/Scenes/LoadingScreen.h"
#include "Assets/Scenes/OpeningCutscene.h"
#include "Assets/Scenes/OpeningScreen.h"
#include "Assets/Scenes/RollOutCutscene.h"
#include "Assets/Scenes/GameOverScreen.h"
#include "Assets/Scenes/EndingCutscene.h"
#include "Assets/Scenes/Credit.h"
std::vector<std::shared_ptr<Scene>> SceneManager::scenes;
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
	scenes.reserve(8);

	std::shared_ptr<Scene> area2 = std::make_shared<Area2>();
	//area2->CreateScene();
	//activeScene = area2;
	scenes.emplace_back(area2);

	std::shared_ptr<Scene> loadingScreen = std::make_shared<LoadingScreen>();
	//loadingScreen->CreateScene();
	//activeScene = loadingScreen;
	scenes.emplace_back(loadingScreen);

	std::shared_ptr<Scene> openingCutscene = std::make_shared<OpeningCutscene>();
	//openingCutscene->CreateScene();
	scenes.emplace_back(openingCutscene);
	//activeScene = openingCutscene;

	std::shared_ptr<Scene> openingScreen = std::make_shared<OpeningScreen>();
	//openingScreen->CreateScene();
	scenes.emplace_back(openingScreen);
	//activeScene = openingScreen;

	std::shared_ptr<Scene> rolloutCutscene = std::make_shared<RollOutCutscene>();
	//rolloutCutscene->CreateScene();
	scenes.emplace_back(rolloutCutscene);
	//activeScene = rolloutCutscene;

	std::shared_ptr<Scene> gameOverScreen = std::make_shared<GameOverScreen>();
	//gameOverScreen->CreateScene();
	scenes.emplace_back(gameOverScreen);
	//activeScene = gameOverScreen;

	std::shared_ptr<Scene> endingCutScene = std::make_shared<EndingCutscene>();
	endingCutScene->CreateScene();
	scenes.emplace_back(endingCutScene);
	activeScene = endingCutScene;

	std::shared_ptr<Scene> credit = std::make_shared<Credit>();
	//credit->CreateScene();
	scenes.emplace_back(credit);
	//activeScene = credit;

	return S_OK;
}



void SceneManager::ReloadScene(std::string p_Name)
{

	std::thread thread([=]
		{
			std::mutex m;
			for (std::shared_ptr<Scene> scene : scenes)
			{
				if (scene->GetName() == p_Name)
				{
					LOG_TRACE("Reloading Scene [{0}]", p_Name);
					scene->ClearScene();
					scene->CreateScene();
					scene->SetReadyToLoad(true);
				}
			}
			LOG_INFO("FINISHED!");
		});

	if (thread.joinable())
	{
		thread.detach();
	}
}

void SceneManager::ReloadScene(size_t index)
{
	std::thread thread([&index]
		{
			size_t currentIndex = 0;
			for (std::shared_ptr<Scene> scene : scenes)
			{
				if (currentIndex == index)
				{
					LOG_TRACE("Reloading Scene [{0}]", scene->GetName());
					scene->ClearScene();
					scene->CreateScene();
					scene->SetReadyToLoad(true);
				}
				++currentIndex;
			}
			LOG_INFO("FINISHED!");
		});

	if (thread.joinable())
	{
		thread.detach();
	}
}

void SceneManager::LoadScene(std::string p_Name)
{
	std::thread thread([=]
		{
			for (std::shared_ptr<Scene> scene : scenes)
			{
				if (scene->GetName() == p_Name)
				{
					LOG_TRACE("Reloading Scene [{0}]", p_Name);
					scene->SetReadyToLoad(true);
				}
			}
			LOG_INFO("FINISHED!");
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
					LOG_TRACE("Reloading Scene [{0}]", scene->GetName());
					scene->SetReadyToLoad(true);
				}
				++currentIndex;
			}
			LOG_INFO("FINISHED!");
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
	for (std::shared_ptr<Object2D> object : activeScene->GetAllObjects())
	{
		if (object->name == p_Object->name)
		{
			object->readyToBeDestroy = true;
			updateAfterDestroy = true;
			return;
		}
	}

	for (std::shared_ptr<Object2D> object : activeScene->GetAllObjects())
	{
		InnerDestroyObject(object, p_Object);
	}
}

void SceneManager::UpdateScene()
{
	if (updateAfterDestroy)
	{
		for (auto it = activeScene->GetAllObjects().begin(); it != activeScene->GetAllObjects().end();)
		{
			if (CheckReadyToBeDestroy(*it))
			{
				it = activeScene->GetAllObjects().erase(it);
				updateAfterDestroy = false;
			}
			else
			{
				++it;
			}
		}

		for (std::shared_ptr<Object2D> object : activeScene->GetAllObjects())
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