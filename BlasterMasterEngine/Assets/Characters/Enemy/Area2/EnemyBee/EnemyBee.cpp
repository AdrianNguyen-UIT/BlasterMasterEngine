#include "d3dpch.h"
#include "EnemyBee.h"
#include "Core/SpriteResources/SpriteResources.h"
#include "Core/AudioMixer/AudioMixer.h"
EnemyBee::EnemyBee(float x, float y, float fHorizontalMoveRange)
	: Enemy(x, y), horizontalMoveRange(fHorizontalMoveRange)
{
	name = "Bee";
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
	Enemy::Start();

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
	detectRange = 1000.0f;
	allowWalkingAudio = false;
	audioWalkingDelay = 300.0f;

	damage = 1;

	AudioMixer::PlayWaveFile("BEE_FLY", TRUE);
}

void EnemyBee::Update()
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

	if (Time::GetTime() - walkingTime >= audioWalkingDelay && allowWalkingAudio)
	{
		walkingTime = Time::GetTime();
		AudioMixer::PlayWaveFile("BEE_FLY_1", FALSE);
		AudioMixer::SetVolume("BEE_FLY", -2000);
	}

	if (abs((transform->position.x) - player->transform->position.x) <= detectingPlayerZoneX && abs((transform->position.y) - player->transform->position.y) <= detectingPlayerZoneY)
	{
		isNearPlayer = true;
		allowWalkingAudio = true;
	}
	else
	{
		allowWalkingAudio = false;
		isNearPlayer = false;
	}

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
		verticalMove = 4 * verticalMoveRange;
	}
	else if (transform->position.y >= beginningY)
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