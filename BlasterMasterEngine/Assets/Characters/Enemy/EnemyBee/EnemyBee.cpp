#include "d3dpch.h"
#include "EnemyBee.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Core/SpriteResources/SpriteResources.h"
EnemyBee::EnemyBee(float x, float y, float fHorizontalMoveRange)
	: Enemy(x, y)
{
	name = "Bee";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	horizontalMoveRange = fHorizontalMoveRange;
}

void EnemyBee::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 19;
	int spriteHeight = 18;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> beeFly = std::make_shared<Animation>("Bee Fly");
	{
		beeFly->SetAnimationFPS(18);
		for (int index = 1; index < 3; index++)
		{
			rect.left = 84 + ((index - 1) * spriteWidth) +(index - 1);
			rect.top = 530;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			beeFly->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(beeFly);
		animationController->SetDefaultAnimation(beeFly);
	}
}

void EnemyBee::Start()
{
	horizontalMove = 0.0f;
	isFacingRight = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 19.0f, 18.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	beginningY = 0.0f;
	beginningX = 0.0f;
	detectRange = 150.0f;
	damage = 0;
}

void EnemyBee::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;
	//LOG_INFO("{0}", verticalMove);

	//BENGINNING POSITION SAVING
	if (beginningY == 0.0f)
	{
		beginningY = transform->position.y;
	}
	if (beginningX == 0.0f)
	{
		beginningX = transform->position.x;
	}


	//MOVEMENT
	if (transform->position.y <= beginningY - verticalMoveRange)
	{
		if (transform->position.x <= beginningX - horizontalMoveRange || transform->position.x >= beginningX + horizontalMoveRange)
		{
			horizontalMove = -horizontalMove;
		}

		if (horizontalMove > 0)
		{
			horizontalMove = 23.0f;
		}
		else
		{
			horizontalMove = -23.0f;
		}
		verticalMove = 4*verticalMoveRange;
	}
	else if (transform->position.y == beginningY)
	{
		if (horizontalMove > 0)
		{
			horizontalMove = 7.0f;
		}
		else
		{
			horizontalMove = -7.0f;
		}
		verticalMove = -15.0f;
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();


	//FLIP COND
	if (horizontalMove > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (horizontalMove < 0 && isFacingRight)
	{
		Flip();
	}
}

void EnemyBee::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<Sophia> sophia = std::dynamic_pointer_cast<Sophia>(object);
		if (sophia != NULL)
		{
			sophia->TakeDamage(damage);
		}

		std::shared_ptr<Jason> jason = std::dynamic_pointer_cast<Jason>(object);
		if (jason != NULL)
		{
			jason->TakeDamage(damage);
		}
	}
}

void EnemyBee::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyBee::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}
