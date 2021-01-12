#include "d3dpch.h"
#include "EnemyCrazyLadybug.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyCrazyLadybug::EnemyCrazyLadybug(float x, float y, float fdetectingPlayerZoneX, float fdetectingPlayerZoneY)
	: Enemy(x, y)
{
	name = "CrazyLadybug";
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	detectingPlayerZoneX = fdetectingPlayerZoneX;
	detectingPlayerZoneY = fdetectingPlayerZoneY;
}

void EnemyCrazyLadybug::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Texture");

	int spriteWidth = 18;
	int spriteHeight = 18;
	KeyFrame keyFrame;
	RECT rect;
	//keyFrame.position = transform->position;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> crazyLadybugSpinning = std::make_shared<Animation>("Crazy Ladybug Spinning");
	{
		crazyLadybugSpinning->SetAnimationFPS(16);
		for (int index = 1; index < 6; index++)
		{
			rect.left = 78 + ((index - 1) * spriteWidth) + (index - 1) * 2;
			rect.top = 387;
			rect.right = rect.left + spriteWidth;
			rect.bottom = rect.top + spriteHeight;
			keyFrame.rect = rect;
			crazyLadybugSpinning->AddKeyFrames(keyFrame);
		}
		animationController->AddAnimation(crazyLadybugSpinning);
		animationController->SetDefaultAnimation(crazyLadybugSpinning);
	}
}

void EnemyCrazyLadybug::Start()
{
	isFacingRight = true;
	isNearPlayer = false;
	playerIsOutRange = false;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 18.0f, 18.0f };
	boxCollider->offset = { 0.0f, 0.0f };
	boxCollider->isTrigger = false;
	transform->scale = { 3.0f, 3.0f, 3.0f };
	damage = 0;
	detectRange = 150.0f;
}

void EnemyCrazyLadybug::Update()
{
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;

	//DETECTING SOPHIA(PLAYER) THE TANK 
	player = SceneManager::GetActiveScene()->FinObjectByName("Sophia");
	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
	}
	else
	{
		isNearPlayer = false;
	}


	//MOVEMENT AND ATTACK
	if (isNearPlayer == true)
	{
		playerIsOutRange = false;
		float A = (player->transform->position.x - transform->position.x);
		float B = (player->transform->position.y - transform->position.y);
		horizontalMove = followingPlayerMultiplier * ((A * defaultFollowingPlayerSpeed) / (float)(sqrt((float)pow(A, 2) + (float)pow(B, 2))));
		verticalMove = followingPlayerMultiplier * ((B * defaultFollowingPlayerSpeed) / (float)(sqrt((float)pow(A, 2) + (float)pow(B, 2))));
	} 
	else
	{
		verticalMove = 0.0f;

		if (playerIsOutRange == false)
		{
			if (transform->position.x - player->transform->position.x > 0)
			{
				horizontalMove = -defaultHorizontalMove;
			}
			else
			{
				horizontalMove = defaultHorizontalMove;
			}
			playerIsOutRange = true;
		}

		if (leftCollision != 0 || rightCollision != 0)
		{
			horizontalMove = -horizontalMove;
		}
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	rigidbody->velocity.y = verticalMove * Time::GetFixedDeltaTime();
}

void EnemyCrazyLadybug::OnCollisionStay(std::shared_ptr<Object2D> object)
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
		
		Die();
	}
}

void EnemyCrazyLadybug::OnTriggerEnter(std::shared_ptr<Object2D> object)
{
}

void EnemyCrazyLadybug::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? -3.0f : 3.0f, 3.0f, 0.0f);
}