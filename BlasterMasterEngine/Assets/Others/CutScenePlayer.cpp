#include "d3dpch.h"
#include "CutScenePlayer.h"
#include "Core/SpriteResources/SpriteResources.h"
#include "Core/SceneManager/SceneManager.h"

CutScenePlayer::CutScenePlayer(float x, float y, CutsceneType cst)
	: Object2D(x, y), cutsceneType(cst)
{
	name = "Cutscene Player";
	tag = Tag::Default;
	spriteRenderer = GetComponent<SpriteRenderer>();
	animationController = GetComponent<AnimationController>();
}

void CutScenePlayer::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X , WINDOW_CAMERA_SCALE_Y, 0.0f};
	allowLoadScene = true;
}

void CutScenePlayer::Update()
{
	if (cutsceneType == CutsceneType::Opening)
	{
		if (allowLoadScene)
		{
			if (animationController->GetCurrentAnimation()->IsFinished())
			{
				allowLoadScene = false;
				SceneManager::ReloadScene("Roll Out Cutscene");
			}
		}
	}
	else if(cutsceneType == CutsceneType::RollOut)
	{
		if (allowLoadScene)
		{
			if (animationController->GetCurrentAnimation()->IsFinished())
			{
				allowLoadScene = false;
				SceneManager::ReloadScene("Loading Screen");
			}
		}
	}
}

void CutScenePlayer::CreateResources()
{
	if (cutsceneType == CutsceneType::Opening)
	{
		spriteRenderer->sprite = SpriteResources::GetSprite("Opening_Cutscene");
		int pauseFrames = 30;
		int fps = 16;
		KeyFrame keyFrame;
		RECT rect;
		keyFrame.scale = { 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Animation> scene = std::make_shared<Animation>("Opening_Cutscene");
		{
			scene->SetAnimationFPS(fps);
			scene->SetIsLooping(false);

			rect = { 0, 0, 256, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 0, 515, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 0, 774, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 0, 1033, 224 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 518, 0, 774, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 0, 515, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 0, 256, 224 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 227, 256, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 227, 515, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 227, 774, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 227, 1033, 451 };
			keyFrame.rect = rect;

			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 518, 227, 774, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 227, 515, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 227, 256, 451 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 454, 256, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 454, 515, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 454, 774, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 454, 1033, 678 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 518, 454, 774, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 454, 515, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 454, 256, 678 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 681, 256, 905 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 681, 515, 905 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 681, 774, 905 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 681, 1033, 905 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames - 10; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 0, 908, 256, 1132 };
			keyFrame.rect = rect;

			for (size_t index = 0; index < pauseFrames - 10; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 259, 908, 515, 1132 };
			keyFrame.rect = rect;

			for (size_t index = 0; index < pauseFrames - 10; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 518, 908, 774, 1132 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 908, 1032, 1132 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 1135, 256, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1135, 515, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1135, 774, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 1135, 1033, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 1362, 256, 1586 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 777, 1135, 1033, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1135, 774, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1135, 515, 1359 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1362, 515, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1362, 774, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 1362, 1033, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 1589, 256, 1813 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 777, 1362, 1033, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1362, 774, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1362, 515, 1586 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1589, 515, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1589, 774, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 1589, 1033, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 1816, 256, 2040 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 777, 1589, 1033, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1589, 774, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1589, 515, 1813 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1816, 515, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1816, 774, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 777, 1816, 1033, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 0, 2043, 256, 2267 };
			keyFrame.rect = rect;
			for (size_t index = 0; index < pauseFrames; index++)
			{
				scene->AddKeyFrames(keyFrame);
			}

			rect = { 777, 1816, 1033, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 518, 1816, 774, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			rect = { 259, 1816, 515, 2040 };
			keyFrame.rect = rect;
			scene->AddKeyFrames(keyFrame);

			animationController->AddAnimation(scene);
			animationController->SetDefaultAnimation(scene);
		}

	}
	else if (cutsceneType == CutsceneType::RollOut)
	{
		spriteRenderer->sprite = SpriteResources::GetSprite("RollOut_Cutscene");
		int departFrames = 15;
		int normalFrames = 1;
		int fps = 16;
		KeyFrame keyFrame;
		RECT rect;
		keyFrame.scale = { 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Animation> scene = std::make_shared<Animation>("RollOut_Cutscene");
		{
			scene->SetAnimationFPS(16);
			scene->SetIsLooping(false);

			for (size_t index = 0; index < departFrames; index++)
			{
				rect = { 0, 0, 256, 224 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);

				rect = { 259, 0, 515, 224 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}
			
			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 518, 0, 774, 224 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 0, 227, 256, 451 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 259, 227, 515, 451 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 518, 227, 774, 451 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}
			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 0, 454, 256, 678 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}
			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 259, 454, 515, 678 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 518, 454, 774, 678 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames; index++)
			{
				rect = { 0, 681, 256, 905 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}

			for (size_t index = 0; index < normalFrames + 5; index++)
			{
				rect = { 0, 454, 256, 678 };
				keyFrame.rect = rect;
				scene->AddKeyFrames(keyFrame);
			}
			animationController->AddAnimation(scene);
			animationController->SetDefaultAnimation(scene);
		}

	}
}