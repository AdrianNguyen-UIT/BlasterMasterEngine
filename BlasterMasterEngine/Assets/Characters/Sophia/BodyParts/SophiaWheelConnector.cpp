#include "d3dpch.h"
#include "SophiaWheelConnector.h"
SophiaWheelConnector::SophiaWheelConnector(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	name = "Sophia Wheel Connector";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void SophiaWheelConnector::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");
	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	KeyFrame keyFrame;
	RECT rect;
	rect.left = 3;
	rect.top = 3 + yOffset + spriteHeight;
	rect.right = rect.left + spriteWidth + 1;
	rect.bottom = rect.top + spriteHeight + 1;
	keyFrame.rect = rect;

	std::shared_ptr<Animation> wheelConnectorRunRight = std::make_shared<Animation>("Wheel Connector Run Right");
	{
		wheelConnectorRunRight->SetAnimationFPS(20);
		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y - 2.0f / scaleY, 0.0f };
		wheelConnectorRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 2.0f / scaleY, 0.0f };
		wheelConnectorRunRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRunRight);
		animationController->SetDefaultAnimation(wheelConnectorRunRight);
	}

	std::shared_ptr<Animation> wheelConnectorRunLeft = std::make_shared<Animation>("Wheel Connector Run Left");
	{
		wheelConnectorRunLeft->SetAnimationFPS(20);
		keyFrame.scale = { 3.0f, 3.0f, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y, 0.0f };
		wheelConnectorRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y - 2.0f / scaleY, 0.0f };
		wheelConnectorRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y, 0.0f };
		wheelConnectorRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 2.0f / scaleY, 0.0f };
		wheelConnectorRunLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRunLeft);
	}

	std::shared_ptr<Animation> wheelConnectorTurnLeft = std::make_shared<Animation>("Wheel Connector Turn Left");
	{
		wheelConnectorTurnLeft->SetAnimationFPS(20);
		wheelConnectorTurnLeft->SetIsLooping(false);
		wheelConnectorTurnLeft->SetHasExitTime(true);
		wheelConnectorTurnLeft->SetAllowPause(false);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y - 2.0f / scaleY, 0.0f };
		wheelConnectorTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		wheelConnectorTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorTurnLeft);
	}

	std::shared_ptr<Animation> wheelConnectorTurnRight = std::make_shared<Animation>("Wheel Connector Turn Right");
	{
		wheelConnectorTurnRight->SetAnimationFPS(20);
		wheelConnectorTurnRight->SetIsLooping(false);
		wheelConnectorTurnRight->SetHasExitTime(true);
		wheelConnectorTurnRight->SetAllowPause(false);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y - 2.0f / scaleY, 0.0f };
		wheelConnectorTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		wheelConnectorTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorTurnRight);
	}

	std::shared_ptr<Animation> wheelConnectorRunRightPointUp = std::make_shared<Animation>("Wheel Connector Run Right Point Up");
	{
		wheelConnectorRunRightPointUp->SetAnimationFPS(60);
		wheelConnectorRunRightPointUp->SetAllowPause(false);
		wheelConnectorRunRightPointUp->SetIsLooping(false);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorRunRightPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRunRightPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorRunLeftPointUp = std::make_shared<Animation>("Wheel Connector Run Left Point Up");
	{
		wheelConnectorRunLeftPointUp->SetAnimationFPS(60);
		wheelConnectorRunLeftPointUp->SetAllowPause(false);
		wheelConnectorRunLeftPointUp->SetIsLooping(false);

		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorRunLeftPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRunLeftPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorRightPushDown = std::make_shared<Animation>("Wheel Connector Right Push Down");
	{
		wheelConnectorRightPushDown->SetAnimationFPS(12);
		wheelConnectorRightPushDown->SetIsLooping(false);
		wheelConnectorRightPushDown->SetAllowPause(false);
		wheelConnectorRightPushDown->SetHasExitTime(true);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y - 8.0f / scaleY, 0.0f };
		wheelConnectorRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRightPushDown->AddKeyFrames(keyFrame);
		animationController->AddAnimation(wheelConnectorRightPushDown);
	}

	std::shared_ptr<Animation> wheelConnectorRightPushDownPointUp = std::make_shared<Animation>("Wheel Connector Right Push Down Point Up");
	{
		wheelConnectorRightPushDownPointUp ->SetAnimationFPS(12);
		wheelConnectorRightPushDownPointUp ->SetIsLooping(false);
		wheelConnectorRightPushDownPointUp ->SetAllowPause(false);
		wheelConnectorRightPushDownPointUp ->SetHasExitTime(true);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f/ scaleY, 0.0f };
		wheelConnectorRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorRightPushDownPointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(wheelConnectorRightPushDownPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorLeftPushDown = std::make_shared<Animation>("Wheel Connector Left Push Down");
	{
		wheelConnectorLeftPushDown->SetAnimationFPS(12);
		wheelConnectorLeftPushDown->SetIsLooping(false);
		wheelConnectorLeftPushDown->SetAllowPause(false);
		wheelConnectorLeftPushDown->SetHasExitTime(true);

		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y - 8.0f / scaleY, 0.0f };
		wheelConnectorLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorLeftPushDown->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftPushDown);
	}

	std::shared_ptr<Animation> wheelConnectorLeftPushDownPointUp = std::make_shared<Animation>("Wheel Connector Left Push Down Point Up");
	{
		wheelConnectorLeftPushDownPointUp->SetAnimationFPS(12);
		wheelConnectorLeftPushDownPointUp->SetIsLooping(false);
		wheelConnectorLeftPushDownPointUp->SetAllowPause(false);
		wheelConnectorLeftPushDownPointUp->SetHasExitTime(true);

		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorLeftPushDownPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftPushDownPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorRightJumping = std::make_shared<Animation>("Wheel Connector Right Jumping");
	{
		wheelConnectorRightJumping->SetAnimationFPS(20);
		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorRightJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRightJumping);
	}

	std::shared_ptr<Animation> wheelConnectorRightJumpingPointUp = std::make_shared<Animation>("Wheel Connector Right Jumping Point Up");
	{
		wheelConnectorRightJumpingPointUp->SetAnimationFPS(20);
		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 16.0f / scaleY, 0.0f };
		wheelConnectorRightJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRightJumpingPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorLeftJumping = std::make_shared<Animation>("Wheel Connector Left Jumping");
	{
		wheelConnectorLeftJumping->SetAnimationFPS(20);
		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorLeftJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftJumping);
	}

	std::shared_ptr<Animation> wheelConnectorLeftJumpingPointUp = std::make_shared<Animation>("Wheel Connector Left Jumping Point Up");
	{
		wheelConnectorLeftJumpingPointUp->SetAnimationFPS(20);
		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 16.0f / scaleY, 0.0f };
		wheelConnectorLeftJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftJumpingPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorRightFalling = std::make_shared<Animation>("Wheel Connector Right Falling");
	{
		wheelConnectorRightFalling->SetAnimationFPS(20);
		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorRightFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRightFalling);
	}

	std::shared_ptr<Animation> wheelConnectorRightFallingPointUp = std::make_shared<Animation>("Wheel Connector Right Falling Point Up");
	{
		wheelConnectorRightFallingPointUp->SetAnimationFPS(20);
		keyFrame.scale = { -scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorRightFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorRightFallingPointUp);
	}

	std::shared_ptr<Animation> wheelConnectorLeftFalling = std::make_shared<Animation>("Wheel Connector Left Falling");
	{
		wheelConnectorLeftFalling->SetAnimationFPS(20);
		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y, 0.0f };
		wheelConnectorLeftFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftFalling);
	}

	std::shared_ptr<Animation> wheelConnectorLeftFallingPointUp = std::make_shared<Animation>("Wheel Connector Left Falling Point Up");
	{
		wheelConnectorLeftFallingPointUp->SetAnimationFPS(20);
		keyFrame.scale = { scaleX, scaleY, 0.0f };

		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorLeftFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorLeftFallingPointUp);
	}


	std::shared_ptr<Animation> wheelConnectorJumpingTurnLeft = std::make_shared<Animation>("Wheel Connector Jumping Turn Left");
	{
		wheelConnectorJumpingTurnLeft->SetAnimationFPS(20);
		wheelConnectorJumpingTurnLeft->SetIsLooping(false);
		wheelConnectorJumpingTurnLeft->SetHasExitTime(true);
		wheelConnectorJumpingTurnLeft->SetAllowPause(false);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorJumpingTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		wheelConnectorJumpingTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorJumpingTurnLeft);
	}

	std::shared_ptr<Animation> wheelConnectorJumpingTurnRight = std::make_shared<Animation>("Wheel Connector Jumping Turn Right");
	{
		wheelConnectorJumpingTurnRight->SetAnimationFPS(20);
		wheelConnectorJumpingTurnRight->SetIsLooping(false);
		wheelConnectorJumpingTurnRight->SetHasExitTime(true);
		wheelConnectorJumpingTurnRight->SetAllowPause(false);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y + 8.0f / scaleY, 0.0f };
		wheelConnectorJumpingTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		wheelConnectorJumpingTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorJumpingTurnRight);
	}

	std::shared_ptr<Animation> wheelConnectorFallingTurnLeft = std::make_shared<Animation>("Wheel Connector Falling Turn Left");
	{
		wheelConnectorFallingTurnLeft->SetAnimationFPS(20);
		wheelConnectorFallingTurnLeft->SetIsLooping(false);
		wheelConnectorFallingTurnLeft->SetHasExitTime(true);
		wheelConnectorFallingTurnLeft->SetAllowPause(false);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y / scaleY, 0.0f };
		wheelConnectorFallingTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		wheelConnectorFallingTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorFallingTurnLeft);
	}

	std::shared_ptr<Animation> wheelConnectorFallingTurnRight = std::make_shared<Animation>("Wheel Connector Falling Turn Right");
	{
		wheelConnectorFallingTurnRight->SetAnimationFPS(20);
		wheelConnectorFallingTurnRight->SetIsLooping(false);
		wheelConnectorFallingTurnRight->SetHasExitTime(true);
		wheelConnectorFallingTurnRight->SetAllowPause(false);

		keyFrame.scale = { scaleX, scaleY, 0.0f };
		keyFrame.position = { transform->position.x, transform->position.y / scaleY, 0.0f };
		wheelConnectorFallingTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = { -scaleX, scaleY, 0.0f };
		wheelConnectorFallingTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(wheelConnectorFallingTurnRight);
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
		animationController->GetAnimationIndex(wheelConnectorRunRight),
		animationController->GetAnimationIndex(wheelConnectorTurnLeft));
	{
		rightToTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightToTurnLeftTrans);
	}

	std::shared_ptr<Transition> turnLeftToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorTurnLeft),
		animationController->GetAnimationIndex(wheelConnectorRunLeft));
	{
		animationController->AddTransition(turnLeftToLeftTrans);
	}

	std::shared_ptr<Transition> leftToTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeft),
		animationController->GetAnimationIndex(wheelConnectorTurnRight));
	{

		leftToTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftToTurnRightTrans);
	}

	std::shared_ptr<Transition> turnRightToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorTurnRight),
		animationController->GetAnimationIndex(wheelConnectorRunRight));
	{
		animationController->AddTransition(turnRightToRightTrans);
	}

	std::shared_ptr<Transition> rightToPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunRight),
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp));
	{
		rightToPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightToPointUpTrans);
	}

	std::shared_ptr<Transition> pointUpToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunRight));
	{
		pointUpToRightTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(pointUpToRightTrans);
	}

	std::shared_ptr<Transition> leftToPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeft),
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp));
	{
		leftToPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftToPointUpTrans);
	}

	std::shared_ptr<Transition> pointUpToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunLeft));
	{
		pointUpToLeftTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(pointUpToLeftTrans);
	}

	std::shared_ptr<Transition> pointUpRightToPointUpLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp));
	{
		pointUpRightToPointUpLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(pointUpRightToPointUpLeftTrans);
	}

	std::shared_ptr<Transition> pointUpLeftToPointUpRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp));
	{
		pointUpLeftToPointUpRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(pointUpLeftToPointUpRightTrans);
	}

	std::shared_ptr<Transition> rightToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunRight),
		animationController->GetAnimationIndex(wheelConnectorRightPushDown));
	{
		rightToRightPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDown),
		animationController->GetAnimationIndex(wheelConnectorRightJumping));
	{
		rightPushDownToRightJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumping),
		animationController->GetAnimationIndex(wheelConnectorRightFalling));
	{
		rightJumpingToRightFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingToRightFallingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFalling),
		animationController->GetAnimationIndex(wheelConnectorRightPushDown));
	{
		rightFallingToRightPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDown),
		animationController->GetAnimationIndex(wheelConnectorRunRight));
	{
		rightPushDownToRightTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightPushDownToRightTrans);
	}

	std::shared_ptr<Transition> rightPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp));
	{
		rightPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp));
	{
		rightPushDownPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownPointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp));
	{
		rightJumpingPointUpToRightFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingPointUpToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp));
	{
		rightFallingPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunRightPointUp));
	{
		rightPushDownPointUpToRightPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightPushDownPointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDown),
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp));
	{
		rightPushDownToRightPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPushDownToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightPushDown));
	{
		rightPushDownPointUpToRightPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPushDownPointUpToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumping),
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp));
	{
		rightJumpingToRightJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightJumpingToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightJumping));
	{
		rightJumpingPointUpToRightJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightJumpingPointUpToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFalling),
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp));
	{
		rightFallingToRightFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightFallingToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightFalling));
	{
		rightFallingPointUpToRightFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightFallingTrans);
	}

	std::shared_ptr<Transition> leftToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeft),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown));
	{
		leftToLeftPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown),
		animationController->GetAnimationIndex(wheelConnectorLeftJumping));
	{
		leftPushDownToLeftJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumping),
		animationController->GetAnimationIndex(wheelConnectorLeftFalling));
	{
		leftJumpingToLeftFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingToLeftFallingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFalling),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown));
	{
		leftFallingToLeftPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown),
		animationController->GetAnimationIndex(wheelConnectorRunLeft));
	{
		leftPushDownToLeftTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftPushDownToLeftTrans);
	}

	std::shared_ptr<Transition> leftPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp));
	{
		leftPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp));
	{
		leftPushDownPointUpToLeftJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownPointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp));
	{
		leftJumpingPointUpToLeftFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingPointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp));
	{
		leftFallingPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorRunLeftPointUp));
	{
		leftPushDownPointUpToLeftPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftPushDownPointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp));
	{
		leftPushDownToLeftPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPushDownToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftPushDownPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftPushDown));
	{
		leftPushDownPointUpToLeftPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPushDownPointUpToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumping),
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp));
	{
		leftJumpingToLeftJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftJumpingToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftJumping));
	{
		leftJumpingPointUpToLeftJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftJumpingPointUpToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFalling),
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp));
	{
		leftFallingToLeftFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftFallingToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftFalling));
	{
		leftFallingPointUpToLeftFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftFallingTrans);
	}




	std::shared_ptr<Transition> rightJumpingToJumpingTurnLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumping),
		animationController->GetAnimationIndex(wheelConnectorJumpingTurnLeft));
	{
		rightJumpingToJumpingTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightJumpingToJumpingTurnLeftTrans);
	}

	std::shared_ptr<Transition> jumpingTurnLeftToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorJumpingTurnLeft),
		animationController->GetAnimationIndex(wheelConnectorLeftJumping));
	{
		animationController->AddTransition(jumpingTurnLeftToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftJumpingToJumpingTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumping),
		animationController->GetAnimationIndex(wheelConnectorJumpingTurnRight));
	{
		leftJumpingToJumpingTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftJumpingToJumpingTurnRightTrans);
	}

	std::shared_ptr<Transition> jumpingTurnRightToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorJumpingTurnRight),
		animationController->GetAnimationIndex(wheelConnectorRightJumping));
	{
		animationController->AddTransition(jumpingTurnRightToRightJumpingTrans);
	}


	std::shared_ptr<Transition> rightFallingToFallingTurnLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFalling),
		animationController->GetAnimationIndex(wheelConnectorFallingTurnLeft));
	{
		rightFallingToFallingTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightFallingToFallingTurnLeftTrans);
	}


	std::shared_ptr<Transition> fallingTurnLeftToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorFallingTurnLeft),
		animationController->GetAnimationIndex(wheelConnectorLeftFalling));
	{
		animationController->AddTransition(fallingTurnLeftToLeftFallingTrans);
	}


	std::shared_ptr<Transition> leftFallingToFallingTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFalling),
		animationController->GetAnimationIndex(wheelConnectorFallingTurnRight));
	{
		leftFallingToFallingTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftFallingToFallingTurnRightTrans);
	}

	std::shared_ptr<Transition> fallingTurnRightToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorFallingTurnRight),
		animationController->GetAnimationIndex(wheelConnectorRightFalling));
	{
		animationController->AddTransition(fallingTurnRightToRightFallingTrans);
	}


	std::shared_ptr<Transition> rightJumpingPointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp));
	{
		rightJumpingPointUpToLeftJumpingPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightJumpingPointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftJumpingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightJumpingPointUp));
	{
		leftJumpingPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftJumpingPointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp));
	{
		rightFallingPointUpToLeftFallingPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightFallingPointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(wheelConnectorLeftFallingPointUp),
		animationController->GetAnimationIndex(wheelConnectorRightFallingPointUp));
	{
		leftJumpingPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftFallingPointUpToRightFallingPointUpTrans);
	}
}