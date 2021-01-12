#include "d3dpch.h"
#include "Jason.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/CameraBound.h"
#include "Assets/Bullets/Jason/SmallFireBullet.h"
#include "Assets/Characters/PlayerHealth.h"
Jason::Jason(float x, float y)
	: Object2D(x, y)
{
	name = "Jason";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Jason;
}

void Jason::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");

	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;

	KeyFrame keyFrame;
	RECT rect = {0, 0, 0, 0};
	//keyFrame.position = transform->position;
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

	std::shared_ptr<Animation> jasonCrouch = std::make_shared<Animation>("Jason Crouch");
	{
		jasonCrouch->SetAnimationFPS(6);

		rect.left = 3;
		rect.top = 47;
		rect.right = 19;
		rect.bottom = 55;

		keyFrame.rect = rect;
		jasonCrouch->AddKeyFrames(keyFrame);
		animationController->AddAnimation(jasonCrouch);
	}

	std::shared_ptr<Animation> jasonCrawl = std::make_shared<Animation>("Jason Crawl");
	{
		jasonCrawl->SetAnimationFPS(6);

		rect.left = 3;
		rect.top = 47;
		rect.right = 19;
		rect.bottom = 55;
		keyFrame.rect = rect;
		jasonCrawl->AddKeyFrames(keyFrame);

		rect.left = 20;
		rect.top = 47;
		rect.right = 36;
		rect.bottom = 55;
		keyFrame.rect = rect;
		jasonCrawl->AddKeyFrames(keyFrame);

		animationController->AddAnimation(jasonCrawl);
	}

	std::shared_ptr<Animation> jasonDead = std::make_shared<Animation>("Jason Dead");
	{
		jasonDead->SetAnimationFPS(12);
		jasonDead->SetIsLooping(false);
		keyFrame.scale = { 1.0f, 1.0f, 1.0f };
		for (size_t index = 0; index < 3; index++)
		{
			rect.left = 3;
			rect.top = 64;
			rect.right = 19;
			rect.bottom = 80;
			keyFrame.rect = rect;
			jasonDead->AddKeyFrames(keyFrame);

			rect.left = 54;
			rect.top = 64;
			rect.right = 70;
			rect.bottom = 80;
			keyFrame.rect = rect;
			jasonDead->AddKeyFrames(keyFrame);

			rect.left = 37;
			rect.top = 64;
			rect.right = 53;
			rect.bottom = 80;
			keyFrame.rect = rect;
			jasonDead->AddKeyFrames(keyFrame);

			rect.left = 20;
			rect.top = 64;
			rect.right = 36;
			rect.bottom = 80;
			keyFrame.rect = rect;
			jasonDead->AddKeyFrames(keyFrame);
		}
		rect.left = 3;
		rect.top = 64;
		rect.right = 19;
		rect.bottom = 80;
		keyFrame.rect = rect;
		keyFrame.position = {-0.1f, -0.1f, 0.0f};
		jasonDead->AddKeyFrames(keyFrame);
		jasonDead->AddKeyFrames(keyFrame);
		jasonDead->AddKeyFrames(keyFrame);
		jasonDead->AddKeyFrames(keyFrame);

		rect.left = 3;
		rect.top = 81;
		rect.right = 19;
		rect.bottom = 97;
		keyFrame.rect = rect;
		keyFrame.position = { 0.0, 0.0, 0.0f };
		jasonDead->AddKeyFrames(keyFrame);

		rect.left = 20;
		rect.top = 89;
		rect.right = 36;
		rect.bottom = 97;
		keyFrame.rect = rect;
		jasonDead->AddKeyFrames(keyFrame);

		animationController->AddAnimation(jasonDead);
	}

	std::shared_ptr<Animation> jasonClimb = std::make_shared<Animation>("Jason Climb");
	{
		jasonClimb->SetAnimationFPS(6);

		rect.left = 37;
		rect.top = 47;
		rect.right = 54;
		rect.bottom = 63;
		keyFrame.rect = rect;
		jasonClimb->AddKeyFrames(keyFrame);

		rect.left = 54;
		rect.top = 47;
		rect.right = 69;
		rect.bottom = 62;
		keyFrame.rect = rect;
		jasonClimb->AddKeyFrames(keyFrame);

		animationController->AddAnimation(jasonClimb);
	}
	std::shared_ptr<Parameter<float>> runSpeed = std::make_shared<Parameter<float>>("runSpeed");
	{
		animationController->AddFloatParameter(runSpeed);
	}

	std::shared_ptr<Parameter<bool>> isJumping = std::make_shared<Parameter<bool>>("isJumping");
	{
		animationController->AddBoolParameter(isJumping);
	}

	std::shared_ptr<Parameter<bool>> isCrouching = std::make_shared<Parameter<bool>>("isCrouching");
	{
		animationController->AddBoolParameter(isCrouching);
	}

	std::shared_ptr<Parameter<bool>> isDead = std::make_shared<Parameter<bool>>("isDead");
	{
		animationController->AddBoolParameter(isDead);
	}

	std::shared_ptr<Parameter<float>> climbSpeed = std::make_shared<Parameter<float>>("climbSpeed");
	{
		animationController->AddFloatParameter(climbSpeed);
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

	std::shared_ptr<TransitionCondition<bool>> isCrouchingTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isCrouchingTrueBoolCond->SetParameter(isCrouching);
		isCrouchingTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> isCrouchingFalseBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isCrouchingFalseBoolCond->SetParameter(isCrouching);
		isCrouchingFalseBoolCond->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<bool>> isDeadTrueBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		isDeadTrueBoolCond->SetParameter(isDead);
		isDeadTrueBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<float>> climbSpeedGreaterFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		climbSpeedGreaterFloatCond->SetParameter(climbSpeed);
		climbSpeedGreaterFloatCond->SetCondition(Condition::Greater);
		climbSpeedGreaterFloatCond->SetValue(0.01f);
	}

	std::shared_ptr<TransitionCondition<float>> climbSpeedLessFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		climbSpeedLessFloatCond->SetParameter(climbSpeed);
		climbSpeedLessFloatCond->SetCondition(Condition::Less);
		climbSpeedLessFloatCond->SetValue(0.01f);
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

	std::shared_ptr<Transition> idleToCrouchTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonIdle),
		animationController->GetAnimationIndex(jasonCrouch));
	{
		idleToCrouchTrans->AddBoolTransitionCondition(isCrouchingTrueBoolCond);
		animationController->AddTransition(idleToCrouchTrans);
	}

	std::shared_ptr<Transition> crouchToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrouch),
		animationController->GetAnimationIndex(jasonIdle));
	{
		crouchToIdleTrans->AddBoolTransitionCondition(isCrouchingFalseBoolCond);
		animationController->AddTransition(crouchToIdleTrans);
	}

	std::shared_ptr<Transition> crouchToCrawlTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrouch),
		animationController->GetAnimationIndex(jasonCrawl));
	{
		crouchToCrawlTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		animationController->AddTransition(crouchToCrawlTrans);
	}

	std::shared_ptr<Transition> crawlToCrouchTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrawl),
		animationController->GetAnimationIndex(jasonCrouch));
	{
		crawlToCrouchTrans->AddFloatTransitionCondition(runSpeedLessFloatCond);
		animationController->AddTransition(crawlToCrouchTrans);
	}

	std::shared_ptr<Transition> runToCrawlTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonRun),
		animationController->GetAnimationIndex(jasonCrawl));
	{
		runToCrawlTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		runToCrawlTrans->AddBoolTransitionCondition(isCrouchingTrueBoolCond);
		animationController->AddTransition(runToCrawlTrans);
	}

	std::shared_ptr<Transition> crawlToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrawl),
		animationController->GetAnimationIndex(jasonRun));
	{
		crawlToRunTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		crawlToRunTrans->AddBoolTransitionCondition(isCrouchingFalseBoolCond);
		animationController->AddTransition(crawlToRunTrans);
	}



	std::shared_ptr<Transition> idleToDeadTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonIdle),
		animationController->GetAnimationIndex(jasonDead));
	{
		idleToDeadTrans->AddBoolTransitionCondition(isDeadTrueBoolCond);
		animationController->AddTransition(idleToDeadTrans);
	}

	std::shared_ptr<Transition> runToDeadTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonRun),
		animationController->GetAnimationIndex(jasonDead));
	{
		runToDeadTrans->AddBoolTransitionCondition(isDeadTrueBoolCond);
		animationController->AddTransition(runToDeadTrans);
	}

	std::shared_ptr<Transition> jumpToDeadTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonJump),
		animationController->GetAnimationIndex(jasonDead));
	{
		jumpToDeadTrans->AddBoolTransitionCondition(isDeadTrueBoolCond);
		animationController->AddTransition(jumpToDeadTrans);
	}

	std::shared_ptr<Transition> crouchToDeadTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrouch),
		animationController->GetAnimationIndex(jasonDead));
	{
		crouchToDeadTrans->AddBoolTransitionCondition(isDeadTrueBoolCond);
		animationController->AddTransition(crouchToDeadTrans);
	}

	std::shared_ptr<Transition> crawlToDeadTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonCrawl),
		animationController->GetAnimationIndex(jasonDead));
	{
		crawlToDeadTrans->AddBoolTransitionCondition(isDeadTrueBoolCond);
		animationController->AddTransition(crawlToDeadTrans);
	}

	std::shared_ptr<Transition> idleToClimbTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonIdle),
		animationController->GetAnimationIndex(jasonClimb));
	{
		idleToClimbTrans->AddFloatTransitionCondition(climbSpeedGreaterFloatCond);
		animationController->AddTransition(idleToClimbTrans);
	}

	std::shared_ptr<Transition> climbToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonClimb),
		animationController->GetAnimationIndex(jasonIdle));
	{
		climbToIdleTrans->AddFloatTransitionCondition(climbSpeedLessFloatCond);
		animationController->AddTransition(climbToIdleTrans);
	}

	std::shared_ptr<Transition> runToClimbTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonRun),
		animationController->GetAnimationIndex(jasonClimb));
	{
		runToClimbTrans->AddFloatTransitionCondition(climbSpeedGreaterFloatCond);
		runToClimbTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		animationController->AddTransition(runToClimbTrans);
	}

	std::shared_ptr<Transition> climbToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(jasonClimb),
		animationController->GetAnimationIndex(jasonRun));
	{
		climbToRunTrans->AddFloatTransitionCondition(runSpeedGreaterFloatCond);
		climbToRunTrans->AddFloatTransitionCondition(climbSpeedLessFloatCond);
		animationController->AddTransition(climbToRunTrans);
	}
}

void Jason::Start()
{
	runSpeed = 80.0f;
	speedMulti = 0.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	isJumping = false;
	isCrouching = false;
	fallMultiplier = 0.3f;
	readyToClimb = false;
	climbSpeed = 40.0f;
	isClimbing = false;
	verticalMove = 0.0f;
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	rigidbody->gravityScale = 1.0f;
	rigidbody->bounciness = 0.0f;
	rigidbody->mass = 1.0f;
	boxCollider->size = { 8.0f, 16.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { -WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 1.0f };
	state = State::Normal;

	iFrame = false;
	camera = SceneManager::GetActiveScene()->GetActiceCamera();

	timeBeforLoadScreen = 0.0f;
	allowToLoad = true;

	iFrameColors[0] = { 0, 255, 0, 255 };
	iFrameColors[1] = { 255, 51, 0, 255 };
	iFrameColors[2] = { 255, 255, 255, 255 };
	iFrameColors[3] = { 255, 204, 255, 2255 };

	color = iFrameColors[2];
}

void Jason::Update()
{
	if (CharacterController::GetCharacterInControl() == Character::Jason)
	{
		if (state == State::Normal)
		{
			rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
			boxCollider->isTrigger = false;

			if (downCollision != 0)
			{
				if (Input::GetKeyDown(KeyCode_SPACE) && !isCrouching)
				{
					Jump();
				}

				if (Input::GetKeyDown(KeyCode_S) && !isCrouching)
				{
					Crouch(true);
				}

				if (Input::GetKeyDown(KeyCode_W) && isCrouching)
				{
					Crouch(false);
				}

				ControlHorizontalMove(true);

			}
			else
			{
				ControlHorizontalMove(false);
			}

			rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

			if (readyToClimb)
			{
				if (Input::GetKeyDown(KeyCode_W) && !isCrouching)
				{
					state = State::Climbing;
					rigidbody->gravityScale = 0.0f;
					transform->Translate(transform->position.x, transform->position.y + 2.0f, 0.0f);
				}
			}

			if (rigidbody->velocity.y < 0.0f)
			{
				rigidbody->velocity.y += Physic::gravity.y * fallMultiplier * Time::GetFixedDeltaTime();
			}

			if (Input::GetKeyDown(KeyCode_J))
			{
				Shoot();
			}

			MoveCameraAccordingly();
			ApplyCameraBound();
		}
		else if (state == State::CheckPointMove)
	{
		rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();

		camera->MoveCamera(rigidbody->velocity.x * 2.24f, 0.0f, 0.0f);
	}
		else if (state == State::Die)
	{
		if (timeBeforLoadScreen >= 2.5f && allowToLoad);
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
		else if (state == State::Climbing)
		{
			if (!ControlVerticalMove())
			{
				ControlHorizontalMove(true);
				rigidbody->velocity.y = 0.0f;
				rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
			}
			else
			{
				rigidbody->velocity.x = 0.0f;
				rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();
			}

			if (Input::GetKeyDown(KeyCode_J))
			{
				Shoot();
			}
			MoveCameraAccordingly();
			ApplyCameraBound();
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
	}
	else
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		boxCollider->isTrigger = true;
	}
	SetAnimationParameter();
	DoIFrame();
}

void Jason::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Terrain && downCollision != 0)
	{
		isJumping = false;
		readyToClimb = false;
		state = State::Normal;
		rigidbody->gravityScale = 1.0f;
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

	if (object->tag == Tag::Ladder)
	{
		readyToClimb = true;
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

		RECT rect = {0, 0, 0, 0};
		rect.left = (LONG)boxCollider->topLeft.x;
		rect.top = (LONG)(SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y);
		rect.right = (LONG)(rect.left + boxCollider->size.width);
		rect.bottom = (LONG)(rect.top + boxCollider->size.height);

		CameraBound::SetCurrentBound(rect);
	}

	if (object->tag == Tag::Ladder)
	{
		readyToClimb = false;
		state = State::Normal;
		rigidbody->gravityScale = 1.0f;
	}
}

void Jason::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -WINDOW_CAMERA_SCALE_X : WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void Jason::Shoot()
{
	std::shared_ptr<Object2D> bullet = std::make_shared<SmallFireBullet>(transform->position.x, transform->position.y, isFacingRight);
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, bullet->transform->position);
}

void Jason::Jump()
{
	isJumping = true;
	D3DXVECTOR2 force(0.0f, 200.0f);
	rigidbody->AddForce(force);
}

void Jason::Crouch(bool enable, float speedScalar)
{
	isCrouching = enable;
	if (enable)
	{
		boxCollider->size = { 16.0f, 8.0f };
		runSpeed *= speedScalar;
		transform->Translate(transform->position.x, transform->position.y - 4.0f, 0.0f);
	}
	else
	{
		boxCollider->size = { 8.0f, 16.0f };
		runSpeed *= 1.0f / speedScalar;
		transform->Translate(transform->position.x, transform->position.y + 4.0f, 0.0f);
	}
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

void Jason::SetAnimationParameter()
{
	animationController->SetBool("isJumping", isJumping);
	animationController->SetFloat("runSpeed", abs(horizontalMove));
	animationController->SetFloat("climbSpeed", abs(verticalMove));
	animationController->SetBool("isCrouching", isCrouching);
}

void Jason::Die()
{
	boxCollider->isEnable = false;
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
	state = State::Die;
	animationController->SetBool("isDead", true);
}

void Jason::DoIFrame()
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

bool Jason::ControlHorizontalMove(bool onGround)
{
	if (onGround)
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

	if (horizontalMove != 0)
	{
		return true;
	}
	return false;
}

bool Jason::ControlVerticalMove()
{
	if (Input::GetKey(KeyCode_W))
	{
		verticalMove = 1.0f * climbSpeed;
	}
	else if (Input::GetKey(KeyCode_S))
	{
		verticalMove = -1.0f * climbSpeed;
	}
	else
	{
		verticalMove = 0.0f;
	}

	if (verticalMove != 0)
	{
		return true;
	}
	return false;
}

void Jason::TakeDamage(int damage)
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
