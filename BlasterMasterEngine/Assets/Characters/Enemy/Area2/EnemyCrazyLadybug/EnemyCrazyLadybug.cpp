#include "d3dpch.h"
#include "EnemyCrazyLadybug.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/Characters/Sophia/Sophia.h"
#include "Assets/Characters/Jason/Jason.h"

EnemyCrazyLadybug::EnemyCrazyLadybug(float x, float y, float fdetectingPlayerZoneX, float fdetectingPlayerZoneY, float fdetectRange)
	: Enemy(x, y), detectingPlayerZoneX(fdetectingPlayerZoneX), detectingPlayerZoneY(fdetectingPlayerZoneY)
{
	name = "CrazyLadybug";
	detectRange = fdetectRange;
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
	Enemy::Start();

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
	damage = 1;
	//detectRange = 200.0f;
}

void EnemyCrazyLadybug::Update()
{
	//SPAWN RANGE
	if (!DetectPlayer())
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		spriteRenderer->enable = false;
		return;
	}
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	spriteRenderer->enable = true;


	std::shared_ptr<Object2D> player;
	//FINDING PLAYER
	if (jason == NULL)
	{
		player = sophia;
	}
	else
	{
		player = jason;
	}

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