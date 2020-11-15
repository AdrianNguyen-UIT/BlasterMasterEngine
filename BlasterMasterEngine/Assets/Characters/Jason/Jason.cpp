#include "d3dpch.h"
#include "Jason.h"
#include "Core/SceneManager/SceneManager.h"
Jason::Jason(float x, float y)
	: Object2D(x, y)
{
	name = "Jason";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
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
	runSpeed = 300.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	isJumping = false;
	fallMultiplier = 4.5f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 2.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 25.0f, 44.0f };
	boxCollider->offset = { 0.0f, 1.0f };
	boxCollider->isTrigger = false;
	transform->scale = { -3.0f, 3.0f, 3.0f };
}

void Jason::Update()
{
	static float speedMulti = 0.0f;
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

	if (Input::GetKeyDown(KeyCode_SPACE) && downCollision != 0)
	{
		isJumping = true;
		D3DXVECTOR2 force(0.0f, 1800.0f);
		rigidbody->AddForce(force);
	}

	if (speedMulti > 1.0f)
	{
		speedMulti = 1.0f;
	}
	else if (speedMulti < 0.0f)
	{
		speedMulti = 0.0f;
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

	if (rigidbody->velocity.y < 0.0f)
	{
		rigidbody->velocity.y += Physic::gravity.y * (fallMultiplier - 1) * Time::GetFixedDeltaTime();
	}
	animationController->SetBool("isJumping", isJumping);
	animationController->SetFloat("runSpeed", abs(horizontalMove));
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
	LOG_INFO("{0}", animationController->GetCurrentAnimation()->GetName());
}

void Jason::OnCollisionEnter()
{
	isJumping = false;
}

void Jason::OnTriggerEnter()
{
}

void Jason::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}