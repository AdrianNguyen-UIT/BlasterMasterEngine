#include "d3dpch.h"
#include "TeleporterBullet.h"

TeleporterBullet::TeleporterBullet(float dx, float dy, float x, float y)
	: Bullet(x, y), directionX(dx), directionY(dy)
{
	name = "TeleporterBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();
}

void TeleporterBullet::CreateResources()
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

void TeleporterBullet::Start()
{
	flyMultiplier = 3.0f;
	runSpeed = 40.0f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 6.0f, 6.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };

	damage = 1;
}

void TeleporterBullet::Update()
{
	rigidbody->velocity.x = directionX * runSpeed * flyMultiplier * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = directionY * runSpeed * flyMultiplier * Time::GetFixedDeltaTime();
}