#include "d3dpch.h"
#include "BossRoomArea2.h"
#include "Core/SceneManager/SceneManager.h"

#include "Assets/Characters/Enemy/BossArea2/BossArea2.h"
#include "Assets/Others/Item/BreakWallBulletItem/BreakWallBulletItem.h"
#include "Core/AudioMixer/AudioMixer.h"

BossRoomArea2::BossRoomArea2(float x, float y)
	: Object2D(x, y)
{
	name = "BossRoom";
	tag = Tag::Default;
	layer = Layer::Ladder;
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	animationController = GetComponent<AnimationController>();

	EnableEnterBossRoom = true;
	isJoinedBossRoom = false;
	isAlreadyAppear = false;
	isLoadBlackBackground = false;
	isDisappear = false;
}

void BossRoomArea2::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Boss_Room_Texture");
	KeyFrame keyFrame;
	RECT rect = { 0,0,0,0 };
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	int width = 260;
	int height = 268;
	int XOffset = 2;
	int YOffSet = 2;

#pragma region Animation
	std::shared_ptr<Animation> NormalBossRoom = std::make_shared<Animation>("Normal Boss Room");
	{
		NormalBossRoom->SetAnimationFPS(1);
		rect.left += XOffset;
		rect.top += YOffSet;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		keyFrame.rect = rect;

		NormalBossRoom->AddKeyFrames(keyFrame);
		animationController->AddAnimation(NormalBossRoom);
	}

	std::shared_ptr<Animation> EnterBossRoom = std::make_shared<Animation>("Enter Boss Room");
	{
		EnterBossRoom->SetAnimationFPS(9);

		rect.left = rect.right + XOffset;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		keyFrame.rect = rect;
		EnterBossRoom->AddKeyFrames(keyFrame);

		rect.left = XOffset;
		rect.top = rect.bottom + YOffSet;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		keyFrame.rect = rect;
		EnterBossRoom->AddKeyFrames(keyFrame);

		rect.left = rect.right + XOffset;
		rect.right = rect.left + width;
		rect.bottom = rect.top + height;
		keyFrame.rect = rect;
		EnterBossRoom->AddKeyFrames(keyFrame);

		animationController->AddAnimation(EnterBossRoom);
	}

	animationController->SetDefaultAnimation(NormalBossRoom);

#pragma endregion

	std::shared_ptr<Parameter<bool>> EnableEnter = std::make_shared<Parameter<bool>>("EnableEnter");
	{
		animationController->AddBoolParameter(EnableEnter);
	}

	std::shared_ptr<Parameter<bool>> JoinRoom = std::make_shared<Parameter<bool>>("JoinRoom");
	{
		animationController->AddBoolParameter(JoinRoom);
	}

	std::shared_ptr<TransitionCondition<bool>> isJoinedRoom = std::make_shared<TransitionCondition<bool>>();
	{
		isJoinedRoom->SetParameter(JoinRoom);
		isJoinedRoom->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isExitRoom = std::make_shared<TransitionCondition<bool>>();
	{
		isExitRoom->SetParameter(JoinRoom);
		isExitRoom->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<bool>> isEnableEnter = std::make_shared<TransitionCondition<bool>>();
	{
		isEnableEnter->SetParameter(EnableEnter);
		isEnableEnter->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isDisableEnter = std::make_shared<TransitionCondition<bool>>();
	{
		isDisableEnter->SetParameter(EnableEnter);
		isDisableEnter->SetValue(false);
	}

	std::shared_ptr<Transition> normalToEnterRoom = std::make_shared<Transition>(
		animationController->GetAnimationIndex(NormalBossRoom),
		animationController->GetAnimationIndex(EnterBossRoom));
	{
		normalToEnterRoom->AddBoolTransitionCondition(isEnableEnter);
		normalToEnterRoom->AddBoolTransitionCondition(isJoinedRoom);
		animationController->AddTransition(normalToEnterRoom);
	}

	std::shared_ptr<Transition> enterToNormalRoom1 = std::make_shared<Transition>(
		animationController->GetAnimationIndex(EnterBossRoom),
		animationController->GetAnimationIndex(NormalBossRoom));
	{
		enterToNormalRoom1->AddBoolTransitionCondition(isDisableEnter);
		animationController->AddTransition(enterToNormalRoom1);
	}

	std::shared_ptr<Transition> enterToNormalRoom2 = std::make_shared<Transition>(
		animationController->GetAnimationIndex(EnterBossRoom),
		animationController->GetAnimationIndex(NormalBossRoom));
	{
		enterToNormalRoom2->AddBoolTransitionCondition(isEnableEnter);
		enterToNormalRoom2->AddBoolTransitionCondition(isExitRoom);
		animationController->AddTransition(enterToNormalRoom2);
	}

	// background object resource
	{
		backgroundObj = std::make_shared<Object2D>(transform->position.x, transform->position.y);
		backgroundObj->spriteRenderer = GetComponent<SpriteRenderer>();
		backgroundObj->tag = Tag::Default;
		backgroundObj->layer = Layer::Ladder;
		backgroundObj->spriteRenderer->sprite = SpriteResources::GetSprite("Boss_Room_Texture");
		backgroundObj->transform->scale = { WINDOW_CAMERA_SCALE_X ,WINDOW_CAMERA_SCALE_Y,0.0f };
		rect = { 2,2,262,270 };
		backgroundObj->spriteRenderer->rect = rect;
		backgroundObj->color = Color(0, 0, 0, 0);
		SceneManager::Instantiate(backgroundObj, transform->position);
	}
}

void BossRoomArea2::Start()
{
	boxCollider->isTrigger = true;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
	boxCollider->size = { 260.0f, 268.0f };
	boxCollider->topLeft = { (transform->position.x - boxCollider->size.width / 2.0f), (transform->position.y + boxCollider->size.height / 2.0f) };
	animationController->SetBool("EnableEnter", EnableEnterBossRoom);
	animationController->SetBool("JoinRoom", isJoinedBossRoom);

	
}

void BossRoomArea2::Update()
{
	CheckIsJoinedRoom();
	if (isJoinedBossRoom)
	{
		DoIFrame_BeforBossAppear();
	}
	else
	{
		backgroundObj->color = Color(0, 0, 0, 0);
	}

	if (boss != nullptr)
	{
		if (std::dynamic_pointer_cast<BossArea2>(boss)->GetIsDisappear() == true && isAlreadyAppear)
		{
			Die();
		}
	}

	if (isDisappear)
	{
		static float iFrameTime = 0.0f;
		static bool isDestroyBackground = false;
		if (iFrameTime <= 1.5f)
		{
			layer = Layer::Gate;
			int index = (int)(iFrameTime / Time::GetFixedDeltaTime());
			int indexColor = (int)(abs(300 - 6 * index)) - 45;
			indexColor = indexColor < 0 ? 0 : indexColor;
			color = Color(0, 0, 0, 255 - indexColor);
		}
		else if (iFrameTime > 1.5f)
		{
			std::shared_ptr <BreakWallBulletItem> item = std::make_shared<BreakWallBulletItem>(transform->position.x, transform->position.y + 35.0f);
			item->CreateResources();
			SceneManager::Instantiate(std::dynamic_pointer_cast<Object2D>(item), item->transform->position);
			SceneManager::DestroyObject(shared_from_this());
		}

		if (iFrameTime >= 0.75f && !isDestroyBackground)
		{
			isDestroyBackground = true;
			SceneManager::DestroyObject(backgroundObj);
		}
		iFrameTime += Time::GetDeltaTime();
	}

	SetAnimationParameter();
}

void BossRoomArea2::SetAnimationParameter()
{
	animationController->SetBool("EnableEnter", EnableEnterBossRoom);
	animationController->SetBool("JoinRoom", isJoinedBossRoom);
}

void BossRoomArea2::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
	isJoinedBossRoom = true;
}

void BossRoomArea2::OnTriggerExit(std::shared_ptr<Object2D> object)
{
	isJoinedBossRoom = false;
	EnableEnterBossRoom = true;
}

void BossRoomArea2::CheckIsJoinedRoom()
{
	std::shared_ptr<Object2D> player = SceneManager::GetActiveScene()->FinObjectByName("OverworldJason");
	if (!(player->boxCollider->topLeft.x + player->boxCollider->size.width < boxCollider->topLeft.x ||
		boxCollider->topLeft.x + boxCollider->size.width < player->boxCollider->topLeft.x ||
		player->boxCollider->topLeft.y - player->boxCollider->size.height > boxCollider->topLeft.y ||
		boxCollider->topLeft.y - boxCollider->size.height > player->boxCollider->topLeft.y))
	{
		if (isJoinedBossRoom == false)
		{
			isJoinedBossRoom = true;
			//? Play audio INTRO and Stop AREA 2 THEME
			AudioMixer::Stop("AREA2_THEME");
			AudioMixer::PlayWaveFile("BOSS_INTRO", true);
		}
	}
	else
	{
		if (isJoinedBossRoom == true)
		{
			isJoinedBossRoom = false;
			EnableEnterBossRoom = true;
		}
	}
}

void BossRoomArea2::SetState(bool EnableEnter, bool JoinedRoom, bool AlreadyAppear)
{
	EnableEnterBossRoom = EnableEnter;
	isJoinedBossRoom = JoinedRoom;
	isAlreadyAppear = AlreadyAppear;
}

void BossRoomArea2::Die()
{
	boxCollider->isEnable = false;
	isDisappear = true;
}

void BossRoomArea2::DoIFrame_BeforBossAppear()
{
	if (EnableEnterBossRoom || !isAlreadyAppear)
	{
		static float iFrameTime = 0.0f;

		backgroundObj->spriteRenderer->sprite = SpriteResources::GetSprite("White_Background");

		if (iFrameTime >= 3.9f && iFrameTime <= 4.0f)
		{
			EnableEnterBossRoom = false;
			animationController->SetBool("EnableEnter", EnableEnterBossRoom);
			color = Color(0, 0, 0, 0);
		}
		else if (iFrameTime >= 4.0f && iFrameTime <= 6.0f)
		{
			layer = Layer::Gate;
			int index = (int)((iFrameTime - 4.0f) / Time::GetFixedDeltaTime());
			int indexColor = (int)(abs(360 - 6 * index)) - 105;
			indexColor = indexColor < 0 ? 0 : indexColor;
			color = Color(0, 0, 0, 255 - indexColor);
		}
		else if (iFrameTime > 6.0f)
		{
			color = Color(0, 0, 0, 0);
			isAlreadyAppear = true;
			iFrameTime = 0;
		}

		if (iFrameTime >= 5.0f && backgroundObj->color.alpha == 0)
		{
			backgroundObj->color = Color(0, 0, 0, 255);
			// create boss
			boss = std::make_shared<BossArea2>(transform->position.x, transform->position.y + 50.0f);
			SceneManager::Instantiate(boss, boss->transform->position);
			boss->CreateResources();
			RECT rect;
			rect.left = transform->position.x - boxCollider->size.width / 2 + 30;
			rect.top = transform->position.y + boxCollider->size.height / 2 - 30;
			rect.bottom = rect.top - (boxCollider->size.height - 30) / 2;
			rect.right = rect.left + boxCollider->size.width - 60;
			std::dynamic_pointer_cast<BossArea2>(boss)->SetMoveBound(rect);
		}

		iFrameTime += Time::GetDeltaTime();
	}

}