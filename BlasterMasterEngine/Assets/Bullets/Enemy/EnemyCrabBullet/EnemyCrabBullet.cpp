#include "d3dpch.h"
#include "EnemyCrabBullet.h"

EnemyCrabBullet::EnemyCrabBullet(float x, float y)
	: Bullet(x, y)
{
	name = "EnemyCrabBullet";
	tag = Tag::EnemyBullet;
	animationController = GetComponent<AnimationController>();

}

void EnemyCrabBullet::CreateResources()
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

void EnemyCrabBullet::Start()
{
	horizontalMove = (float)(rand() % defaultBulletSpeed + 0) - (float)defaultBulletSpeed/2; //ANGLE OF BULLETS DEPENDS ON THE RANGE OF RNG
	verticalMove = - sqrt(pow(defaultBulletSpeed, 2) - pow(horizontalMove, 2));
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 6.0f, 6.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 1;
}

void EnemyCrabBullet::Update()
{
	rigidbody->velocity.x = horizontalMove * flyMultiplier * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * flyMultiplier * Time::GetFixedDeltaTime();
}