#include "d3dpch.h"
#include "Sophia.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/CameraBound.h"
#include "Assets/Particles/PlayerDeadExplosion.h"
#include "Assets/Characters/Jason/Jason.h"
#include "Assets/Characters/PlayerHealth.h"

Sophia::Sophia(float x, float y)
	: Object2D(x, y)
{
	name = "Sophia";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
}

void Sophia::CreateResources()
{
	float scaleX = WINDOW_CAMERA_SCALE_X;
	float scaleY = WINDOW_CAMERA_SCALE_Y;
	{
		leftWheel = std::make_shared<SophiaLeftWheel>((-22.0f / scaleX), -(5.0f / scaleY));
		leftWheel->CreateResources();
		leftWheel->parentObject = shared_from_this();
		childObjects.emplace_back(leftWheel);
	}

	{
		rightWheel = std::make_shared<SophiaRightWheel>(22.0f / scaleX, -(5.0f / scaleY));
		rightWheel->CreateResources();
		rightWheel->parentObject = shared_from_this();
		childObjects.emplace_back(rightWheel);
	}

	{
		wheelConnector = std::make_shared<SophiaWheelConnector>(0.0f / scaleX, 0.0f / scaleY);
		wheelConnector->CreateResources();
		wheelConnector->parentObject = shared_from_this();
		childObjects.emplace_back(wheelConnector);
	}

	{
		cabin = std::make_shared<SophiaCabin>(-10.0f / scaleX, 0.0f / scaleY);
		cabin->CreateResources();
		cabin->parentObject = shared_from_this();
		childObjects.emplace_back(cabin);
	}

	{
		barrel = std::make_shared<SophiaBarrel>(24.0f / scaleX, 0.0f / scaleY);
		barrel->CreateResources();
		barrel->parentObject = shared_from_this();
		childObjects.emplace_back(barrel);
	}
}	

void Sophia::Start()
{
	runSpeed = 80.0f;
	speedMulti = 0.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	pointUp = false;
	isJumping = false;
	fallMultiplier = 0.3f;
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	rigidbody->gravityScale = 1.0f;
	rigidbody->bounciness = 0.0f;
	rigidbody->mass = 3.0f;
	boxCollider->size = { 20.0f, 20.0f };
	boxCollider->offset = { 0.0f, 5.0f };
	boxCollider->isTrigger = false;
	camera = SceneManager::GetActiveScene()->GetActiceCamera();
	state = State::Normal;
	iFrame = false;
	timeBeforLoadScreen = 0.0f;
	allowToLoad = true;
	RECT rect = { 0, 0, 0, 0 };
	rect.left = (LONG)boxCollider->topLeft.x;
	rect.top = (LONG)(SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y);
	rect.right = (LONG)(rect.left + boxCollider->size.width);
	rect.bottom = (LONG)(rect.top + boxCollider->size.height);

	CameraBound::SetCurrentBound(rect);
	iFrameColors[0] = {0, 255, 0, 255};
	iFrameColors[1] = {255, 51, 0, 255};
	iFrameColors[2] = {255, 255, 255, 255};
	iFrameColors[3] = {255, 204, 255, 2255};

	color = iFrameColors[2];
}

void Sophia::Update()
{
	if (CharacterController::GetCharacterInControl() == Character::Sophia)
	{
		rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
		boxCollider->isTrigger = false;
		if (state == State::Normal)
		{
			static bool jump = false;

			if (Input::GetKey(KeyCode_W))
			{
				pointUp = true;
			}
			else
			{
				pointUp = false;
			}

			if (downCollision != 0)
			{
				if (Input::GetKey(KeyCode_D))
				{
					horizontalMove = 1.0f * runSpeed * speedMulti;
					speedMulti += 0.2f;

				}
				else if (Input::GetKey(KeyCode_A))
				{
					horizontalMove = -1.0f * runSpeed * speedMulti;
					speedMulti += 0.2f;
				}
				else
				{
					horizontalMove = (isFacingRight ? 1.0f : -1.0f) * runSpeed * speedMulti;
					speedMulti -= 0.2f;
				}

				if (Input::GetKeyDown(KeyCode_SPACE))
				{
					jump = true;
				}

				if (Input::GetKeyDown(KeyCode_V))
				{
					SpawnJason();
				}

				if (speedMulti > 1.0f)
				{
					speedMulti = 1.0f;
				}
				else if (speedMulti < 0.0f)
				{
					speedMulti = 0.0f;
				}
			}
			else
			{
				speedMulti = 0.4f;
				jump = false;
				if (Input::GetKey(KeyCode_D) && horizontalMove <= 0)
				{
					horizontalMove = 1.0f * runSpeed * speedMulti;
				}
				else if (Input::GetKey(KeyCode_A) && horizontalMove >= 0)
				{
					horizontalMove = -1.0f * runSpeed * speedMulti;
				}
			}

			Jump(jump);

			rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

			if (Input::GetKeyDown(KeyCode_J))
			{
				Shoot();
			}

			if (rigidbody->velocity.y < 0.0f)
			{
				rigidbody->velocity.y += Physic::gravity.y * fallMultiplier * Time::GetFixedDeltaTime();
			}

			if (horizontalMove > 0 && !isFacingRight)
			{
				speedMulti = 0.0f;
				Flip();
			}
			else if (horizontalMove < 0 && isFacingRight)
			{
				speedMulti = 0.0f;
				Flip();
			}

			MoveCameraAccordingly();
			ApplyCameraBound();
		}
		else if (state == State::CheckPointMove)
		{
			rigidbody->velocity.x = (isFacingRight ? 1.0f : -1.0f) * runSpeed * Time::GetFixedDeltaTime();

			camera->MoveCamera(rigidbody->velocity.x * 2.24f, 0.0f, 0.0f);

		}
		else if (state == State::Die)
		{
			rigidbody->bodyType = Rigidbody::BodyType::Static;

			if (timeBeforLoadScreen >= 1.5f && allowToLoad)
			{
				PlayerHealth::SetPlayerLife(PlayerHealth::GetPlayerLife() - 1);
				if (PlayerHealth::GetPlayerLife() < 0)
				{
					SceneManager::ReloadScene("Game Over Screen");
				}
				else
				{
					SceneManager::ReloadScene("Loading Screen");
				}
				timeBeforLoadScreen = 0.0f;
				allowToLoad = false;
			}
			timeBeforLoadScreen += Time::GetDeltaTime();
		}
	}

	SetAnimationParameter();
	DoIFrame();
}

void Sophia::OnCollisionEnter(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Terrain)
	{
		isJumping = false;
	}

	if (object->tag == Tag::CheckPoint)
	{
		pointUp = false;
		state = State::CheckPointMove;
	}
}

void Sophia::OnCollisionStay(std::shared_ptr<Object2D> object)
{
}

void Sophia::OnCollisionExit(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::CheckPoint)
	{
		state = State::Normal;

		RECT rect = { 0, 0, 0, 0 };
		rect.left = (LONG)boxCollider->topLeft.x;
		rect.top = (LONG)(SceneManager::GetActiveScene()->GetMapSize().height - boxCollider->topLeft.y);
		rect.right = (LONG)(rect.left + boxCollider->size.width);
		rect.bottom = (LONG)(rect.top + boxCollider->size.height);

		CameraBound::SetCurrentBound(rect);
	}
}

void Sophia::Flip()
{
	isFacingRight = !isFacingRight;
}

void Sophia::SpawnJason()
{
	horizontalMove = 0.0f;
	pointUp = false;
	D3DXVECTOR3 location = { transform->position.x, transform->position.y + 12.0f, 0.0f};
	std::shared_ptr<Object2D> jason = std::make_shared<Jason>(location.x, location.y);
	jason->CreateResources();
	SceneManager::Instantiate(jason, location, false);
	CharacterController::SetCharacterInControl(Character::Jason);
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	boxCollider->isTrigger = true;
}

void Sophia::Shoot()
{
	std::shared_ptr<Object2D> bullet;
	if (pointUp)
	{
		bullet = std::make_shared<NormalFireBullet>(transform->position.x, transform->position.y + 10.0f, false, isFacingRight);
	}
	else
	{
		bullet = std::make_shared<NormalFireBullet>(transform->position.x, transform->position.y + 10.0f, true, isFacingRight);
	}
	bullet->CreateResources();
	SceneManager::Instantiate(bullet, bullet->transform->position);
}

void Sophia::Jump(bool& jump)
{
	static float timeLapse = 0.0f;

	if (!jump)
	{
		timeLapse = 0.0f;
		return;
	}

	isJumping = true;

	if (timeLapse >= 0.2f)
	{
		jump = false;

		if (downCollision != 0)
		{
			D3DXVECTOR2 force(0.0f, 850.0f);
			rigidbody->AddForce(force);
		}
		return;
	}
	timeLapse += Time::GetDeltaTime();
}

void Sophia::MoveCameraAccordingly()
{
	float distanceXBetweenCamPlay = transform->position.x - camera->GetPosition().x;

	if (distanceXBetweenCamPlay > (camera->GetSize().width / 2) + 30.0f)
	{
		camera->SetPosition(transform->position.x - (camera->GetSize().width / 2) - 30.0f, camera->GetPosition().y, 0.0f);
	}
	else if (distanceXBetweenCamPlay < (camera->GetSize().width / 2) - 30.0f)
	{
		camera->SetPosition(transform->position.x - (camera->GetSize().width / 2) + 30.0f, camera->GetPosition().y, 0.0f);
	}

	RECT currentBound = CameraBound::GetCurrentBound();
	if (currentBound.bottom - currentBound.top < 300.0f)
		return;

	float distanceYBetweenCamPlay = camera->GetPosition().y - transform->position.y;
	if (distanceYBetweenCamPlay < (camera->GetSize().height / 2) - 30.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + (camera->GetSize().height / 2) - 30.0f, 0.0f);
	}
	else if (distanceYBetweenCamPlay > (camera->GetSize().height / 2) + 30.0f)
	{
		camera->SetPosition(camera->GetPosition().x, transform->position.y + (camera->GetSize().height / 2) + 30.0f, 0.0f);
	}
}

void Sophia::ApplyCameraBound()
{
	if (camera->GetPosition().x < CameraBound::GetCurrentBound().left)
	{
		camera->SetPosition((float)CameraBound::GetCurrentBound().left, camera->GetPosition().y, 0.0f);
	}
	else if (camera->GetPosition().x > CameraBound::GetCurrentBound().right - camera->GetSize().width)
	{
		camera->SetPosition(CameraBound::GetCurrentBound().right - camera->GetSize().width, camera->GetPosition().y, 0.0f);
	}

	float mapHeight = SceneManager::GetActiveScene()->GetMapSize().height;
	if (mapHeight - camera->GetPosition().y < CameraBound::GetCurrentBound().top)
	{
		camera->SetPosition(camera->GetPosition().x, mapHeight - CameraBound::GetCurrentBound().top, 0.0f);
	}
	else if (mapHeight - camera->GetPosition().y > CameraBound::GetCurrentBound().bottom - camera->GetSize().height)
	{
		camera->SetPosition(camera->GetPosition().x, mapHeight - (CameraBound::GetCurrentBound().bottom - camera->GetSize().height), 0.0f);
	}
}

void Sophia::SetAnimationParameter()
{
	if (horizontalMove == 0.0f)
	{
		for (std::shared_ptr<Object2D> object : childObjects)
		{
			object->animationController->PauseAnimation();
		}
	}
	else
	{
		for (std::shared_ptr<Object2D> object : childObjects)
		{
			object->animationController->PlayAnimation(isFacingRight);
		}
	}

	leftWheel->animationController->SetBool("pointUp", pointUp);
	rightWheel->animationController->SetBool("pointUp", pointUp);
	wheelConnector->animationController->SetBool("pointUp", pointUp);
	cabin->animationController->SetBool("pointUp", pointUp);
	barrel->animationController->SetBool("pointUp", pointUp);

	wheelConnector->animationController->SetBool("isJumping", isJumping);
	barrel->animationController->SetBool("isJumping", isJumping);
	cabin->animationController->SetBool("isJumping", isJumping);

	wheelConnector->animationController->SetFloat("verticalVelocity", rigidbody->velocity.y);
	barrel->animationController->SetFloat("verticalVelocity", rigidbody->velocity.y);
	cabin->animationController->SetFloat("verticalVelocity", rigidbody->velocity.y);

	wheelConnector->animationController->SetFloat("runSpeed", horizontalMove);
	cabin->animationController->SetFloat("runSpeed", horizontalMove);
	barrel->animationController->SetFloat("runSpeed", horizontalMove);
}

void Sophia::Die()
{
	std::shared_ptr<Object2D> playerDeadExplosion = std::make_shared<PlayerDeadExplosion>(transform->position.x, transform->position.y + 16.0f);
	playerDeadExplosion->CreateResources();
	SceneManager::Instantiate(playerDeadExplosion, playerDeadExplosion->transform->position);
	for (std::shared_ptr<Object2D> child : childObjects)
	{
		child->enable = false;
	}
	boxCollider->isEnable = false;
	state = State::Die;
}

void Sophia::DoIFrame()
{
	if (iFrame)
	{
		static float iFrameTime = 0.0f;
		static int iFrameColorIndex = 0;

		if (iFrameTime >= 0.45f)
		{
			iFrameTime = 0.0f;
			iFrame = false;
			iFrameColorIndex = 0;
			color = iFrameColors[2];
		}
		else
		{
			color = iFrameColors[iFrameColorIndex];
			++iFrameColorIndex;
			if (iFrameColorIndex > iFrameColors.size() - 1)
			{
				iFrameColorIndex = 0;
			}
			iFrameTime += Time::GetDeltaTime();
		}
	}
}

void Sophia::TakeDamage(int damage)
{
	if (!iFrame)
	{
		int health = PlayerHealth::GetSophiaHealth();
		health -= damage;
		PlayerHealth::SetSophiaHealth(health);
		iFrame = true;

		if (health <= 0)
		{
			PlayerHealth::SetSophiaHealth(0);
			Die();
		}
	}
}