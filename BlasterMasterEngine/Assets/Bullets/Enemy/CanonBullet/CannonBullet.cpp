#include "d3dpch.h"
#include "CannonBullet.h"

CannonBullet::CannonBullet(Direction pDirection, float x, float y)
	: Bullet(x, y), direction(pDirection)
{
	name = "CannonBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();
}

void CannonBullet::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");

	int spriteWidth = 6;
	int spriteHeight = 6;
	KeyFrame keyFrame;
	RECT rect;
	keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> bulletFly = std::make_shared<Animation>("Bullet Fly");
	{
		bulletFly->SetAnimationFPS(10);

		rect.left = 360;
		rect.top = 164;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;

		keyFrame.rect = rect;
		bulletFly->AddKeyFrames(keyFrame);
		animationController->AddAnimation(bulletFly);
		animationController->SetDefaultAnimation(bulletFly);
	}
}

void CannonBullet::Start()
{
	switch (direction)
	{
	case Direction::UP:
		horizontalMove = 0.0f;
		verticalMove = 40.0f;
		break;
	case Direction::DOWN:
		horizontalMove = 0.0f;
		verticalMove = -40.0f;
		break;
	case Direction::RIGHT:
		horizontalMove = 40.0f;
		verticalMove = 0.0f;
		break;
	case Direction::LEFT:
		horizontalMove = -40.0f;
		verticalMove = 0.0f;
		break;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 6.0f, 6.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };

	damage = 1;
}

void CannonBullet::Update()
{
	rigidbody->velocity.x = horizontalMove * flyMultiplier * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * flyMultiplier * Time::GetFixedDeltaTime();
}