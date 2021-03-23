#include "d3dpch.h"
#include "OverworldJason.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/CameraBound.h"
#include "Assets/Particles/PlayerDeadExplosion.h"
#include "Assets/Bullets/Sophia/NormalFireBullet.h"
#include "Assets/Bullets/Jason/IndoorBullet.h"
#include "Assets/Others/Checkpoint/IndoorVerticalCheckpoint.h"
#include "Assets/Characters/PlayerHealth.h"

int OverworldJason::id = 0;

OverworldJason::OverworldJason(float x, float y)
	: Object2D(x, y)
{
	name = "OverworldJason";
	tag = Tag::Player;
	// giu nguyen
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();

	//end
}

void OverworldJason::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	KeyFrame keyFrame;
	RECT rect = { 0, 0, 0, 0 };
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	int verticalMoveSpriteWidth = 20;
	int verticalMoveSpriteHeight = 31;

	int horizontalMoveSpriteWidth = 24;
	int horizontalMoveSpriteHeight = 32;

	//int xOffset = 2;
	//int yOffset = 2;
	// keyFrame voi rect

	//chinh ten animation
#pragma region animation
	std::shared_ptr<Animation> overworldJasonDownIdle = std::make_shared<Animation>("Jason Down Idle");
	{
		overworldJasonDownIdle->SetAnimationFPS(6);

		rect.left = 235;
		rect.top = 3;
		rect.right = rect.left + verticalMoveSpriteWidth;
		rect.bottom = rect.top + verticalMoveSpriteHeight;

		keyFrame.rect = rect;
		overworldJasonDownIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(overworldJasonDownIdle);
	}

	std::shared_ptr<Animation> overworldJasonUpIdle = std::make_shared<Animation>("Jason Up Idle");
	{
		overworldJasonUpIdle->SetAnimationFPS(6);

		rect.left = 235;
		rect.top = 36;
		rect.right = rect.left + verticalMoveSpriteWidth;
		rect.bottom = rect.top + verticalMoveSpriteHeight;

		keyFrame.rect = rect;
		overworldJasonUpIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(overworldJasonUpIdle);
		animationController->SetDefaultAnimation(overworldJasonUpIdle);
	}

	std::shared_ptr<Animation> overworldJasonMoveUp = std::make_shared<Animation>("Jason Moving Up");
	{
		overworldJasonMoveUp->SetAnimationFPS(12);

		for (size_t index = 0; index < 2; index++)
		{
			rect.left = 210 + (int)index * 25;
			rect.top = 36;
			rect.right = rect.left + verticalMoveSpriteWidth;
			rect.bottom = rect.top + verticalMoveSpriteHeight;
			keyFrame.rect = rect;
			overworldJasonMoveUp->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(overworldJasonMoveUp);
	}

	std::shared_ptr<Animation> overworldJasonMoveDown = std::make_shared<Animation>("Jason Moving Down");
	{
		overworldJasonMoveDown->SetAnimationFPS(12);

		for (size_t index = 0; index < 2; index++)
		{
			rect.left = 210 + (int)index * 25;
			rect.top = 3;
			rect.right = rect.left + verticalMoveSpriteWidth;
			rect.bottom = rect.top + verticalMoveSpriteHeight;
			keyFrame.rect = rect;
			overworldJasonMoveDown->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(overworldJasonMoveDown);
	}

	std::shared_ptr<Animation> overworldJasonHorizontalIdle = std::make_shared<Animation>("Jason Horizontal Idle");
	{
		overworldJasonHorizontalIdle->SetAnimationFPS(6);

		rect.left = 233;
		rect.top = 69;
		rect.right = rect.left + horizontalMoveSpriteWidth;
		rect.bottom = rect.top + horizontalMoveSpriteHeight;

		keyFrame.rect = rect;
		overworldJasonHorizontalIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(overworldJasonHorizontalIdle);
	}

	std::shared_ptr<Animation> overworldJasonHorizontalMove = std::make_shared<Animation>("Jason Horizontal Move");
	{
		overworldJasonHorizontalMove->SetAnimationFPS(12);

		for (size_t index = 0; index < 2; index++)
		{
			rect.left = 208 + (int)index * 25;
			rect.top = 69;
			rect.right = rect.left + horizontalMoveSpriteWidth;
			rect.bottom = rect.top + horizontalMoveSpriteHeight;
			keyFrame.rect = rect;
			overworldJasonHorizontalMove->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(overworldJasonHorizontalMove);
	}
#pragma endregion

#pragma region condParameter

	std::shared_ptr<Parameter<float>> verticalSpeed = std::make_shared<Parameter<float>>("verticalSpeed");
	{
		animationController->AddFloatParameter(verticalSpeed);
	}

	std::shared_ptr<Parameter<float>> absVerticalSpeed = std::make_shared<Parameter<float>>("absVerticalSpeed");
	{
		animationController->AddFloatParameter(absVerticalSpeed);
	}

	std::shared_ptr<TransitionCondition<float>> verticalSpeedGreaterThanZero = std::make_shared<TransitionCondition<float>>();
	{
		verticalSpeedGreaterThanZero->SetParameter(verticalSpeed);
		verticalSpeedGreaterThanZero->SetCondition(Condition::Greater);
		verticalSpeedGreaterThanZero->SetValue(0.0f);
	}

	std::shared_ptr<TransitionCondition<float>> verticalSpeedLessThanZero = std::make_shared<TransitionCondition<float>>();
	{
		verticalSpeedLessThanZero->SetParameter(verticalSpeed);
		verticalSpeedLessThanZero->SetCondition(Condition::Less);
		verticalSpeedLessThanZero->SetValue(0.0f);
	}

	std::shared_ptr<Parameter<float>> absHorizontalSpeed = std::make_shared<Parameter<float>>("absHorizontalSpeed");
	{
		animationController->AddFloatParameter(absHorizontalSpeed);
	}

	std::shared_ptr<TransitionCondition<float>> abshorizontalSpeedGreaterThanZero = std::make_shared<TransitionCondition<float>>();
	{
		abshorizontalSpeedGreaterThanZero->SetParameter(absHorizontalSpeed);
		abshorizontalSpeedGreaterThanZero->SetCondition(Condition::Greater);
		abshorizontalSpeedGreaterThanZero->SetValue(0.01f);
	}

	std::shared_ptr<TransitionCondition<float>> abshorizontalSpeedEqualZero = std::make_shared<TransitionCondition<float>>();
	{
		abshorizontalSpeedEqualZero->SetParameter(absHorizontalSpeed);
		abshorizontalSpeedEqualZero->SetCondition(Condition::Less);
		abshorizontalSpeedEqualZero->SetValue(0.01f);
	}

	std::shared_ptr<TransitionCondition<float>> absVeritcalSpeedEqualZero = std::make_shared<TransitionCondition<float>>();
	{
		absVeritcalSpeedEqualZero->SetParameter(absVerticalSpeed);
		absVeritcalSpeedEqualZero->SetCondition(Condition::Less);
		absVeritcalSpeedEqualZero->SetValue(0.001f);
	}

	std::shared_ptr<Parameter<bool>> isMoving = std::make_shared<Parameter<bool>>("isMoving");
	{
		animationController->AddBoolParameter(isMoving);
	}

	std::shared_ptr<TransitionCondition<bool>> isMovingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isMovingTrueBoolCond->SetParameter(isMoving);
		isMovingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isMovingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isMovingFalseBoolCond->SetParameter(isMoving);
		isMovingFalseBoolCond->SetValue(false);
	}
#pragma endregion

#pragma region cond

	//dung tren xong chay len
	std::shared_ptr<Transition> upIdleToMoveUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonUpIdle),
		animationController->GetAnimationIndex(overworldJasonMoveUp));
	{
		upIdleToMoveUpTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		upIdleToMoveUpTrans->AddFloatTransitionCondition(verticalSpeedGreaterThanZero);
		animationController->AddTransition(upIdleToMoveUpTrans);
	}
	//dung duoi xong chay len
	std::shared_ptr<Transition> downIdleToMoveUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonDownIdle),
		animationController->GetAnimationIndex(overworldJasonMoveUp));
	{
		downIdleToMoveUpTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		downIdleToMoveUpTrans->AddFloatTransitionCondition(verticalSpeedGreaterThanZero);
		animationController->AddTransition(downIdleToMoveUpTrans);
	}
	//chay len xong dung yen
	std::shared_ptr<Transition> moveUpToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonMoveUp),
		animationController->GetAnimationIndex(overworldJasonUpIdle));
	{
		moveUpToIdleTrans->AddBoolTransitionCondition(isMovingFalseBoolCond);
		animationController->AddTransition(moveUpToIdleTrans);
	}
	//dung duoi xong chay xuong
	std::shared_ptr<Transition> downIdleToMoveDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonDownIdle),
		animationController->GetAnimationIndex(overworldJasonMoveDown));
	{
		downIdleToMoveDownTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		downIdleToMoveDownTrans->AddFloatTransitionCondition(verticalSpeedLessThanZero);
		animationController->AddTransition(downIdleToMoveDownTrans);
	}
	//dung tren xong chay xuong
	std::shared_ptr<Transition> upIdleToMoveDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonUpIdle),
		animationController->GetAnimationIndex(overworldJasonMoveDown));
	{
		upIdleToMoveDownTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		upIdleToMoveDownTrans->AddFloatTransitionCondition(verticalSpeedLessThanZero);
		animationController->AddTransition(upIdleToMoveDownTrans);
	}
	//chay xuong xong dung yen
	std::shared_ptr<Transition> moveDownToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonMoveDown),
		animationController->GetAnimationIndex(overworldJasonDownIdle));
	{
		moveDownToIdleTrans->AddBoolTransitionCondition(isMovingFalseBoolCond);
		animationController->AddTransition(moveDownToIdleTrans);
	}
	//dung tren xong chay ngang
	std::shared_ptr<Transition> upIdleToHorizontalMoveTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonUpIdle),
		animationController->GetAnimationIndex(overworldJasonHorizontalMove));
	{
		upIdleToHorizontalMoveTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		upIdleToHorizontalMoveTrans->AddFloatTransitionCondition(abshorizontalSpeedGreaterThanZero);
		animationController->AddTransition(upIdleToHorizontalMoveTrans);
	}
	//dung duoi xong chay ngang
	std::shared_ptr<Transition> downIdleToHorizontalMoveTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonDownIdle),
		animationController->GetAnimationIndex(overworldJasonHorizontalMove));
	{
		downIdleToHorizontalMoveTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		downIdleToHorizontalMoveTrans->AddFloatTransitionCondition(abshorizontalSpeedGreaterThanZero);
		animationController->AddTransition(downIdleToHorizontalMoveTrans);
	}
	//dung ngang xong chay len
	std::shared_ptr<Transition> horizontalIdleToMoveUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalIdle),
		animationController->GetAnimationIndex(overworldJasonMoveUp));
	{
		horizontalIdleToMoveUpTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		horizontalIdleToMoveUpTrans->AddFloatTransitionCondition(verticalSpeedGreaterThanZero);
		animationController->AddTransition(horizontalIdleToMoveUpTrans);
	}
	//dung ngang xong chay xuong
	std::shared_ptr<Transition> horizontalIdleToMoveDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalIdle),
		animationController->GetAnimationIndex(overworldJasonMoveDown));
	{
		horizontalIdleToMoveDownTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		horizontalIdleToMoveDownTrans->AddFloatTransitionCondition(verticalSpeedLessThanZero);
		animationController->AddTransition(horizontalIdleToMoveDownTrans);
	}
	//chay ngang xong dung yen
	std::shared_ptr<Transition> horizontalMoveToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalMove),
		animationController->GetAnimationIndex(overworldJasonHorizontalIdle));
	{
		horizontalMoveToIdleTrans->AddBoolTransitionCondition(isMovingFalseBoolCond);
		animationController->AddTransition(horizontalMoveToIdleTrans);
	}
	//dung ngang xong chay ngang
	std::shared_ptr<Transition> horizontalIdleToHorizontalMoveTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalIdle),
		animationController->GetAnimationIndex(overworldJasonHorizontalMove));
	{
		horizontalIdleToHorizontalMoveTrans->AddBoolTransitionCondition(isMovingTrueBoolCond);
		horizontalIdleToHorizontalMoveTrans->AddFloatTransitionCondition(abshorizontalSpeedGreaterThanZero);
		animationController->AddTransition(horizontalIdleToHorizontalMoveTrans);
	}
	//chay len xong chay ngang
	std::shared_ptr<Transition> moveUpToHorizontalMoveTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonMoveUp),
		animationController->GetAnimationIndex(overworldJasonHorizontalMove));
	{
		moveUpToHorizontalMoveTrans->AddFloatTransitionCondition(absVeritcalSpeedEqualZero);
		animationController->AddTransition(moveUpToHorizontalMoveTrans);
	}
	//chay ngang xong chay len
	std::shared_ptr<Transition> horizontalMoveToMoveUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalMove),
		animationController->GetAnimationIndex(overworldJasonMoveUp));
	{
		horizontalMoveToMoveUpTrans->AddFloatTransitionCondition(abshorizontalSpeedEqualZero);
		horizontalMoveToMoveUpTrans->AddFloatTransitionCondition(verticalSpeedGreaterThanZero);
		animationController->AddTransition(horizontalMoveToMoveUpTrans);
	}
	//chay xuong xong chay ngang
	std::shared_ptr<Transition> moveDownToHorizontalMoveTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonMoveDown),
		animationController->GetAnimationIndex(overworldJasonHorizontalMove));
	{
		moveDownToHorizontalMoveTrans->AddFloatTransitionCondition(absVeritcalSpeedEqualZero);
		animationController->AddTransition(moveDownToHorizontalMoveTrans);
	}
	//chay ngang xong chay xuong
	std::shared_ptr<Transition> horizontalMoveToMoveDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(overworldJasonHorizontalMove),
		animationController->GetAnimationIndex(overworldJasonMoveDown));
	{
		horizontalMoveToMoveDownTrans->AddFloatTransitionCondition(abshorizontalSpeedEqualZero);
		horizontalMoveToMoveDownTrans->AddFloatTransitionCondition(verticalSpeedLessThanZero);
		animationController->AddTransition(horizontalMoveToMoveDownTrans);
	}
#pragma endregion

}

void OverworldJason::Start()
{
	runSpeed = 80.0f;
	timeBeforLoadScreen = 0.0f;
	isFacingRight = true;
	allowToLoad = true;

	isMoving = false;
	isTouching = true;
	direction = Direction::UP;
	//trang thai nhan vat
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 20.0f, 20.0f };
	boxCollider->offset = { 0.0f, -8.0f };
	//is trigger dung lam gi ?
	boxCollider->isTrigger = false;
	camera = SceneManager::GetActiveScene()->GetActiceCamera();
	state = State::Normal;
	hitPoint = 8;
	iFrame = false;
	transform->scale = { -3.0f, 3.0f, 3.0f };
	rigidbody->gravityScale = 0.0f;

	if (id == 0)
	{
		transform->position.x = 1400.0f;
		transform->position.y = SceneManager::GetActiveScene()->GetMapSize().height - 1190.0f;

	}
	else
	{
		transform->position.x = 119.0f;
		transform->position.y = SceneManager::GetActiveScene()->GetMapSize().height - 1950.0f;

	}

	boxCollider->topLeft = { (transform->position.x - boxCollider->size.width / 2.0f) + boxCollider->offset.x, (transform->position.y + boxCollider->size.height / 2.0f) + boxCollider->offset.y };
	RECT rect;
	rect.left = boxCollider->topLeft.x;
	rect.top = SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y;
	rect.right = rect.left + boxCollider->size.width;
	rect.bottom = rect.top + boxCollider->size.height;

	CameraBound::SetCurrentBound(rect);

	iFrameColors[0] = { 0, 255, 0, 255 };
	iFrameColors[1] = { 255, 51, 0, 255 };
	iFrameColors[2] = { 255, 255, 255, 255 };
	iFrameColors[3] = { 255, 204, 255, 2255 };

	color = iFrameColors[2];

	

}

void OverworldJason::Update()
{
	//LOG_INFO("{0}", animationController->GetCurrentAnimation()->GetName());

	if (state == State::Normal)
	{
		if (Input::GetKey(KeyCode_D))
		{
			horizontalMove = 1.0f * runSpeed;
		}
		else if (Input::GetKey(KeyCode_A))
		{
			horizontalMove = -1.0f * runSpeed;
		}
		else
		{
			horizontalMove = 0;
		}
		if (Input::GetKey(KeyCode_W))
		{
			verticalMove = 1.0f * runSpeed;
			isFacingUp = true;
		}
		else if (Input::GetKey(KeyCode_S) && (downCollision == 0))
		{
			verticalMove = -1.0f * runSpeed;
			isFacingUp = false;
		}
		else
		{
			verticalMove = 0;
		}

		if ((verticalMove == 0) && (horizontalMove == 0))
		{
			isMoving = false;
		}
		else
		{
			isMoving = true;
		}

		if (Input::GetKeyDown(KeyCode_J))
		{
			Shoot();
		}

		if (Input::GetKeyDown(KeyCode_K))
		{
			TakeDamage(1);
		}

		rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

		rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();

		if (horizontalMove > 0)
		{
			if (isFacingRight == false)
			{
				Flip();
			}
		}
		else if (horizontalMove < 0)
		{
			if (isFacingRight == true)
			{
				Flip();
			}
		}

		//LOG_INFO("{0}", hitPoint);
		MoveCameraAccordingly();
		ApplyCameraBound();
	}
	else if (state == State::CheckPointMove)
	{
		if (!isVerticalCheckPoint)
		{
			horizontalMove = (isFacingRight ? 1.0f : -1.0f);
			verticalMove = 0.0f;
			rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();
			camera->MoveCamera((isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime() * 3.0f, 0.0f, 0.0f);
		}
		else
		{
			verticalMove = (isFacingUp ? 1.0f : -1.0f);
			horizontalMove = 0.0f;
			rigidbody->velocity.y = (isFacingUp ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();
			camera->MoveCamera(0.0f, rigidbody->velocity.y * 1.8f, 0.0f);
		}
		isMoving = true;
	}
	else if (state == State::Die)
	{
		isMoving = false;
		rigidbody->bodyType = Rigidbody::BodyType::Static;

		if (timeBeforLoadScreen >= 1.5f && allowToLoad)
		{
			PlayerHealth::SetPlayerLife(PlayerHealth::GetPlayerLife() - 1);
			if (PlayerHealth::GetPlayerLife() < 0)
			{
				SceneManager::ReloadScene("Game Over Screen");
			}
			else
			{
				SceneManager::ReloadScene("Loading Screen");
			}
			timeBeforLoadScreen = 0.0f;
			allowToLoad = false;
		}
		timeBeforLoadScreen += Time::GetDeltaTime();
	}
	SetAnimationParameter();
	DoIFrame();
}

void OverworldJason::DoIFrame()
{
	if (iFrame)
	{
		static float iFrameTime = 0.0f;
		static int iFrameColorIndex = 0;

		if (iFrameTime >= 0.45f)
		{
			iFrameTime = 0.0f;
			iFrame = false;
			iFrameColorIndex = 0;
			color = iFrameColors[2];
		}
		else
		{
			color = iFrameColors[iFrameColorIndex];
			++iFrameColorIndex;
			if (iFrameColorIndex > iFrameColors.size() - 1)
			{
				iFrameColorIndex = 0;
			}
			iFrameTime += Time::GetDeltaTime();
		}
	}
}


void OverworldJason::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Terrain)
	{
	}

	if (object->tag == Tag::CheckPoint)
	{
		state = State::CheckPointMove;
		std::shared_ptr<IndoorVerticalCheckpoint> verticalCheckpoint = std::dynamic_pointer_cast<IndoorVerticalCheckpoint>(object);
		if (verticalCheckpoint != NULL)
		{
			isVerticalCheckPoint = true;
			this->transform->position.x = object->transform->position.x;
			
			/*std::string s = "vi tri player x: " + std::to_string(this->transform->position.x) + " ,y: " + std::to_string(this->transform->position.y) + ". Vi tri checkpoint x: " + std::to_string(object->transform->position.x) + " ,y: " + std::to_string(object->transform->position.y);
			LOG_INFO(s);*/
		}
		else
		{
			isVerticalCheckPoint = false;
			this->transform->position.y = object->transform->position.y + 8;
		}
	}
}

void OverworldJason::OnCollisionStay(std::shared_ptr<Object2D> object)
{
	//LOG_INFO("damn bruh");
	if (object->tag == Tag::CheckPoint)
	{
		std::shared_ptr<IndoorVerticalCheckpoint> verticalCheckpoint = std::dynamic_pointer_cast<IndoorVerticalCheckpoint>(object);
		if (verticalCheckpoint != NULL)
		{
			this->transform->position.x = object->transform->position.x;
		}
		else
		{
			this->transform->position.y = object->transform->position.y + 8;
		}
	}
	
	if (object->tag == Tag::Gate)
	{
			SceneManager::LoadScene("Area2");
	}
}

void OverworldJason::OnCollisionExit(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::CheckPoint)
	{
		state = State::Normal;

		RECT rect = { 0, 0, 0, 0 };
		rect.left = (LONG)boxCollider->topLeft.x;
		rect.top = (LONG)(SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y);
		rect.right = (LONG)(rect.left + boxCollider->size.width);
		rect.bottom = (LONG)(rect.top + boxCollider->size.height);
		CameraBound::SetCurrentBound(rect);
	}
}

void OverworldJason::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}

void OverworldJason::Die()
{
	std::shared_ptr<Object2D> playerDeadExplosion = std::make_shared<PlayerDeadExplosion>(transform->position.x, transform->position.y);
	playerDeadExplosion->CreateResources();
	SceneManager::Instantiate(playerDeadExplosion, playerDeadExplosion->transform->position);
	for (std::shared_ptr<Object2D> child : childObjects)
	{
		child->enable = false;
	}
	boxCollider->isEnable = false;

	state = State::Die;
}

void OverworldJason::SetAnimationParameter()
{

	animationController->SetFloat("verticalSpeed", verticalMove);

	animationController->SetBool("isMoving", isMoving);

	animationController->SetFloat("absHorizontalSpeed", abs(horizontalMove));

	animationController->SetFloat("absVerticalSpeed", abs(verticalMove));
}

void OverworldJason::ApplyCameraBound()
{
	if (camera->GetPosition().x < CameraBound::GetCurrentBound().left)
	{
		camera->SetPosition((float)CameraBound::GetCurrentBound().left, camera->GetPosition().y, 0.0f);
	}
	else if (camera->GetPosition().x > CameraBound::GetCurrentBound().right - camera->GetSize().width)
	{
		camera->SetPosition(CameraBound::GetCurrentBound().right - camera->GetSize().width, camera->GetPosition().y, 0.0f);
	}

	float mapHeight = SceneManager::GetActiveScene()->GetMapSize().height;
	if (mapHeight - camera->GetPosition().y < CameraBound::GetCurrentBound().top)
	{
		camera->SetPosition(camera->GetPosition().x, mapHeight - CameraBound::GetCurrentBound().top, 0.0f);
	}
	else if (mapHeight - camera->GetPosition().y > CameraBound::GetCurrentBound().bottom - camera->GetSize().height)
	{
		camera->SetPosition(camera->GetPosition().x, mapHeight - (CameraBound::GetCurrentBound().bottom - camera->GetSize().height), 0.0f);
	}
}

void OverworldJason::MoveCameraAccordingly()
{
	float distanceXBetweenCamPlay = transform->position.x - camera->GetPosition().x;

	if (distanceXBetweenCamPlay > (camera->GetSize().width / 2) + 30.0f)
	{
		camera->SetPosition(transform->position.x - (camera->GetSize().width / 2) - 30.0f, camera->GetPosition().y, 0.0f);
	}
	else if (distanceXBetweenCamPlay < (camera->GetSize().width / 2) - 30.0f)
	{
		camera->SetPosition(transform->position.x - (camera->GetSize().width / 2) + 30.0f, camera->GetPosition().y, 0.0f);
	}

	RECT currentBound = CameraBound::GetCurrentBound();
	if (currentBound.bottom - currentBound.top < 300.0f)
		return;

	float distanceYBetweenCamPlay = camera->GetPosition().y - transform->position.y;
	if (distanceYBetweenCamPlay < (camera->GetSize().height / 2) - 30.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + (camera->GetSize().height / 2) - 30.0f, 0.0f);
	}
	else if (distanceYBetweenCamPlay > (camera->GetSize().height / 2) + 30.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + (camera->GetSize().height / 2) + 30.0f, 0.0f);
	}
}

void OverworldJason::Shoot()
{
	SetDirection();
	std::shared_ptr<Object2D> bullet;
	D3DXVECTOR3 location;
	if (direction == Direction::UP)
	{
		location = { transform->position.x, transform->position.y, 0.0f };
		bullet = std::make_shared<IndoorBullet>(Direction::UP, location.x, location.y);
	}
	if (direction == Direction::DOWN)
	{
		location = { transform->position.x, transform->position.y, 0.0f };
		bullet = std::make_shared<IndoorBullet>(Direction::DOWN, location.x, location.y);
	}
	if (direction == Direction::RIGHT)
	{
		location = { transform->position.x, transform->position.y, 0.0f };
		bullet = std::make_shared<IndoorBullet>(Direction::RIGHT, location.x, location.y);
	}
	if (direction == Direction::LEFT)
	{
		location = { transform->position.x, transform->position.y, 0.0f };
		bullet = std::make_shared<IndoorBullet>(Direction::LEFT, location.x, location.y);
	}
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, location);
}

void OverworldJason::SetDirection()
{
	if ((animationController->GetCurrentAnimation()->GetName() == "Jason Down Idle") || (animationController->GetCurrentAnimation()->GetName() == "Jason Moving Down"))
		direction = Direction::DOWN;
	if ((animationController->GetCurrentAnimation()->GetName() == "Jason Up Idle") || (animationController->GetCurrentAnimation()->GetName() == "Jason Moving Up"))
		direction = Direction::UP;
	if ((animationController->GetCurrentAnimation()->GetName() == "Jason Horizontal Idle") || (animationController->GetCurrentAnimation()->GetName() == "Jason Horizontal Move"))
	{
		if (isFacingRight)
			direction = Direction::RIGHT;
		else direction = Direction::LEFT;
	}
}

void OverworldJason::TakeDamage(int damage)
{
	if (!iFrame)
	{
		int health = PlayerHealth::GetJasonHealth();
		health -= damage;
		PlayerHealth::SetJasonHealth(health);
		iFrame = true;

		if (health <= 0)
		{
			PlayerHealth::SetJasonHealth(0);
			Die();
		}
	}
}