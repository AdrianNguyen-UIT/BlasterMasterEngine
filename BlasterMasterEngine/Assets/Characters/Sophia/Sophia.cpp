#include "d3dpch.h"
#include "Sophia.h"
#include "Core/SceneManager/SceneManager.h"
Sophia::Sophia(float x, float y)
	: Object2D(x, y)
{
	name = "Shophia";
	tag = Tag::Player;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
}

void Sophia::CreateResources()
{
	{
		leftWheel = std::make_shared<SophiaLeftWheel>(-22.0f, -5.0f);
		leftWheel->CreateResources();
		leftWheel->parentObject = shared_from_this();
		childObjects.emplace_back(leftWheel);
	}

	{
		rightWheel = std::make_shared<SophiaRightWheel>(22.0f, -5.0f);
		rightWheel->CreateResources();
		rightWheel->parentObject = shared_from_this();
		childObjects.emplace_back(rightWheel);
	}

	{
		wheelConnector = std::make_shared<SophiaWheelConnector>(0.0f, 0.0f);
		wheelConnector->CreateResources();
		wheelConnector->parentObject = shared_from_this();
		childObjects.emplace_back(wheelConnector);
	}

	{
		cabin = std::make_shared<SophiaCabin>(-10.0f, 0.0f);
		cabin->CreateResources();
		cabin->parentObject = shared_from_this();
		childObjects.emplace_back(cabin);
	}

	{
		barrel = std::make_shared<SophiaBarrel>(24.0f, 0.0f);
		barrel->CreateResources();
		barrel->parentObject = shared_from_this();
		childObjects.emplace_back(barrel);
	}
}	

void Sophia::Start()
{
	runSpeed = 300.0f;
	horizontalMove = 0.0f;
	isFacingRight = true;
	pointUp = false;
	isJumping = false;
	frameBeforeJump = 20;
	frameCount = 0;
	fallMultiplier = 4.5f;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 2.0f;
	rigidbody->bounciness = 0.0f;
	boxCollider->size = { 65.0f, 55.0f };
	boxCollider->offset = { 0.0f, 10.0f };
	boxCollider->isTrigger = false;
}

void Sophia::Update()
{
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
			D3DXVECTOR2 force(0.0f, 1800.0f);
			rigidbody->AddForce(force);
			frameCount = 0;
		}
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