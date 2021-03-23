#include "d3dpch.h"
#include "EnemyGuardianBullet.h"

EnemyGuardianBullet::EnemyGuardianBullet(float x, float y, Direction direction)
	: Bullet(x, y), directionBullet(direction)
{
	name = "EnemyGuardianBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();
}

void EnemyGuardianBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");

	int spriteWidth = 8;
	int spriteHeight = 8;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> bulletGuardian = std::make_shared<Animation>("Bullet Guardian");
	{
		bulletGuardian->SetAnimationFPS(10);

		rect.left = 359;
		rect.top = 113;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		bulletGuardian->AddKeyFrames(keyFrame);
		animationController->AddAnimation(bulletGuardian);
		animationController->SetDefaultAnimation(bulletGuardian);
	}
}

void EnemyGuardianBullet::Start()
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

void EnemyGuardianBullet::Update()
{
}
