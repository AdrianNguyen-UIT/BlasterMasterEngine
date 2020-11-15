#include "d3dpch.h"
#include "SophiaCabin.h"
SophiaCabin::SophiaCabin(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	name = "Sophia Cabin";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void SophiaCabin::CreateResources()
{
	spriteRenderer->sprite = DeviceResources::LoadTexture(SOPHIA_JASON_TEXTURE_PATH, 0);
	KeyFrame keyFrame;
	RECT normRect;
	RECT pointUpRect;
	RECT turnRect;

	normRect.left = 39;
	normRect.top = 3;
	normRect.right = 55;
	normRect.bottom = 11;

	turnRect.left = 56;
	turnRect.top = 3;
	turnRect.right = 72;
	turnRect.bottom = 11;
	
	pointUpRect.left = 73;
	pointUpRect.top = 3;
	pointUpRect.right = 89;
	pointUpRect.bottom = 19;
	std::shared_ptr<Animation> cabinRunRight = std::make_shared<Animation>("Cabin Run Right");
	{
		cabinRunRight->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 22.0f, 0.0f };
		cabinRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 26.0f, 0.0f };
		cabinRunRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRunRight);
		animationController->SetDefaultAnimation(cabinRunRight);
	}

	std::shared_ptr<Animation> cabinRunLeft = std::make_shared<Animation>("Cabin Run Left");
	{
		cabinRunLeft->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 22.0f, 0.0f };
		cabinRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 26.0f, 0.0f };
		cabinRunLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRunLeft);
	}

	std::shared_ptr<Animation> cabinTurnLeft = std::make_shared<Animation>("Cabin Turn Left");
	{
		cabinTurnLeft->SetAnimationFPS(20);
		cabinTurnLeft->SetIsLooping(false);
		cabinTurnLeft->SetHasExitTime(true);
		cabinTurnLeft->SetAllowPause(false);

		keyFrame.rect = turnRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x + 9.0f, 22.0f, 0.0f };
		cabinTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = { 3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x * -1.0f - 9.0f, 22.0f, 0.0f };
		cabinTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinTurnLeft);
	}

	std::shared_ptr<Animation> cabinTurnRight = std::make_shared<Animation>("Cabin Turn Right");
	{
		cabinTurnRight->SetAnimationFPS(20);
		cabinTurnRight->SetIsLooping(false);
		cabinTurnRight->SetHasExitTime(true);
		cabinTurnRight->SetAllowPause(false);
		
		keyFrame.rect = turnRect;

		keyFrame.scale = { 3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x * -1.0f - 9.0f, 22.0f, 0.0f };
		cabinTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x + 9.0f, 22.0f, 0.0f };
		cabinTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinTurnRight);
	}

	std::shared_ptr<Animation> cabinRunRightPrePointUp = std::make_shared<Animation>("Cabin Run Right Pre Point Up");
	{
		cabinRunRightPrePointUp->SetAnimationFPS(20);
		cabinRunRightPrePointUp->SetAllowPause(false);
		cabinRunRightPrePointUp->SetIsLooping(false);
		cabinRunRightPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRunRightPrePointUp->AddKeyFrames(keyFrame);
		cabinRunRightPrePointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(cabinRunRightPrePointUp);
	}

	std::shared_ptr<Animation> cabinRunLeftPrePointUp = std::make_shared<Animation>("Cabin Run Left Pre Point Up");
	{
		cabinRunLeftPrePointUp->SetAnimationFPS(20);
		cabinRunLeftPrePointUp->SetAllowPause(false);
		cabinRunLeftPrePointUp->SetIsLooping(false);
		cabinRunLeftPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinRunLeftPrePointUp->AddKeyFrames(keyFrame);
		cabinRunLeftPrePointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(cabinRunLeftPrePointUp);
	}

	std::shared_ptr<Animation> cabinRunRightPointUp = std::make_shared<Animation>("Cabin Run Right Point Up");
	{
		cabinRunRightPointUp->SetAnimationFPS(20);
		cabinRunRightPointUp->SetAllowPause(false);
		cabinRunRightPointUp->SetIsLooping(false);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRunRightPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRunRightPointUp);
	}

	std::shared_ptr<Animation> cabinRunLeftPointUp = std::make_shared<Animation>("Cabin Run Left Point Up");
	{
		cabinRunLeftPointUp->SetAnimationFPS(20);
		cabinRunLeftPointUp->SetAllowPause(false);
		cabinRunLeftPointUp->SetIsLooping(false);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinRunLeftPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRunLeftPointUp);
	}

	std::shared_ptr<Animation> cabinRightPushDown = std::make_shared<Animation>("Barrel Right Push Down");
	{
		cabinRightPushDown->SetAnimationFPS(12);
		cabinRightPushDown->SetIsLooping(false);
		cabinRightPushDown->SetAllowPause(false);
		cabinRightPushDown->SetHasExitTime(true);

		keyFrame.rect = normRect;

		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 16.0f, 0.0f };
		cabinRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightPushDown->AddKeyFrames(keyFrame);
		animationController->AddAnimation(cabinRightPushDown);
	}

	std::shared_ptr<Animation> cabinRightPushDownPrePointUp = std::make_shared<Animation>("Barrel Right Push Down Pre Point Up");
	{
		cabinRightPushDownPrePointUp->SetAnimationFPS(20);
		cabinRightPushDownPrePointUp->SetIsLooping(false);
		cabinRightPushDownPrePointUp->SetAllowPause(false);
		cabinRightPushDownPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;

		keyFrame.scale = { -3.0f, 3.0f, 0.0f };
		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightPushDownPrePointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(cabinRightPushDownPrePointUp);
	}

	std::shared_ptr<Animation> cabinRightPushDownPointUp = std::make_shared<Animation>("Barrel Right Push Down Point Up");
	{
		cabinRightPushDownPointUp->SetAnimationFPS(12);
		cabinRightPushDownPointUp->SetIsLooping(false);
		cabinRightPushDownPointUp->SetAllowPause(false);
		cabinRightPushDownPointUp->SetHasExitTime(true);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightPushDownPointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(cabinRightPushDownPointUp);
	}

	std::shared_ptr<Animation> cabinLeftPushDown = std::make_shared<Animation>("Barrel Left Push Down");
	{
		cabinLeftPushDown->SetAnimationFPS(12);
		cabinLeftPushDown->SetIsLooping(false);
		cabinLeftPushDown->SetAllowPause(false);
		cabinLeftPushDown->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 16.0f, 0.0f };
		cabinLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftPushDown->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftPushDown);
	}

	std::shared_ptr<Animation> cabinLeftPushDownPrePointUp = std::make_shared<Animation>("Barrel Left Push Down Pre Point Up");
	{
		cabinLeftPushDownPrePointUp->SetAnimationFPS(20);
		cabinLeftPushDownPrePointUp->SetIsLooping(false);
		cabinLeftPushDownPrePointUp->SetAllowPause(false);
		cabinLeftPushDownPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftPushDownPrePointUp);
	}

	std::shared_ptr<Animation> cabinLeftPushDownPointUp = std::make_shared<Animation>("Barrel Left Push Down Point Up");
	{
		cabinLeftPushDownPointUp->SetAnimationFPS(12);
		cabinLeftPushDownPointUp->SetIsLooping(false);
		cabinLeftPushDownPointUp->SetAllowPause(false);
		cabinLeftPushDownPointUp->SetHasExitTime(true);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftPushDownPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftPushDownPointUp);
	}

	std::shared_ptr<Animation> cabinRightJumping = std::make_shared<Animation>("Barrel Right Jumping");
	{
		cabinRightJumping->SetAnimationFPS(20);
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.rect = normRect;
		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightJumping);
	}

	std::shared_ptr<Animation> cabinRightJumpingPrePointUp = std::make_shared<Animation>("Barrel Right Jumping Pre Point Up");
	{
		cabinRightJumpingPrePointUp->SetAnimationFPS(20);
		cabinRightJumpingPrePointUp->SetIsLooping(false);
		cabinRightJumpingPrePointUp->SetAllowPause(false);
		cabinRightJumpingPrePointUp->SetHasExitTime(true);
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.rect = normRect;
		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightJumpingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightJumpingPrePointUp);
	}

	std::shared_ptr<Animation> cabinRightJumpingPointUp = std::make_shared<Animation>("Barrel Right Jumping Point Up");
	{
		cabinRightJumpingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 40.0f, 0.0f };
		cabinRightJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightJumpingPointUp);
	}

	std::shared_ptr<Animation> cabinLeftJumping = std::make_shared<Animation>("Barrel Left Jumping");
	{
		cabinLeftJumping->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftJumping);
	}

	std::shared_ptr<Animation> cabinLeftJumpingPrePointUp = std::make_shared<Animation>("Barrel Left Jumping Pre Point Up");
	{
		cabinLeftJumpingPrePointUp->SetAnimationFPS(20);
		cabinLeftJumpingPrePointUp->SetIsLooping(false);
		cabinLeftJumpingPrePointUp->SetAllowPause(false);
		cabinLeftJumpingPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftJumpingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftJumpingPrePointUp);
	}

	std::shared_ptr<Animation> cabinLeftJumpingPointUp = std::make_shared<Animation>("Barrel Left Jumping Point Up");
	{
		cabinLeftJumpingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 40.0f, 0.0f };
		cabinLeftJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftJumpingPointUp);
	}

	std::shared_ptr<Animation> cabinRightFalling = std::make_shared<Animation>("Barrel Right Falling");
	{
		cabinRightFalling->SetAnimationFPS(20);
		keyFrame.rect = normRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightFalling);
	}

	std::shared_ptr<Animation> cabinRightFallingPrePointUp = std::make_shared<Animation>("Barrel Right Falling Pre Point Up");
	{
		cabinRightFallingPrePointUp->SetAnimationFPS(20);
		cabinRightFallingPrePointUp->SetIsLooping(false);
		cabinRightFallingPrePointUp->SetAllowPause(false);
		cabinRightFallingPrePointUp->SetHasExitTime(true);
		keyFrame.rect = normRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 24.0f, 0.0f };
		cabinRightFallingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightFallingPrePointUp);
	}

	std::shared_ptr<Animation> cabinRightFallingPointUp = std::make_shared<Animation>("Barrel Right Falling Point Up");
	{
		cabinRightFallingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { -3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x, 32.0f, 0.0f };
		cabinRightFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinRightFallingPointUp);
	}

	std::shared_ptr<Animation> cabinLeftFalling = std::make_shared<Animation>("Barrel Left Falling");
	{
		cabinLeftFalling->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftFalling);
	}

	std::shared_ptr<Animation> cabinLeftFallingPrePointUp = std::make_shared<Animation>("Barrel Left Falling Pre Point Up");
	{
		cabinLeftFallingPrePointUp->SetAnimationFPS(20);
		cabinLeftFallingPrePointUp->SetIsLooping(false);
		cabinLeftFallingPrePointUp->SetAllowPause(false);
		cabinLeftFallingPrePointUp->SetHasExitTime(true);
		keyFrame.rect = normRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 24.0f, 0.0f };
		cabinLeftFallingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftFallingPrePointUp);
	}

	std::shared_ptr<Animation> cabinLeftFallingPointUp = std::make_shared<Animation>("Barrel Left Falling Point Up");
	{
		cabinLeftFallingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, 32.0f, 0.0f };
		cabinLeftFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(cabinLeftFallingPointUp);
	}

	std::shared_ptr<Parameter<float>> runSpeed = std::make_shared<Parameter<float>>("runSpeed");
	{
		animationController->AddFloatParameter(runSpeed);
	}

	std::shared_ptr<Parameter<bool>> pointUp = std::make_shared<Parameter<bool>>("pointUp");
	{
		animationController->AddBoolParameter(pointUp);
	}

	std::shared_ptr<Parameter<bool>> isJumping = std::make_shared<Parameter<bool>>("isJumping");
	{
		animationController->AddBoolParameter(isJumping);
	}

	std::shared_ptr<Parameter<float>> verticalVelocity = std::make_shared<Parameter<float>>("verticalVelocity");
	{
		animationController->AddFloatParameter(verticalVelocity);
	}

	std::shared_ptr<TransitionCondition<float>> rightToLeftFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		rightToLeftFloatCond->SetParameter(runSpeed);
		rightToLeftFloatCond->SetCondition(Condition::Less);
		rightToLeftFloatCond->SetValue(0.0f);
	}

	std::shared_ptr<TransitionCondition<float>> leftToRightFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		leftToRightFloatCond->SetParameter(runSpeed);
		leftToRightFloatCond->SetCondition(Condition::Greater);
		leftToRightFloatCond->SetValue(0.0f);
	}

	std::shared_ptr<TransitionCondition<bool>> pointUpBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		pointUpBoolCond->SetParameter(pointUp);
		pointUpBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> backFromPointUpBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		backFromPointUpBoolCond->SetParameter(pointUp);
		backFromPointUpBoolCond->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<bool>> jumpingBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		jumpingBoolCond->SetParameter(isJumping);
		jumpingBoolCond->SetValue(true);
	}

	std::shared_ptr<TransitionCondition<bool>> fallingBoolCond = std::make_shared<TransitionCondition<bool>>();
	{
		fallingBoolCond->SetParameter(isJumping);
		fallingBoolCond->SetValue(false);
	}

	std::shared_ptr<TransitionCondition<float>> jumpingFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		jumpingFloatCond->SetParameter(verticalVelocity);
		jumpingFloatCond->SetCondition(Condition::Greater);
		jumpingFloatCond->SetValue(0.0f);
	}

	std::shared_ptr<TransitionCondition<float>> fallingFloatCond = std::make_shared<TransitionCondition<float>>();
	{
		fallingFloatCond->SetParameter(verticalVelocity);
		fallingFloatCond->SetCondition(Condition::Less);
		fallingFloatCond->SetValue(0.0f);
	}

	std::shared_ptr<Transition> rightToTurnLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRight),
		animationController->GetAnimationIndex(cabinTurnLeft));
	{
		rightToTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightToTurnLeftTrans);
	}

	std::shared_ptr<Transition> turnLeftToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinTurnLeft),
		animationController->GetAnimationIndex(cabinRunLeft));
	{
		animationController->AddTransition(turnLeftToLeftTrans);
	}

	std::shared_ptr<Transition> leftToTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeft),
		animationController->GetAnimationIndex(cabinTurnRight));
	{
		leftToTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftToTurnRightTrans);
	}

	std::shared_ptr<Transition> turnRightToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinTurnRight),
		animationController->GetAnimationIndex(cabinRunRight));
	{
		animationController->AddTransition(turnRightToRightTrans);
	}

	std::shared_ptr<Transition> rightToRightPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRight),
		animationController->GetAnimationIndex(cabinRunRightPrePointUp));
	{
		rightToRightPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightToRightPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPrePointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRightPrePointUp),
		animationController->GetAnimationIndex(cabinRunRightPointUp));
	{
		rightPrePointUpToRightPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPrePointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightPointUpToRightPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRightPointUp),
		animationController->GetAnimationIndex(cabinRunRightPrePointUp));
	{
		rightPointUpToRightPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPointUpToRightPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPrePointUpToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRightPrePointUp),
		animationController->GetAnimationIndex(cabinRunRight));
	{
		rightPrePointUpToRightTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPrePointUpToRightTrans);
	}

	std::shared_ptr<Transition> leftToLeftPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeft),
		animationController->GetAnimationIndex(cabinRunLeftPrePointUp));
	{
		leftToLeftPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftToLeftPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPrePointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeftPrePointUp),
		animationController->GetAnimationIndex(cabinRunLeftPointUp));
	{
		leftPrePointUpToLeftPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPrePointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPointUpToLeftPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeftPointUp),
		animationController->GetAnimationIndex(cabinRunLeftPrePointUp));
	{
		leftPointUpToLeftPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPointUpToLeftPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPrePointUpToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeftPrePointUp),
		animationController->GetAnimationIndex(cabinRunLeft));
	{
		leftPrePointUpToLeftTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPrePointUpToLeftTrans);
	}

	std::shared_ptr<Transition> rightPointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRightPointUp),
		animationController->GetAnimationIndex(cabinRunLeftPointUp));
	{
		rightPointUpToLeftPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightPointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeftPointUp),
		animationController->GetAnimationIndex(cabinRunRightPointUp));
	{
		leftPointUpToRightPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftPointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRight),
		animationController->GetAnimationIndex(cabinRightPushDown));
	{
		rightToRightPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDown),
		animationController->GetAnimationIndex(cabinRightJumping));
	{
		rightPushDownToRightJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumping),
		animationController->GetAnimationIndex(cabinRightFalling));
	{
		rightJumpingToRightFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingToRightFallingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFalling),
		animationController->GetAnimationIndex(cabinRightPushDown));
	{
		rightFallingToRightPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDown),
		animationController->GetAnimationIndex(cabinRunRight));
	{
		animationController->AddTransition(rightPushDownToRightTrans);
	}

	std::shared_ptr<Transition> rightPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunRightPointUp),
		animationController->GetAnimationIndex(cabinRightPushDownPointUp));
	{
		rightPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDownPointUp),
		animationController->GetAnimationIndex(cabinRightJumpingPointUp));
	{
		rightPushDownPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownPointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumpingPointUp),
		animationController->GetAnimationIndex(cabinRightFallingPointUp));
	{
		rightJumpingPointUpToRightFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingPointUpToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFallingPointUp),
		animationController->GetAnimationIndex(cabinRightPushDownPointUp));
	{
		rightFallingPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDownPointUp),
		animationController->GetAnimationIndex(cabinRunRightPointUp));
	{
		animationController->AddTransition(rightPushDownPointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDown),
		animationController->GetAnimationIndex(cabinRightPushDownPrePointUp));
	{
		rightPushDownToRightPushDownPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPushDownToRightPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPrePointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDownPrePointUp),
		animationController->GetAnimationIndex(cabinRightPushDownPointUp));
	{
		rightPushDownPrePointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPushDownPrePointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDownPointUp),
		animationController->GetAnimationIndex(cabinRightPushDownPrePointUp));
	{
		rightPushDownPointUpToRightPushDownPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPushDownPointUpToRightPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPrePointUpToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightPushDownPrePointUp),
		animationController->GetAnimationIndex(cabinRightPushDown));
	{
		rightPushDownPrePointUpToRightPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPushDownPrePointUpToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumping),
		animationController->GetAnimationIndex(cabinRightJumpingPrePointUp));
	{
		rightJumpingToRightJumpingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightJumpingToRightJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPrePointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumpingPrePointUp),
		animationController->GetAnimationIndex(cabinRightJumpingPointUp));
	{
		rightJumpingPrePointUpToRightJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightJumpingPrePointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumpingPointUp),
		animationController->GetAnimationIndex(cabinRightJumpingPrePointUp));
	{
		rightJumpingPointUpToRightJumpingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightJumpingPointUpToRightJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPrePointUpToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightJumpingPrePointUp),
		animationController->GetAnimationIndex(cabinRightJumping));
	{
		rightJumpingPrePointUpToRightJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightJumpingPrePointUpToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFalling),
		animationController->GetAnimationIndex(cabinRightFallingPrePointUp));
	{
		rightFallingToRightFallingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightFallingToRightFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPrePointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFallingPrePointUp),
		animationController->GetAnimationIndex(cabinRightFallingPointUp));
	{
		rightFallingPrePointUpToRightFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightFallingPrePointUpToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFallingPointUp),
		animationController->GetAnimationIndex(cabinRightFallingPrePointUp));
	{
		rightFallingPointUpToRightFallingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPrePointUpToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRightFallingPrePointUp),
		animationController->GetAnimationIndex(cabinRightFalling));
	{
		rightFallingPrePointUpToRightFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightFallingPrePointUpToRightFallingTrans);
	}

	std::shared_ptr<Transition> leftToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeft),
		animationController->GetAnimationIndex(cabinLeftPushDown));
	{
		leftToLeftPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDown),
		animationController->GetAnimationIndex(cabinLeftJumping));
	{
		leftPushDownToLeftJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumping),
		animationController->GetAnimationIndex(cabinLeftFalling));
	{
		leftJumpingToLeftFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingToLeftFallingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFalling),
		animationController->GetAnimationIndex(cabinLeftPushDown));
	{
		leftFallingToLeftPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDown),
		animationController->GetAnimationIndex(cabinRunLeft));
	{
		animationController->AddTransition(leftPushDownToLeftTrans);
	}

	std::shared_ptr<Transition> leftPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinRunLeftPointUp),
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp));
	{
		leftPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp),
		animationController->GetAnimationIndex(cabinLeftJumpingPointUp));
	{
		leftPushDownPointUpToLeftJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownPointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumpingPointUp),
		animationController->GetAnimationIndex(cabinLeftFallingPointUp));
	{
		leftJumpingPointUpToLeftFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingPointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFallingPointUp),
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp));
	{
		leftFallingPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp),
		animationController->GetAnimationIndex(cabinRunLeftPointUp));
	{
		animationController->AddTransition(leftPushDownPointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDown),
		animationController->GetAnimationIndex(cabinLeftPushDownPrePointUp));
	{
		leftPushDownToLeftPushDownPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPushDownToLeftPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPrePointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDownPrePointUp),
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp));
	{
		leftPushDownPrePointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPushDownPrePointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDownPointUp),
		animationController->GetAnimationIndex(cabinLeftPushDownPrePointUp));
	{
		leftPushDownPointUpToLeftPushDownPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPushDownPointUpToLeftPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPrePointUpToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftPushDownPrePointUp),
		animationController->GetAnimationIndex(cabinLeftPushDown));
	{
		leftPushDownPrePointUpToLeftPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPushDownPrePointUpToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumping),
		animationController->GetAnimationIndex(cabinLeftJumpingPrePointUp));
	{
		leftJumpingToLeftJumpingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftJumpingToLeftJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPrePointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumpingPrePointUp),
		animationController->GetAnimationIndex(cabinLeftJumpingPointUp));
	{
		leftJumpingPrePointUpToLeftJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftJumpingPrePointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumpingPointUp),
		animationController->GetAnimationIndex(cabinLeftJumpingPrePointUp));
	{
		leftJumpingPointUpToLeftJumpingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftJumpingPointUpToLeftJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPrePointUpToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftJumpingPrePointUp),
		animationController->GetAnimationIndex(cabinLeftJumping));
	{
		leftJumpingPrePointUpToLeftJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftJumpingPrePointUpToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFalling),
		animationController->GetAnimationIndex(cabinLeftFallingPrePointUp));
	{
		leftFallingToLeftFallingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftFallingToLeftFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPrePointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFallingPrePointUp),
		animationController->GetAnimationIndex(cabinLeftFallingPointUp));
	{
		leftFallingPrePointUpToLeftFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftFallingPrePointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFallingPointUp),
		animationController->GetAnimationIndex(cabinLeftFallingPrePointUp));
	{
		leftFallingPointUpToLeftFallingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPrePointUpToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(cabinLeftFallingPrePointUp),
		animationController->GetAnimationIndex(cabinLeftFalling));
	{
		leftFallingPrePointUpToLeftFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftFallingPrePointUpToLeftFallingTrans);
	}
}

void SophiaCabin::Start()
{
}

void SophiaCabin::Update()
{
	//LOG_INFO("{0}", animationController->GetCurrentAnimation()->GetName());
}

void SophiaCabin::OnCollisionEnter()
{
}

void SophiaCabin::OnTriggerEnter()
{
}