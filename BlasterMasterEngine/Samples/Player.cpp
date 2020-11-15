#include "d3dpch.h"
#include "Player.h"
#include "Bullet.h"
#include "Core/SceneManager/SceneManager.h"
#include "Core/AudioMixer/AudioMixer.h"

Player::Player(float x, float y)
	: Object2D(x, y)
{
	name = "Player";
	tag = Tag::Player;
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
}

void Player::Start()
{
	runSpeed = 300.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;

	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = {25.0f, 30.0f};
	boxCollider->isTrigger = false;
}

void Player::Update()
{
	std::shared_ptr<OrthographicCamera> camera = SceneManager::GetActiveScene()->GetActiceCamaera();

	static bool firstPlay = false;
	if (!firstPlay)
	{
		//AudioMixer::PlayWaveFile("BGM", true);
		firstPlay = true;
	}

	if (Input::GetKey(KeyCode_D))
	{
		horizontalMove = 1.0f * runSpeed;
	}
	else if (Input::GetKey(KeyCode_A))
	{
		horizontalMove = -1.0f * runSpeed;
	}
	else
	{
		horizontalMove = 0.0f;
	}
	if (Input::GetKeyDown(KeyCode_SPACE) && downCollision != 0)
	{
		D3DXVECTOR2 force(0.0f, 1000.0f);
		rigidbody->AddForce(force);
	}

	rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();
	if (horizontalMove > 0 && !isFacingRight)
	{
		Flip();
	}
	else if (horizontalMove < 0 && isFacingRight)
	{
		Flip();
	}

	float distanceXBetweenCamPlay = transform->position.x - camera->GetPosition().x;
	LOG_INFO("camera x {0}", camera->GetPosition().x);
	if (distanceXBetweenCamPlay <= 200.0f)
	{
		camera->SetPosition(transform->position.x - 200.0f, camera->GetPosition().y, 0.0f);
	}
	else if (distanceXBetweenCamPlay >= 600.0f && camera->GetPosition().x < 2048 - 100)
	{
		camera->SetPosition(transform->position.x - 600.0f, camera->GetPosition().y, 0.0f);
	}

	/*float distanceYBetweenCamPlay = abs(camera->GetPosition().y - transform->position.y);
	if (distanceYBetweenCamPlay <= 200.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + 400.0f, 0.0f);
	}
	else if (distanceYBetweenCamPlay >= 600.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + 200.0f, 0.0f);
	}*/

	animationController->SetFloat("runSpeed", abs(horizontalMove));

	if (Input::GetKeyDown(KeyCode_C))
	{

		SceneManager::DestroyObject(shared_from_this());
	}

	if (Input::GetKeyDown(KeyCode_V))
	{
		copy = std::make_shared<Bullet>();
		copy->name = "bullet";
		copy->spriteRenderer->sprite = DeviceResources::LoadTexture(TEXTURE_PATH, 0);
		copy->CreateResources();
		D3DXVECTOR3 location = { transform->position.x + 30, transform->position.y + 40, 0.0f };
		SceneManager::Instantiate(copy, location);
	}
}

void Player::CreateResources()
{
	int spriteWidth = 32;
	int spriteHeight = 32;
	int xOffset = 6;
	int yOffset = 6;

	//Create Idle Animation
	std::shared_ptr<Animation> playerIdle = std::make_shared<Animation>("Player_Idle");
	playerIdle->SetAnimationFPS(6);
	for (size_t index = 0; index < 4; index++)
	{
		RECT rect;
		rect.left = (int)index * (spriteWidth + xOffset);
		rect.top = spriteHeight + yOffset;
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		KeyFrame keyFrame;
		keyFrame.rect = rect;
		playerIdle->AddKeyFrames(keyFrame);
	}
	animationController->AddAnimation(playerIdle);
	animationController->SetDefaultAnimation(playerIdle);

	//Create Run Animation
	std::shared_ptr<Animation> playerRun = std::make_shared<Animation>("Player_Run");
	playerRun->SetAnimationFPS(12);

	for (size_t index = 0; index < 10; index++)
	{
		RECT rect;
		rect.left = (int)index * (spriteWidth + xOffset);
		rect.top = 5 * (spriteHeight + yOffset);
		rect.right = rect.left + spriteWidth;
		rect.bottom = rect.top + spriteHeight;
		KeyFrame keyFrame;
		keyFrame.rect = rect;
		playerRun->AddKeyFrames(keyFrame);
	}
	animationController->AddAnimation(playerRun);

	//Add parameter of type float: runSpeed
	std::shared_ptr<Parameter<float>> runSpeed = std::make_shared<Parameter<float>>("runSpeed");
	animationController->AddFloatParameter(runSpeed);

	//Create IdleToRun Transition
	std::shared_ptr<TransitionCondition<float>> idleToRunFloatCond = std::make_shared<TransitionCondition<float>>();
	idleToRunFloatCond->parameter = runSpeed;
	idleToRunFloatCond->condition = Condition::Greater;
	idleToRunFloatCond->value = 0.01f;

	std::shared_ptr<Transition> idleToRunTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(playerIdle),
		animationController->GetAnimationIndex(playerRun));
	idleToRunTrans->AddFloatTransitionCondition(idleToRunFloatCond);

	animationController->AddTransition(idleToRunTrans);

	//Create RunToIdle Transition
	std::shared_ptr<TransitionCondition<float>> runToIdleFloatCond = std::make_shared<TransitionCondition<float>>();
	runToIdleFloatCond->parameter = runSpeed;
	runToIdleFloatCond->condition = Condition::Less;
	runToIdleFloatCond->value = 0.01f;

	std::shared_ptr<Transition> runToIdleTrans = std::make_shared<Transition>(
		animationController->GetAnimationIndex(playerRun),
		animationController->GetAnimationIndex(playerIdle));

	runToIdleTrans->AddFloatTransitionCondition(runToIdleFloatCond);

	animationController->AddTransition(runToIdleTrans);
}

void Player::OnCollisionEnter()
{
	//LOG_INFO("Player: Collide!");
}

void Player::OnTriggerEnter()
{
	//LOG_INFO("Player: Collide - Trigger!");
}

void Player::Flip()
{
	isFacingRight = !isFacingRight;
	transform->Scale(isFacingRight ? 1.0f : -1.0f, 1.0f, 0.0f);
}