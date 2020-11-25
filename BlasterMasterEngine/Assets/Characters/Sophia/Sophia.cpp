#include "d3dpch.h"
#include "Sophia.h"
#include "Core/SceneManager/SceneManager.h"
#include "Assets/CharacterController.h"
#include "Assets/Characters/Jason/Jason.h"
Sophia::Sophia(float x, float y)
	: Object2D(x, y)
{
	name = "Shophia";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();

	jason = std::make_shared<Jason>();
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

	jason->CreateResources();
}	

void Sophia::Start()
{
	runSpeed = 60.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	pointUp = false;
	isJumping = false;
	frameBeforeJump = 20;
	frameCount = 0;
	fallMultiplier = 1.5f;
	rigidbody->bodyType = Rigidbody::BodyType::Static;
	rigidbody->gravityScale = 2.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 20.0f, 20.0f };
	boxCollider->offset = { 0.0f, 5.0f };
	boxCollider->isTrigger = false;
}

void Sophia::Update()
{
	std::shared_ptr<OrthographicCamera> camera = SceneManager::GetActiveScene()->GetActiceCamaera();
	if (CharacterController::GetCharacterInControl() == Character::Sophia)
	{
		rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
		boxCollider->isTrigger = false;
		static float speedMulti = 0.0f;
		if (downCollision)
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
		}

		if (Input::GetKey(KeyCode_W))
		{
			pointUp = true;
		}
		else
		{
			pointUp = false;
		}
		if (Input::GetKeyDown(KeyCode_SPACE) && downCollision != 0 && frameCount == 0)
		{
			++frameCount;
		}

		if (frameCount != 0)
		{
			++frameCount;
			isJumping = true;
			if (frameCount == frameBeforeJump)
			{
				D3DXVECTOR2 force(0.0f, 1200.0f);
				rigidbody->AddForce(force);
				frameCount = 0;
			}
		}
		if (Input::GetKeyDown(KeyCode_V))
		{

			CharacterController::SetCharacterInControl(Character::Jason);
			D3DXVECTOR3 location = { transform->position.x, transform->position.y + 10.0f, 0.0f };
			SceneManager::Instantiate(jason, location);
		}

		if (speedMulti > 1.0f)
		{
			speedMulti = 1.0f;
		}
		else if (speedMulti < 0.0f)
		{
			speedMulti = 0.0f;
		}

		rigidbody->velocity.x = horizontalMove * Time::GetFixedDeltaTime();

		if (rigidbody->velocity.y < 0.0f)
		{
			rigidbody->velocity.y += Physic::gravity.y * (fallMultiplier - 1) * Time::GetFixedDeltaTime();
		}

		if (horizontalMove == 0.0f)
		{
			for (auto object : childObjects)
			{
				object->animationController->PauseAnimation();
			}
		}
		else
		{
			for (auto object : childObjects)
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

		/*float distanceXBetweenCamPlay = transform->position.x - camera->GetPosition().x;
		LOG_INFO("camera x {0}", camera->GetPosition().x);
		if (distanceXBetweenCamPlay <= 200.0f)
		{
			camera->SetPosition(transform->position.x - 200.0f, camera->GetPosition().y, 0.0f);
		}
		else if (distanceXBetweenCamPlay >= 600.0f && camera->GetPosition().x < 2048 - 100)
		{
			camera->SetPosition(transform->position.x - 600.0f, camera->GetPosition().y, 0.0f);
		}*/

	}
	else if (downCollision != 0)
	{
		rigidbody->bodyType = Rigidbody::BodyType::Static;
		boxCollider->isTrigger = true;
	}

}

void Sophia::OnCollisionEnter()
{
		isJumping = false;
}

void Sophia::OnTriggerEnter()
{
}

void Sophia::Flip()
{
	isFacingRight = !isFacingRight;
}