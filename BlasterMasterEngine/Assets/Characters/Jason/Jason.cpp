#include "d3dpch.h"
#include "Jason.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/CameraBound.h"

Jason::Jason(float x, float y)
	: Object2D(x, y)
{
	name = "Jason ";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Jason;
}

void Jason::CreateResources()
{
	spriteRenderer->sprite = DeviceResources::LoadTexture(SOPHIA_JASON_TEXTURE_PATH, 0);

	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;

	KeyFrame keyFrame;
	RECT rect;
	keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };
	std::shared_ptr<Animation> jasonIdle = std::make_shared<Animation>("Jason Idle");
	{
		jasonIdle->SetAnimationFPS(6);

		rect.left = 3;
		rect.top = 3 + 3 * (yOffset + spriteHeight);
		rect.right = rect.left + spriteWidth + 1;
		rect.bottom = rect.top + 15 + 1;
		
		keyFrame.rect = rect;
		jasonIdle->AddKeyFrames(keyFrame);
		animationController->AddAnimation(jasonIdle);
		animationController->SetDefaultAnimation(jasonIdle);
	}

	std::shared_ptr<Animation> jasonRun = std::make_shared<Animation>("Jason Run");
	{
		jasonRun->SetAnimationFPS(12);
		for (size_t index = 1; index < 4; index++)
		{
			rect.left = 3 + (int)index * (xOffset + spriteWidth);
			rect.top = 3 + 3 * (yOffset + spriteHeight);
			rect.right = rect.left + spriteWidth + 1;
			rect.bottom = rect.top + 15 + 1;
			keyFrame.rect = rect;
			jasonRun->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(jasonRun);
	}

	std::shared_ptr<Animation> jasonJump = std::make_shared<Animation>("Jason Jump");
	{
		jasonJump->SetAnimationFPS(12);

		rect.left = 3 + (xOffset + spriteWidth);
		rect.top = 3 + 3 * (yOffset + spriteHeight);
		rect.right = rect.left + spriteWidth + 1;
		rect.bottom = rect.top + 15 + 1;
		keyFrame.rect = rect;
		jasonJump->AddKeyFrames(keyFrame);

		animationController->AddAnimation(jasonJump);
	}

	std::shared_ptr<Parameter<float>> runSpeed = std::make_shared<Parameter<float>>("runSpeed");
	{
		animationController->AddFloatParameter(runSpeed);
	}

	std::shared_ptr<Parameter<bool>> isJumping = std::make_shared<Parameter<bool>>("isJumping");
	{
		animationController->AddBoolParameter(isJumping);
	}

	std::shared_ptr<TransitionCondition<float>> runSpeedGreaterFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		runSpeedGreaterFloatCond->SetParameter(runSpeed);
		runSpeedGreaterFloatCond->SetCondition(Condition::Greater);
		runSpeedGreaterFloatCond->SetValue(0.01f);
	}

	std::shared_ptr<TransitionCondition<float>> runSpeedLessFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		runSpeedLessFloatCond->SetParameter(runSpeed);
		runSpeedLessFloatCond->SetCondition(Condition::Less);
		runSpeedLessFloatCond->SetValue(0.01f);
	}

	std::shared_ptr<TransitionCondition<bool>> isJumpingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isJumpingTrueBoolCond->SetParameter(isJumping);
		isJumpingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isJumpingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isJumpingFalseBoolCond->SetParameter(isJumping);
		isJumpingFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<Transition> idleToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonIdle),
		animationController->GetAnimationIndex(jasonRun));
	{
		idleToRunTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		animationController->AddTransition(idleToRunTrans);
	}

	std::shared_ptr<Transition> runToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonRun),
		animationController->GetAnimationIndex(jasonIdle));
	{
		runToIdleTrans->AddFloatTransitionCondition(runSpeedLessFloatCond);
		animationController->AddTransition(runToIdleTrans);
	}

	std::shared_ptr<Transition> idleToJumpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonIdle),
		animationController->GetAnimationIndex(jasonJump));
	{
		idleToJumpTrans->AddBoolTransitionCondition(isJumpingTrueBoolCond);
		animationController->AddTransition(idleToJumpTrans);
	}

	std::shared_ptr<Transition> jumpToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonJump),
		animationController->GetAnimationIndex(jasonIdle));
	{
		jumpToIdleTrans->AddBoolTransitionCondition(isJumpingFalseBoolCond);
		jumpToIdleTrans->AddFloatTransitionCondition(runSpeedLessFloatCond);
		animationController->AddTransition(jumpToIdleTrans);
	}

	std::shared_ptr<Transition> runToJumpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonRun),
		animationController->GetAnimationIndex(jasonJump));
	{
		runToJumpTrans->AddBoolTransitionCondition(isJumpingTrueBoolCond);
		runToJumpTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		animationController->AddTransition(runToJumpTrans);
	}

	std::shared_ptr<Transition> jumpToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonJump),
		animationController->GetAnimationIndex(jasonRun));
	{
		jumpToRunTrans->AddBoolTransitionCondition(isJumpingFalseBoolCond);
		jumpToRunTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		animationController->AddTransition(jumpToRunTrans);
	}
}

void Jason::Start()
{
	runSpeed = 70.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	isJumping = false;
	fallMultiplier = 0.5f;
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	rigidbody->gravityScale = 1.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 8.0f, 17.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { -WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
	state = State::Normal;
	hitPoint = 8;
	iFrame = false;
	camera = SceneManager::GetActiveScene()->GetActiceCamera();

	iFrameColors[0] = { 0, 255, 0, 255 };
	iFrameColors[1] = { 255, 51, 0, 255 };
	iFrameColors[2] = { 255, 255, 255, 255 };
	iFrameColors[3] = { 255, 204, 255, 2255 };

	color = iFrameColors[2];
}

void Jason::Update()
{
	if (state == State::Normal)
	{
		if (CharacterController::GetCharacterInControl() == Character::Jason)
		{
			rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
			boxCollider->isTrigger = false;

			static float speedMulti = 0.0f;

			if (downCollision != 0)
			{
				if (Input::GetKey(KeyCode_D))
				{
					horizontalMove = 1.0f * runSpeed * speedMulti;
					speedMulti += 0.2f;

				}
				else if (Input::GetKey(KeyCode_A))
				{
					horizontalMove = -1.0f * runSpeed * speedMulti;
					speedMulti += 0.2f;
				}
				else
				{
					horizontalMove = (isFacingRight ? 1.0f : -1.0f) * runSpeed * speedMulti;
					speedMulti -= 0.2f;
				}

				if (Input::GetKeyDown(KeyCode_SPACE))
				{
					Jump();
				}

				if (speedMulti > 1.0f)
				{
					speedMulti = 1.0f;
				}
				else if (speedMulti < 0.0f)
				{
					speedMulti = 0.0f;
				}
			}
			else
			{
				speedMulti = 0.4f;
				if (Input::GetKey(KeyCode_D) && horizontalMove <= 0)
				{
					horizontalMove = 1.0f * runSpeed * speedMulti;
				}
				else if (Input::GetKey(KeyCode_A) && horizontalMove >= 0)
				{
					horizontalMove = -1.0f * runSpeed * speedMulti;
				}
			}

			rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

			if (Input::GetKeyDown(KeyCode_J))
			{
				Shoot();
			}

			if (rigidbody->velocity.y < 0.0f)
			{
				rigidbody->velocity.y += Physic::gravity.y * fallMultiplier * Time::GetFixedDeltaTime();
			}

			if (horizontalMove > 0 && !isFacingRight)
			{
				speedMulti = 0.0f;
				Flip();
			}
			else if (horizontalMove < 0 && isFacingRight)
			{
				speedMulti = 0.0f;
				Flip();
			}

			MoveCameraAccordingly();
			ApplyCameraBound();
		}
		else if (downCollision != 0)
		{
			rigidbody->bodyType = Rigidbody::BodyType::Static;
			boxCollider->isTrigger = true;
		}
	}
	else if (state == State::CheckPointMove)
	{
		rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();

		camera->MoveCamera(rigidbody->velocity.x * 2.24f, 0.0f, 0.0f);
	}
	else if (state == State::Die)
	{
		static float timeBeforLoadScreen = 0.0f;

		if (timeBeforLoadScreen >= 1.5f)
		{
			SceneManager::LoadScene("Loading Screen");
		}
		timeBeforLoadScreen += Time::GetDeltaTime();
	}
	SetAnimationParameter();
	DoIFrame();

	LOG_INFO("{0}", hitPoint);
}

void Jason::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Terrain)
	{
		isJumping = false;
	}

	if (object->tag == Tag::CheckPoint)
	{
		state = State::CheckPointMove;

	}
}

void Jason::OnCollisionStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player)
	{
		if (Input::GetKeyDown(KeyCode_V) && abs(transform->position.x - object->transform->position.x) <= 10.0f)
		{
			CharacterController::SetCharacterInControl(Character::Sophia);
			SceneManager::DestroyObject(shared_from_this());
		}
	}
}

void Jason::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void Jason::OnCollisionExit(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::CheckPoint)
	{
		state = State::Normal;

		RECT rect;
		rect.left = boxCollider->topLeft.x;
		rect.top = SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y;
		rect.right = rect.left + boxCollider->size.width;
		rect.bottom = rect.top + boxCollider->size.height;

		CameraBound::SetCurrentBound(rect);
	}
}

void Jason::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void Jason::Jump()
{
	isJumping = true;
	D3DXVECTOR2 force(0.0f, 850.0f);
	rigidbody->AddForce(force);
}

void Jason::MoveCameraAccordingly()
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

void Jason::ApplyCameraBound()
{
	if (camera->GetPosition().x < CameraBound::GetCurrentBound().left)
	{
		camera->SetPosition(CameraBound::GetCurrentBound().left, camera->GetPosition().y, 0.0f);
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

void Jason::SetAnimationParameter()
{
	animationController->SetBool("isJumping", isJumping);
	animationController->SetFloat("runSpeed", abs(horizontalMove));
}

void Jason::Die()
{
	boxCollider->isEnable = false;
	state = State::Die;
}

void Jason::DoIFrame()
{
	if (iFrame)
	{
		static float iFrameTime = 0.0f;
		static int iFrameColorIndex = 0;

		if (iFrameTime > 0.45f)
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

void Jason::TakeDamage(int damage)
{
	if (!iFrame)
	{
		hitPoint -= damage;
		iFrame = true;

		if (hitPoint <= 0)
		{
			Die();
		}
	}
}
