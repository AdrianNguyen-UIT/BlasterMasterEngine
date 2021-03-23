#include "d3dpch.h"
#include "EnemyWalkerBullet.h"


EnemyWalkerBullet::EnemyWalkerBullet(float x, float y, Direction direction, bool pIsLeftAnimation)
	: Bullet(x, y), directionBullet(direction), isLeftAnimation(pIsLeftAnimation)
{
	name = "EnemyWalkerBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();
}

void EnemyWalkerBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 8;
	int spriteHeight = 8;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	if (isLeftAnimation)
	{
		std::shared_ptr<Animation> leftBulletWalker = std::make_shared<Animation>("Left Bullet Walker");
		{
			leftBulletWalker->SetAnimationFPS(10);

			rect.left = 214;
			rect.top = 305;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;

			keyFrame.rect = rect;
			leftBulletWalker->AddKeyFrames(keyFrame);
			animationController->AddAnimation(leftBulletWalker);
			animationController->SetDefaultAnimation(leftBulletWalker);
		}
	}
	
	else
	{
		std::shared_ptr<Animation> rightBulletWalker = std::make_shared<Animation>("Right Bullet Walker");
		{
			rightBulletWalker->SetAnimationFPS(10);

			rect.left = 32;
			rect.top = 305;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;

			keyFrame.rect = rect;
			rightBulletWalker->AddKeyFrames(keyFrame);
			animationController->AddAnimation(rightBulletWalker);
			animationController->SetDefaultAnimation(rightBulletWalker);
		}
	}
}

void EnemyWalkerBullet::Start()
{
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 8.0f, 8.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
	if (directionBullet == Direction::LEFT)
	{
		rigidbody->velocity.x = -defaultBulletSpeed * Time::GetFixedDeltaTime();
		rigidbody->velocity.y = 0;
	}
	else if (directionBullet == Direction::RIGHT)
	{
		rigidbody->velocity.x = defaultBulletSpeed * Time::GetFixedDeltaTime();
		rigidbody->velocity.y = 0;
	}
	else if (directionBullet == Direction::UP)
	{
		rigidbody->velocity.x = 0;
		rigidbody->velocity.y = defaultBulletSpeed * Time::GetFixedDeltaTime();
	}
	else if (directionBullet == Direction::DOWN)
	{
		rigidbody->velocity.x = 0;
		rigidbody->velocity.y = -defaultBulletSpeed * Time::GetFixedDeltaTime();
	}

	damage = 1;
}

void EnemyWalkerBullet::Update()
{
}
