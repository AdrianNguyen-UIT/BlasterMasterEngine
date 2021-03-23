#include "d3dpch.h"
#include "RocketSparkle.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Particles/NormalExplosion.h"

RocketSparkle::RocketSparkle(float x, float y, bool pIsFacingLeft, bool pIsFacingRight, bool pIsFacingTop, bool pIsFacingDown)
	: Object2D(x, y)
{
	name = "Rocket Sparkle Bullet";
	isFacingRight = pIsFacingRight;
	isFacingTop = pIsFacingTop;
	isFacingDown = pIsFacingDown;
	isFacingLeft = pIsFacingLeft;

	tag = Tag::PlayerBullet;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
	animationController = GetComponent<AnimationController>();
}

void RocketSparkle::Start()
{
	horizontalRect = { 225, 103, 232, 116 };
	verticalRect = { 209, 106, 222, 113 };
	boxCollider->size = { 7.0f, 7.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	damage = 3;
	spriteRenderer->rect = horizontalRect;
}

void RocketSparkle::Update()
{
	if (isFacingRight)
	{
		animationController->SetDefaultAnimation(onLeftSide);
	}
	if (isFacingLeft)
	{
		animationController->SetDefaultAnimation(onRightSide);
	}
	if (isFacingTop)
	{

		animationController->SetDefaultAnimation(onTopSide);
	}
	if (isFacingDown)
	{
		LOG_TRACE(isFacingDown);
		animationController->SetDefaultAnimation(onDownSide);
	}
}

void RocketSparkle::CreateResources()
{
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	int spriteWidth = 7;
	int spriteHeight = 13;
	int xOffset = 2;
	int yOffset = 2;
	KeyFrame keyFrame;
	RECT rect;

	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");

	onLeftSide = std::make_shared<Animation>("Left Sparkle");
	{
		onLeftSide->SetAnimationFPS(5);

		for (size_t index = 0; index < 2; ++index)
		{
			rect.left = 225;
			rect.top = 103 + index * spriteHeight;
			rect.right = 232;
			rect.bottom = 116 + index * spriteHeight;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x - 5, transform->position.y ,0.0f };
			keyFrame.scale = { -scaleX / 3, scaleY / 3, 0.0f };
			onLeftSide->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(onLeftSide);
		animationController->SetDefaultAnimation(onLeftSide);
	}

	onRightSide = std::make_shared<Animation>("Right Sparkle");
	{
		onRightSide->SetAnimationFPS(5);

		for (size_t index = 0; index < 2; ++index)
		{
			rect.left = 225;
			rect.top = 103 + index * spriteHeight;
			rect.right = 232;
			rect.bottom = 116 + index * spriteHeight;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x + 5, transform->position.y ,0.0f };
			onRightSide->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(onRightSide);
	}

	onTopSide = std::make_shared < Animation >("TOP Sparkle");
	{
		onTopSide->SetAnimationFPS(5);

		for (size_t index = 0; index < 2; ++index)
		{
			rect.left = 209;
			rect.top = 106 + index * spriteHeight;
			rect.right = 222;
			rect.bottom = 113 + index * spriteHeight;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x, transform->position.y + 5 ,0.0f };
			onTopSide->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(onTopSide);
	}

	onDownSide = std::make_shared < Animation >("DOWN Sparkle");
	{
		onDownSide->SetAnimationFPS(5);

		for (size_t index = 0; index < 2; ++index)
		{
			rect.left = 209;
			rect.top = 106 + index * spriteHeight;
			rect.right = 222;
			rect.bottom = 113 + index * spriteHeight;
			keyFrame.rect = rect;
			keyFrame.position = { transform->position.x + 1, transform->position.y - 5 ,0.0f };
			keyFrame.scale = { -scaleX / 3, scaleY / 3, 0.0f };
			onDownSide->AddKeyFrames(keyFrame);
		}

		animationController->AddAnimation(onDownSide);
	}
}

void RocketSparkle::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void RocketSparkle::Explode()
{
}
