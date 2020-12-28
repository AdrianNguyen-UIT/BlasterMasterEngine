#include "d3dpch.h"
#include "SophiaBarrel.h"
SophiaBarrel::SophiaBarrel(float x, float y)
	: Object2D(x, y)
{
	tag = Tag::Player;
	name = "Sophia Barrel";
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
}

void SophiaBarrel::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");

	int spriteWidth = 7;
	int spriteHeight = 7;
	int xOffset = 2;
	int yOffset = 2;
	KeyFrame keyFrame;
	RECT normRect;
	RECT pointUpRect;
	RECT prePointUpRect;
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	D3DXVECTOR3 rightScale = { -scaleX , scaleY , 0.0f };
	D3DXVECTOR3 leftScale = { scaleX , scaleY , 0.0f };
	normRect.left = 3 + spriteWidth + xOffset;
	normRect.top = 3;
	normRect.right = normRect.left + spriteWidth + 1;
	normRect.bottom = normRect.top + spriteHeight + 1;

	prePointUpRect.left = 21;
	prePointUpRect.top = 3;
	prePointUpRect.right = 29;
	prePointUpRect.bottom = 11;

	pointUpRect.left = 30;
	pointUpRect.top = 3;
	pointUpRect.right = 38;
	pointUpRect.bottom = 11;

	std::shared_ptr<Animation> barrelRunRight = std::make_shared<Animation>("Barrel Run Right");
	{
		barrelRunRight->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRunRight->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 26.0f / scaleY, 0.0f };
		barrelRunRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRunRight);
		animationController->SetDefaultAnimation(barrelRunRight);
	}

	std::shared_ptr<Animation> barrelRunLeft = std::make_shared<Animation>("Barrel Run Left");
	{
		barrelRunLeft->SetAnimationFPS(20);
		keyFrame.rect = normRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRunLeft->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 26.0f / scaleY, 0.0f };
		barrelRunLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRunLeft);
	}

	std::shared_ptr<Animation> barrelTurnRight = std::make_shared<Animation>("Barrel Turn Right");
	{
		barrelTurnRight->SetAnimationFPS(20);
		barrelTurnRight->SetIsLooping(false);
		barrelTurnRight->SetHasExitTime(true);
		barrelTurnRight->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelTurnRight);
	}

	std::shared_ptr<Animation> barrelTurnLeft = std::make_shared<Animation>("Barrel Turn Left");
	{
		barrelTurnLeft->SetAnimationFPS(20);
		barrelTurnLeft->SetIsLooping(false);
		barrelTurnLeft->SetHasExitTime(true);
		barrelTurnLeft->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + 22.0f / scaleY, 0.0f };
		barrelTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelTurnLeft);
	}

	std::shared_ptr<Animation> barrelRunRightPrePointUp = std::make_shared<Animation>("Barrel Run Right Pre Point Up");
	{
		barrelRunRightPrePointUp->SetAnimationFPS(20);
		barrelRunRightPrePointUp->SetAllowPause(false);
		barrelRunRightPrePointUp->SetIsLooping(false);
		barrelRunRightPrePointUp->SetHasExitTime(true);

		keyFrame.rect = prePointUpRect;
		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + 48.0f / scaleY, 0.0f };
		barrelRunRightPrePointUp->AddKeyFrames(keyFrame);
		barrelRunRightPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRunRightPrePointUp);
	}

	std::shared_ptr<Animation> barrelRunLeftPrePointUp = std::make_shared<Animation>("Barrel Run Left Pre Point Up");
	{
		barrelRunLeftPrePointUp->SetAnimationFPS(20);
		barrelRunLeftPrePointUp->SetAllowPause(false);
		barrelRunLeftPrePointUp->SetIsLooping(false);
		barrelRunLeftPrePointUp->SetHasExitTime(true);

		keyFrame.rect = prePointUpRect;
		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 48.0f / scaleY, 0.0f };
		barrelRunLeftPrePointUp->AddKeyFrames(keyFrame);

		barrelRunLeftPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRunLeftPrePointUp);
	}

	std::shared_ptr<Animation> barrelRunRightPointUp = std::make_shared<Animation>("Barrel Run Right Point Up");
	{
		barrelRunRightPointUp->SetAnimationFPS(20);
		barrelRunRightPointUp->SetAllowPause(false);
		barrelRunRightPointUp->SetIsLooping(false);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x - 19.0f / scaleX, transform->position.y + 61.0f / scaleY, 0.0f };
		barrelRunRightPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRunRightPointUp);
	}

	std::shared_ptr<Animation> barrelRunLeftPointUp = std::make_shared<Animation>("Barrel Run Left Point Up");
	{
		barrelRunLeftPointUp->SetAnimationFPS(20);
		barrelRunLeftPointUp->SetAllowPause(false);
		barrelRunLeftPointUp->SetIsLooping(false);
		keyFrame.scale = leftScale;
		keyFrame.rect = pointUpRect;
		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + 61.0f / scaleY, 0.0f };
		barrelRunLeftPointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(barrelRunLeftPointUp);
	}

	std::shared_ptr<Animation> barrelRightPushDown = std::make_shared<Animation>("Barrel Right Push Down");
	{
		barrelRightPushDown->SetAnimationFPS(12);
		barrelRightPushDown->SetIsLooping(false);
		barrelRightPushDown->SetAllowPause(false);
		barrelRightPushDown->SetHasExitTime(true);

		keyFrame.rect = normRect;

		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 16.0f / scaleY, 0.0f };
		barrelRightPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRightPushDown->AddKeyFrames(keyFrame);
		animationController->AddAnimation(barrelRightPushDown);
	}

	std::shared_ptr<Animation> barrelRightPushDownPrePointUp = std::make_shared<Animation>("Barrel Right Push Down Pre Point Up");
	{
		barrelRightPushDownPrePointUp->SetAnimationFPS(20);
		barrelRightPushDownPrePointUp->SetIsLooping(false);
		barrelRightPushDownPrePointUp->SetAllowPause(false);
		barrelRightPushDownPrePointUp->SetHasExitTime(true);

		keyFrame.rect = prePointUpRect;

		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelRightPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + (16.0f + 24.0f) / scaleY, 0.0f };
		barrelRightPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x, transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelRightPushDownPrePointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(barrelRightPushDownPrePointUp);
	}

	std::shared_ptr<Animation> barrelRightPushDownPointUp = std::make_shared<Animation>("Barrel Right Push Down Point Up");
	{
		barrelRightPushDownPointUp->SetAnimationFPS(12);
		barrelRightPushDownPointUp->SetIsLooping(false);
		barrelRightPushDownPointUp->SetAllowPause(false);
		barrelRightPushDownPointUp->SetHasExitTime(true);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x - 19.0f / scaleX, transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x - 19.0f / scaleX , transform->position.y + (16.0f + 22.0f) / scaleY, 0.0f };
		barrelRightPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x - 19.0f / scaleX ,transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelRightPushDownPointUp->AddKeyFrames(keyFrame);
		animationController->AddAnimation(barrelRightPushDownPointUp);
	}

	std::shared_ptr<Animation> barrelLeftPushDown = std::make_shared<Animation>("Barrel Left Push Down");
	{
		barrelLeftPushDown->SetAnimationFPS(12);
		barrelLeftPushDown->SetIsLooping(false);
		barrelLeftPushDown->SetAllowPause(false);
		barrelLeftPushDown->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 16.0f / scaleY, 0.0f };
		barrelLeftPushDown->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelLeftPushDown->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftPushDown);
	}

	std::shared_ptr<Animation> barrelLeftPushDownPrePointUp = std::make_shared<Animation>("Barrel Left Push Down Pre Point Up");
	{
		barrelLeftPushDownPrePointUp->SetAnimationFPS(20);
		barrelLeftPushDownPrePointUp->SetIsLooping(false);
		barrelLeftPushDownPrePointUp->SetAllowPause(false);
		barrelLeftPushDownPrePointUp->SetHasExitTime(true);

		keyFrame.rect = normRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + (16.0f + 24.0f) / scaleY, 0.0f };
		barrelLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f,transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelLeftPushDownPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftPushDownPrePointUp);
	}

	std::shared_ptr<Animation> barrelLeftPushDownPointUp = std::make_shared<Animation>("Barrel Left Push Down Point Up");
	{
		barrelLeftPushDownPointUp->SetAnimationFPS(12);
		barrelLeftPushDownPointUp->SetIsLooping(false);
		barrelLeftPushDownPointUp->SetAllowPause(false);
		barrelLeftPushDownPointUp->SetHasExitTime(true);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + (16.0f + 22.0f) / scaleY, 0.0f };
		barrelLeftPushDownPointUp->AddKeyFrames(keyFrame);

		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelLeftPushDownPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftPushDownPointUp);
	}

	std::shared_ptr<Animation> barrelRightJumping = std::make_shared<Animation>("Barrel Right Jumping");
	{
		barrelRightJumping->SetAnimationFPS(20);
		keyFrame.scale = rightScale;

		keyFrame.rect = normRect;
		keyFrame.position = { transform->position.x, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelRightJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightJumping);
	}

	std::shared_ptr<Animation> barrelRightJumpingPrePointUp = std::make_shared<Animation>("Barrel Right Jumping Pre Point Up");
	{
		barrelRightJumpingPrePointUp->SetAnimationFPS(20);
		barrelRightJumpingPrePointUp->SetIsLooping(false);
		barrelRightJumpingPrePointUp->SetAllowPause(false);
		barrelRightJumpingPrePointUp->SetHasExitTime(true);
		keyFrame.scale = rightScale;

		keyFrame.rect = prePointUpRect;
		keyFrame.position = { transform->position.x, transform->position.y + (32.0f + 24.0f) / scaleY, 0.0f };
		barrelRightJumpingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightJumpingPrePointUp);
	}

	std::shared_ptr<Animation> barrelRightJumpingPointUp = std::make_shared<Animation>("Barrel Right Jumping Point Up");
	{
		barrelRightJumpingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x - 19.0f / scaleX, transform->position.y + (32.0f + 37.0f) / scaleY, 0.0f };
		barrelRightJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightJumpingPointUp);
	}

	std::shared_ptr<Animation> barrelLeftJumping = std::make_shared<Animation>("Barrel Left Jumping");
	{
		barrelLeftJumping->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelLeftJumping->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftJumping);
	}

	std::shared_ptr<Animation> barrelLeftJumpingPrePointUp = std::make_shared<Animation>("Barrel Left Jumping Pre Point Up");
	{
		barrelLeftJumpingPrePointUp->SetAnimationFPS(20);
		barrelLeftJumpingPrePointUp->SetIsLooping(false);
		barrelLeftJumpingPrePointUp->SetAllowPause(false);
		barrelLeftJumpingPrePointUp->SetHasExitTime(true);

		keyFrame.rect = prePointUpRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + (32.0f + 24.0f) / scaleY, 0.0f };
		barrelLeftJumpingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftJumpingPrePointUp);
	}

	std::shared_ptr<Animation> barrelLeftJumpingPointUp = std::make_shared<Animation>("Barrel Left Jumping Point Up");
	{
		barrelLeftJumpingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + (32.0f + 37.0f) / scaleY, 0.0f };
		barrelLeftJumpingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftJumpingPointUp);
	}

	std::shared_ptr<Animation> barrelRightFalling = std::make_shared<Animation>("Barrel Right Falling");
	{
		barrelRightFalling->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelRightFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightFalling);
	}

	std::shared_ptr<Animation> barrelRightFallingPrePointUp = std::make_shared<Animation>("Barrel Right Falling Pre Point Up");
	{
		barrelRightFallingPrePointUp->SetAnimationFPS(20);
		barrelRightFallingPrePointUp->SetIsLooping(false);
		barrelRightFallingPrePointUp->SetAllowPause(false);
		barrelRightFallingPrePointUp->SetHasExitTime(true);
		keyFrame.rect = prePointUpRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelRightFallingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightFallingPrePointUp);
	}

	std::shared_ptr<Animation> barrelRightFallingPointUp = std::make_shared<Animation>("Barrel Right Falling Point Up");
	{
		barrelRightFallingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x - 19.0f / scaleX, transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelRightFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelRightFallingPointUp);
	}

	std::shared_ptr<Animation> barrelLeftFalling = std::make_shared<Animation>("Barrel Left Falling");
	{
		barrelLeftFalling->SetAnimationFPS(20);

		keyFrame.rect = normRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelLeftFalling->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftFalling);
	}

	std::shared_ptr<Animation> barrelLeftFallingPrePointUp = std::make_shared<Animation>("Barrel Left Falling Pre Point Up");
	{
		barrelLeftFallingPrePointUp->SetAnimationFPS(20);
		barrelLeftFallingPrePointUp->SetIsLooping(false);
		barrelLeftFallingPrePointUp->SetAllowPause(false);
		barrelLeftFallingPrePointUp->SetHasExitTime(true);
		keyFrame.rect = prePointUpRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + (24.0f + 24.0f) / scaleY, 0.0f };
		barrelLeftFallingPrePointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftFallingPrePointUp);
	}

	std::shared_ptr<Animation> barrelLeftFallingPointUp = std::make_shared<Animation>("Barrel Left Falling Point Up");
	{
		barrelLeftFallingPointUp->SetAnimationFPS(20);

		keyFrame.rect = pointUpRect;
		keyFrame.scale = leftScale;

		keyFrame.position = { transform->position.x * -1.0f + 19.0f / scaleX, transform->position.y + (24.0f + 37.0f) / scaleY, 0.0f };
		barrelLeftFallingPointUp->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelLeftFallingPointUp);
	}

	std::shared_ptr<Animation> barrelJumpingTurnLeft = std::make_shared<Animation>("Barrel Jumping Turn Left");
	{
		barrelJumpingTurnLeft->SetAnimationFPS(20);
		barrelJumpingTurnLeft->SetIsLooping(false);
		barrelJumpingTurnLeft->SetHasExitTime(true);
		barrelJumpingTurnLeft->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelJumpingTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelJumpingTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelJumpingTurnLeft);
	}

	std::shared_ptr<Animation> barrelJumpingTurnRight = std::make_shared<Animation>("Barrel Jumping Turn Right");
	{
		barrelJumpingTurnRight->SetAnimationFPS(20);
		barrelJumpingTurnRight->SetIsLooping(false);
		barrelJumpingTurnRight->SetHasExitTime(true);
		barrelJumpingTurnRight->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelJumpingTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelJumpingTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelJumpingTurnRight);
	}

	std::shared_ptr<Animation> barrelFallingTurnLeft = std::make_shared<Animation>("Barrel Falling Turn Left");
	{
		barrelFallingTurnLeft->SetAnimationFPS(20);
		barrelFallingTurnLeft->SetIsLooping(false);
		barrelFallingTurnLeft->SetHasExitTime(true);
		barrelFallingTurnLeft->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelFallingTurnLeft->AddKeyFrames(keyFrame);

		keyFrame.scale = rightScale;
		keyFrame.position = { transform->position.x, transform->position.y + 32.0f / scaleY, 0.0f };
		barrelFallingTurnLeft->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelFallingTurnLeft);
	}

	std::shared_ptr<Animation> barrelFallingTurnRight = std::make_shared<Animation>("Barrel Falling Turn Right");
	{
		barrelFallingTurnRight->SetAnimationFPS(20);
		barrelFallingTurnRight->SetIsLooping(false);
		barrelFallingTurnRight->SetHasExitTime(true);
		barrelFallingTurnRight->SetAllowPause(false);

		keyFrame.rect = { 0, 0, 0, 0 };
		keyFrame.scale = rightScale;

		keyFrame.position = { transform->position.x, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelFallingTurnRight->AddKeyFrames(keyFrame);

		keyFrame.scale = leftScale;
		keyFrame.position = { transform->position.x * -1.0f, transform->position.y + 24.0f / scaleY, 0.0f };
		barrelFallingTurnRight->AddKeyFrames(keyFrame);

		animationController->AddAnimation(barrelFallingTurnRight);
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
		animationController->GetAnimationIndex(barrelRunRight),
		animationController->GetAnimationIndex(barrelTurnLeft));
	{
		rightToTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightToTurnLeftTrans);
	}

	std::shared_ptr<Transition> turnLeftToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelTurnLeft),
		animationController->GetAnimationIndex(barrelRunLeft));
	{
		animationController->AddTransition(turnLeftToLeftTrans);
	}

	std::shared_ptr<Transition> leftToTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeft),
		animationController->GetAnimationIndex(barrelTurnRight));
	{
		leftToTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftToTurnRightTrans);
	}

	std::shared_ptr<Transition> turnRightToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelTurnRight),
		animationController->GetAnimationIndex(barrelRunRight));
	{
		animationController->AddTransition(turnRightToRightTrans);
	}

	std::shared_ptr<Transition> rightToRightPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRight),
		animationController->GetAnimationIndex(barrelRunRightPrePointUp));
	{
		rightToRightPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightToRightPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPrePointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRightPrePointUp),
		animationController->GetAnimationIndex(barrelRunRightPointUp));
	{
		rightPrePointUpToRightPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPrePointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightPointUpToRightPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRightPointUp),
		animationController->GetAnimationIndex(barrelRunRightPrePointUp));
	{
		rightPointUpToRightPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPointUpToRightPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPrePointUpToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRightPrePointUp),
		animationController->GetAnimationIndex(barrelRunRight));
	{
		rightPrePointUpToRightTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPrePointUpToRightTrans);
	}

	std::shared_ptr<Transition> leftToLeftPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeft),
		animationController->GetAnimationIndex(barrelRunLeftPrePointUp));
	{
		leftToLeftPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftToLeftPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPrePointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeftPrePointUp),
		animationController->GetAnimationIndex(barrelRunLeftPointUp));
	{
		leftPrePointUpToLeftPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPrePointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPointUpToLeftPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeftPointUp),
		animationController->GetAnimationIndex(barrelRunLeftPrePointUp));
	{
		leftPointUpToLeftPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPointUpToLeftPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPrePointUpToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeftPrePointUp),
		animationController->GetAnimationIndex(barrelRunLeft));
	{
		leftPrePointUpToLeftTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPrePointUpToLeftTrans);
	}

	std::shared_ptr<Transition> rightPointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRightPointUp),
		animationController->GetAnimationIndex(barrelRunLeftPointUp));
	{
		rightPointUpToLeftPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightPointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeftPointUp),
		animationController->GetAnimationIndex(barrelRunRightPointUp));
	{
		leftPointUpToRightPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftPointUpToRightPointUpTrans);
	}

	std::shared_ptr<Transition> rightToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRight),
		animationController->GetAnimationIndex(barrelRightPushDown));
	{
		rightToRightPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDown),
		animationController->GetAnimationIndex(barrelRightJumping));
	{
		rightPushDownToRightJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumping),
		animationController->GetAnimationIndex(barrelRightFalling));
	{
		rightJumpingToRightFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingToRightFallingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFalling),
		animationController->GetAnimationIndex(barrelRightPushDown));
	{
		rightFallingToRightPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightPushDownToRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDown),
		animationController->GetAnimationIndex(barrelRunRight));
	{
		rightPushDownToRightTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightPushDownToRightTrans);
	}

	std::shared_ptr<Transition> rightPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunRightPointUp),
		animationController->GetAnimationIndex(barrelRightPushDownPointUp));
	{
		rightPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(rightPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDownPointUp),
		animationController->GetAnimationIndex(barrelRightJumpingPointUp));
	{
		rightPushDownPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(rightPushDownPointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumpingPointUp),
		animationController->GetAnimationIndex(barrelRightFallingPointUp));
	{
		rightJumpingPointUpToRightFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(rightJumpingPointUpToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFallingPointUp),
		animationController->GetAnimationIndex(barrelRightPushDownPointUp));
	{
		rightFallingPointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDownPointUp),
		animationController->GetAnimationIndex(barrelRunRightPointUp));
	{
		rightPushDownPointUpToRightPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(rightPushDownPointUpToRightPointUpTrans);
	}


	std::shared_ptr<Transition> rightPushDownToRightPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDown),
		animationController->GetAnimationIndex(barrelRightPushDownPrePointUp));
	{
		rightPushDownToRightPushDownPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPushDownToRightPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPrePointUpToRightPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDownPrePointUp),
		animationController->GetAnimationIndex(barrelRightPushDownPointUp));
	{
		rightPushDownPrePointUpToRightPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightPushDownPrePointUpToRightPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPointUpToRightPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDownPointUp),
		animationController->GetAnimationIndex(barrelRightPushDownPrePointUp));
	{
		rightPushDownPointUpToRightPushDownPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPushDownPointUpToRightPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightPushDownPrePointUpToRightPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightPushDownPrePointUp),
		animationController->GetAnimationIndex(barrelRightPushDown));
	{
		rightPushDownPrePointUpToRightPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightPushDownPrePointUpToRightPushDownTrans);
	}

	std::shared_ptr<Transition> rightJumpingToRightJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumping),
		animationController->GetAnimationIndex(barrelRightJumpingPrePointUp));
	{
		rightJumpingToRightJumpingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightJumpingToRightJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPrePointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumpingPrePointUp),
		animationController->GetAnimationIndex(barrelRightJumpingPointUp));
	{
		rightJumpingPrePointUpToRightJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightJumpingPrePointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPointUpToRightJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumpingPointUp),
		animationController->GetAnimationIndex(barrelRightJumpingPrePointUp));
	{
		rightJumpingPointUpToRightJumpingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightJumpingPointUpToRightJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightJumpingPrePointUpToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumpingPrePointUp),
		animationController->GetAnimationIndex(barrelRightJumping));
	{
		rightJumpingPrePointUpToRightJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightJumpingPrePointUpToRightJumpingTrans);
	}

	std::shared_ptr<Transition> rightFallingToRightFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFalling),
		animationController->GetAnimationIndex(barrelRightFallingPrePointUp));
	{
		rightFallingToRightFallingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightFallingToRightFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPrePointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFallingPrePointUp),
		animationController->GetAnimationIndex(barrelRightFallingPointUp));
	{
		rightFallingPrePointUpToRightFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(rightFallingPrePointUpToRightFallingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToRightFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFallingPointUp),
		animationController->GetAnimationIndex(barrelRightFallingPrePointUp));
	{
		rightFallingPointUpToRightFallingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightFallingPointUpToRightFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPrePointUpToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFallingPrePointUp),
		animationController->GetAnimationIndex(barrelRightFalling));
	{
		rightFallingPrePointUpToRightFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(rightFallingPrePointUpToRightFallingTrans);
	}

	std::shared_ptr<Transition> leftToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeft),
		animationController->GetAnimationIndex(barrelLeftPushDown));
	{
		leftToLeftPushDownTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDown),
		animationController->GetAnimationIndex(barrelLeftJumping));
	{
		leftPushDownToLeftJumpingTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumping),
		animationController->GetAnimationIndex(barrelLeftFalling));
	{
		leftJumpingToLeftFallingTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingToLeftFallingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFalling),
		animationController->GetAnimationIndex(barrelLeftPushDown));
	{
		leftFallingToLeftPushDownTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDown),
		animationController->GetAnimationIndex(barrelRunLeft));
	{
		leftPushDownToLeftTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftPushDownToLeftTrans);
	}

	std::shared_ptr<Transition> leftPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRunLeftPointUp),
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp));
	{
		leftPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(jumpingBoolCond);
		animationController->AddTransition(leftPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp),
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp));
	{
		leftPushDownPointUpToLeftJumpingPointUpTrans->AddFloatTransitionCondition(jumpingFloatCond);
		animationController->AddTransition(leftPushDownPointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp),
		animationController->GetAnimationIndex(barrelLeftFallingPointUp));
	{
		leftJumpingPointUpToLeftFallingPointUpTrans->AddFloatTransitionCondition(fallingFloatCond);
		animationController->AddTransition(leftJumpingPointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFallingPointUp),
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp));
	{
		leftFallingPointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp),
		animationController->GetAnimationIndex(barrelRunLeftPointUp));
	{
		leftPushDownPointUpToLeftPointUpTrans->AddBoolTransitionCondition(fallingBoolCond);
		animationController->AddTransition(leftPushDownPointUpToLeftPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownToLeftPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDown),
		animationController->GetAnimationIndex(barrelLeftPushDownPrePointUp));
	{
		leftPushDownToLeftPushDownPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPushDownToLeftPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPrePointUpToLeftPushDownPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDownPrePointUp),
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp));
	{
		leftPushDownPrePointUpToLeftPushDownPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftPushDownPrePointUpToLeftPushDownPointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPointUpToLeftPushDownPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDownPointUp),
		animationController->GetAnimationIndex(barrelLeftPushDownPrePointUp));
	{
		leftPushDownPointUpToLeftPushDownPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPushDownPointUpToLeftPushDownPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftPushDownPrePointUpToLeftPushDownTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftPushDownPrePointUp),
		animationController->GetAnimationIndex(barrelLeftPushDown));
	{
		leftPushDownPrePointUpToLeftPushDownTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftPushDownPrePointUpToLeftPushDownTrans);
	}

	std::shared_ptr<Transition> leftJumpingToLeftJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumping),
		animationController->GetAnimationIndex(barrelLeftJumpingPrePointUp));
	{
		leftJumpingToLeftJumpingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftJumpingToLeftJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPrePointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumpingPrePointUp),
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp));
	{
		leftJumpingPrePointUpToLeftJumpingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftJumpingPrePointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToLeftJumpingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp),
		animationController->GetAnimationIndex(barrelLeftJumpingPrePointUp));
	{
		leftJumpingPointUpToLeftJumpingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftJumpingPointUpToLeftJumpingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPrePointUpToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumpingPrePointUp),
		animationController->GetAnimationIndex(barrelLeftJumping));
	{
		leftJumpingPrePointUpToLeftJumpingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftJumpingPrePointUpToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftFallingToLeftFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFalling),
		animationController->GetAnimationIndex(barrelLeftFallingPrePointUp));
	{
		leftFallingToLeftFallingPrePointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftFallingToLeftFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPrePointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFallingPrePointUp),
		animationController->GetAnimationIndex(barrelLeftFallingPointUp));
	{
		leftFallingPrePointUpToLeftFallingPointUpTrans->AddBoolTransitionCondition(pointUpBoolCond);
		animationController->AddTransition(leftFallingPrePointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToLeftFallingPrePointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFallingPointUp),
		animationController->GetAnimationIndex(barrelLeftFallingPrePointUp));
	{
		leftFallingPointUpToLeftFallingPrePointUpTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftFallingPointUpToLeftFallingPrePointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPrePointUpToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFallingPrePointUp),
		animationController->GetAnimationIndex(barrelLeftFalling));
	{
		leftFallingPrePointUpToLeftFallingTrans->AddBoolTransitionCondition(backFromPointUpBoolCond);
		animationController->AddTransition(leftFallingPrePointUpToLeftFallingTrans);
	}




	std::shared_ptr<Transition> rightJumpingToJumpingTurnLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumping),
		animationController->GetAnimationIndex(barrelJumpingTurnLeft));
	{
		rightJumpingToJumpingTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightJumpingToJumpingTurnLeftTrans);
	}

	std::shared_ptr<Transition> jumpingTurnLeftToLeftJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelJumpingTurnLeft),
		animationController->GetAnimationIndex(barrelLeftJumping));
	{
		animationController->AddTransition(jumpingTurnLeftToLeftJumpingTrans);
	}

	std::shared_ptr<Transition> leftJumpingToJumpingTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumping),
		animationController->GetAnimationIndex(barrelJumpingTurnRight));
	{
		leftJumpingToJumpingTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftJumpingToJumpingTurnRightTrans);
	}

	std::shared_ptr<Transition> jumpingTurnRightToRightJumpingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelJumpingTurnRight),
		animationController->GetAnimationIndex(barrelRightJumping));
	{
		animationController->AddTransition(jumpingTurnRightToRightJumpingTrans);
	}


	std::shared_ptr<Transition> rightFallingToFallingTurnLeftTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFalling),
		animationController->GetAnimationIndex(barrelFallingTurnLeft));
	{
		rightFallingToFallingTurnLeftTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightFallingToFallingTurnLeftTrans);
	}


	std::shared_ptr<Transition> fallingTurnLeftToLeftFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelFallingTurnLeft),
		animationController->GetAnimationIndex(barrelLeftFalling));
	{
		animationController->AddTransition(fallingTurnLeftToLeftFallingTrans);
	}


	std::shared_ptr<Transition> leftFallingToFallingTurnRightTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFalling),
		animationController->GetAnimationIndex(barrelFallingTurnRight));
	{
		leftFallingToFallingTurnRightTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftFallingToFallingTurnRightTrans);
	}

	std::shared_ptr<Transition> fallingTurnRightToRightFallingTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelFallingTurnRight),
		animationController->GetAnimationIndex(barrelRightFalling));
	{
		animationController->AddTransition(fallingTurnRightToRightFallingTrans);
	}


	std::shared_ptr<Transition> rightJumpingPointUpToLeftJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightJumpingPointUp),
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp));
	{
		rightJumpingPointUpToLeftJumpingPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightJumpingPointUpToLeftJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> leftJumpingPointUpToRightJumpingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftJumpingPointUp),
		animationController->GetAnimationIndex(barrelRightJumpingPointUp));
	{
		leftJumpingPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftJumpingPointUpToRightJumpingPointUpTrans);
	}

	std::shared_ptr<Transition> rightFallingPointUpToLeftFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelRightFallingPointUp),
		animationController->GetAnimationIndex(barrelLeftFallingPointUp));
	{
		rightFallingPointUpToLeftFallingPointUpTrans->AddFloatTransitionCondition(rightToLeftFloatCond);
		animationController->AddTransition(rightFallingPointUpToLeftFallingPointUpTrans);
	}

	std::shared_ptr<Transition> leftFallingPointUpToRightFallingPointUpTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(barrelLeftFallingPointUp),
		animationController->GetAnimationIndex(barrelRightFallingPointUp));
	{
		leftJumpingPointUpToRightJumpingPointUpTrans->AddFloatTransitionCondition(leftToRightFloatCond);
		animationController->AddTransition(leftFallingPointUpToRightFallingPointUpTrans);
	}
}