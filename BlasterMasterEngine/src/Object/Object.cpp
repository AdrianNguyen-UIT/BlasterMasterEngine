#include "d3dpch.h"
#include "Object.h"

Object2D::Object2D(float x, float y)
{
	transform = std::make_shared<Transform>();
	transform->position = { x, y, 0.0f };
	subPosition = {0.0f, 0.0f, 0.0f};
	subRotation = { 0.0f, 0.0f, 0.0f };
	subScale = { 1.0f, 1.0f, 1.0f };
	name = "Object2D";
	tag = Tag::Default;
	enable = true;
	readyToBeDestroy = false;
	upCollision = 0;
	downCollision = 0;
	leftCollision = 0;
	rightCollision = 0;
	layer = Layer::Sophia;
}

void Object2D::Draw(DWORD flags)
{
	if (enable)
	{
		if (spriteRenderer != NULL && spriteRenderer->enable)
		{
			RECT rect = spriteRenderer->rect;
			D3DXVECTOR3 center((float)((rect.right - rect.left) / 2), (float)((rect.bottom - rect.top) / 2), 0.0f);

			spriteRenderer->Begin(flags);
			spriteRenderer->spriteHandler->Draw(
				spriteRenderer->sprite->spriteImage,
				&rect,
				&center,
				NULL,
				D3DCOLOR_RGBA(color.red, color.green, color.blue, color.alpha));
			spriteRenderer->End();
		}
	}

	for (std::shared_ptr<Object2D> object : childObjects)
	{
		object->Draw(flags);
	}
}

void Object2D::InnerUpdate(const D3DXMATRIX& worldToViewportMat)
{
	if (enable)
	{
		Update();

		if (rigidbody != NULL)
		{
			if (rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
			{
				if (downCollision != 0)
				{
					D3DXVECTOR2 groundReactionForce = -1.0f * rigidbody->mass * Physic::gravity * rigidbody->gravityScale;
					rigidbody->AddForce(groundReactionForce);
					rigidbody->velocity.y *= -1.0f * rigidbody->bounciness;
					if (rigidbody->velocity.y < 0.05f)
					{
						rigidbody->velocity.y = 0.0f;
					}
				}

				if (upCollision != 0)
				{
					rigidbody->velocity.y *= -1.0f * rigidbody->bounciness;
					if (rigidbody->velocity.y > -0.05f)
					{
						rigidbody->velocity.y = 0.0f;
					}
				}

				if (rightCollision != 0)
				{
					rigidbody->velocity.x *= -1.0f * rigidbody->bounciness;

					if (rigidbody->velocity.x > -0.05f)
					{
						rigidbody->velocity.x = 0.0f;
					}
				}

				if (leftCollision != 0)
				{
					rigidbody->velocity.x *= -1.0f * rigidbody->bounciness;

					if (rigidbody->velocity.x < 0.05f)
					{
						rigidbody->velocity.x = 0.0f;
					}

				}
				rigidbody->UpdateForce();
				transform->position.x += rigidbody->velocity.x;
				transform->position.y += rigidbody->velocity.y;
			}
			else if (rigidbody->bodyType == Rigidbody::BodyType::Static)
			{
				rigidbody->velocity = { 0.0f, 0.0f };
			}
			else if (rigidbody->bodyType == Rigidbody::BodyType::Kinematic)
			{
				transform->position.x += rigidbody->velocity.x;
				transform->position.y += rigidbody->velocity.y;
			}

			if (boxCollider != NULL && boxCollider->isEnable)
			{
				boxCollider->topLeft = { (transform->position.x - boxCollider->size.width / 2.0f) + boxCollider->offset.x, (transform->position.y + boxCollider->size.height / 2.0f) + boxCollider->offset.y };
			}
		}


		if (spriteRenderer != NULL)
		{
			spriteRenderer->spriteHandler->SetTransform(&transform->GetTransformMatrix());

			if (animationController != NULL && animationController->enable)
			{
				animationController->Update();
				spriteRenderer->rect = animationController->GetCurrentAnimation()->GetCurrentFrameRect();
				subPosition = animationController->GetCurrentAnimation()->GetCurrentFramePosition();
				subRotation = animationController->GetCurrentAnimation()->GetCurrentFrameRotation();
				subScale = animationController->GetCurrentAnimation()->GetCurrentFrameScale();
			}
		}

		if (parentObject != NULL)
		{
			transform->position = parentObject->transform->position + subPosition;
			transform->rotation = parentObject->transform->rotation + subRotation;
			transform->scale.x = parentObject->transform->scale.x * subScale.x;
			transform->scale.y = parentObject->transform->scale.y * subScale.y;
			transform->scale.z = parentObject->transform->scale.z * subScale.z;
			color = parentObject->color;
		}
		else
		{
			transform->position += subPosition;
			transform->rotation += subRotation;
			transform->scale.x *= subScale.x;
			transform->scale.y *= subScale.y;
			transform->scale.z *= subScale.z;
		}

		transform->TranslateWorldToViewport(worldToViewportMat);
		transform->Update();


	}

	for (std::shared_ptr<Object2D> object : childObjects)
	{
		object->InnerUpdate(worldToViewportMat);
	}
}

void Object2D::InnerStart()
{
	if (spriteRenderer != NULL)
	{
		spriteRenderer->InitSpriteRenderer(DeviceResources::GetDevice());
	}

	if (boxCollider != NULL && boxCollider->isEnable)
	{
		boxCollider->topLeft = { (transform->position.x - boxCollider->size.width / 2.0f) + boxCollider->offset.x, (transform->position.y + boxCollider->size.height / 2.0f) + boxCollider->offset.y };
	}

	Start();

	for (std::shared_ptr<Object2D> object : childObjects)
	{
		object->InnerStart();
	}
}

void Object2D::DoCollision(std::shared_ptr<Object2D> object)
{
	if (rigidbody == NULL || object->rigidbody == NULL)
		return;

	if (boxCollider == NULL || object->boxCollider == NULL)
		return;

	if (!boxCollider->isEnable || !object->boxCollider->isEnable)
		return;

	if (tag == Tag::Ladder)
		return;

	if ((tag == Tag::PlayerBullet && object->tag == Tag::PlayerBullet) || 
		(tag == Tag::PlayerBullet && object->tag == Tag::Trap) ||
		(tag == Tag::PlayerBullet && object->tag == Tag::Item) ||
		(tag == Tag::PlayerBullet && object->tag == Tag::Player) || 
		(tag == Tag::PlayerBullet && object->tag == Tag::Ladder))
		return;

	if ((tag == Tag::EnemyBullet && object->tag == Tag::EnemyBullet) ||
		(tag == Tag::EnemyBullet && object->tag == Tag::Trap) ||
		(tag == Tag::EnemyBullet && object->tag == Tag::Item) ||
		(tag == Tag::EnemyBullet && object->tag == Tag::Enemy) ||
		(tag == Tag::EnemyBullet && object->tag == Tag::Ladder))
		return;

	if (tag == Tag::Player && object->tag == Tag::PlayerBullet)
		return;

	if ((tag == Tag::Enemy && object->tag == Tag::Enemy) || 
		(tag == Tag::Enemy && object->tag == Tag::EnemyBullet) ||
		(tag == Tag::Enemy && object->tag == Tag::Ladder))
		return;

	if ((tag == Tag::Trap && object->tag == Tag::PlayerBullet) ||
		(tag == Tag::Trap && object->tag == Tag::EnemyBullet))
		return;

	if ((tag == Tag::Item && object->tag == Tag::PlayerBullet) ||
		(tag == Tag::Trap && object->tag == Tag::EnemyBullet))
		return;

	if (rigidbody->bodyType == Rigidbody::BodyType::Static)
		return;

	if (rigidbody->bodyType == Rigidbody::BodyType::Kinematic &&
		object->rigidbody->bodyType == Rigidbody::BodyType::Kinematic)
		return;

	if (rigidbody->bodyType == Rigidbody::BodyType::Kinematic &&
		object->rigidbody->bodyType == Rigidbody::BodyType::Static)
		return;

	broadphaseBox = GetSweptBroadphaseBox();
	if (CheckCollision(std::make_unique<BoxCollider2D>(broadphaseBox), object->boxCollider))
	{
		for (std::pair<std::shared_ptr<Object2D>, Direction> collidedObject : collidedObjects)
		{
			if (collidedObject.first == object)
			{
				if (boxCollider->isTrigger)
				{
					OnTriggerStay(object);
				}
				else
				{
					OnCollisionStay(object);
				}
				return;
			}
		}

		if (boxCollider->isTrigger)
		{
			collidedObjects.emplace_back(std::make_pair(object, Direction::NONE));

			OnTriggerEnter(object);
		}
		else
		{
			if (object->boxCollider->isTrigger)
			{
				collidedObjects.emplace_back(std::make_pair(object, Direction::NONE));
			}
			else
			{
				Direction direction;
				float collisionTime = SweptAABB(object->boxCollider, direction);

				if (direction == Direction::UP)
				{
					++upCollision;
				}
				else if (direction == Direction::DOWN)
				{
					++downCollision;
				}
				else if (direction == Direction::RIGHT)
				{
					++rightCollision;
				}
				else if (direction == Direction::LEFT)
				{
					++leftCollision;
				}

				collidedObjects.emplace_back(std::make_pair(object, direction));
				transform->position.x += rigidbody->velocity.x * collisionTime;
				transform->position.y += rigidbody->velocity.y * collisionTime;
			}

			OnCollisionEnter(object);
		}
	}
	else
	{
		for (auto it = collidedObjects.begin(); it != collidedObjects.end();)
		{
			if ((*it).first == object)
			{
				if ((*it).second == Direction::UP)
				{
					--upCollision;
				}
				else if ((*it).second == Direction::DOWN)
				{
					--downCollision;
				}
				else if ((*it).second == Direction::LEFT)
				{
					--leftCollision;
				}
				else if ((*it).second == Direction::RIGHT)
				{
					--rightCollision;
				}

				if (boxCollider->isTrigger)
				{
					OnTriggerExit(object);
				}
				else
				{
					OnCollisionExit(object);
				}

				it = collidedObjects.erase(it);
				return;
			}
			else
			{
				++it;
			}
		}
	}
}

bool Object2D::CheckCollision(std::unique_ptr<BoxCollider2D>& col1, std::unique_ptr<BoxCollider2D>& col2)
{
	return !(col1->topLeft.x + col1->size.width < col2->topLeft.x ||
		col2->topLeft.x + col2->size.width < col1->topLeft.x ||
		col1->topLeft.y - col1->size.height > col2->topLeft.y ||
		col2->topLeft.y - col2->size.height > col1->topLeft.y);
}

float Object2D::SweptAABB(std::unique_ptr<BoxCollider2D>& col, Direction& result)
{
	float dxEntry = 0.0f;
	float dxExit = 0.0f;
	float dyEntry = 0.0f;
	float dyExit = 0.0f;

	if (rigidbody->velocity.x > 0.0f)
	{
		dxEntry = col->topLeft.x - (boxCollider->topLeft.x + boxCollider->size.width);
		dxExit = (col->topLeft.x + col->size.width) - boxCollider->topLeft.x;
	}
	else
	{
		dxEntry = (col->topLeft.x + col->size.width) - boxCollider->topLeft.x;
		dxExit = col->topLeft.x - (boxCollider->topLeft.x + boxCollider->size.width);
	}

	if (rigidbody->velocity.y > 0.0f)
	{
		dyEntry = (col->topLeft.y - col->size.height) - boxCollider->topLeft.y;
		dyExit = col->topLeft.y - (boxCollider->topLeft.y - boxCollider->size.height);
	}
	else
	{
		dyEntry = col->topLeft.y - (boxCollider->topLeft.y - boxCollider->size.height);

		dyExit = (col->topLeft.y - col->size.height) - boxCollider->topLeft.y;
	}

	float txEntry = 0.0f;
	float txExit = 0.0f;
	float tyEntry = 0.0f;
	float tyExit = 0.0f;

	if (rigidbody->velocity.x == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / rigidbody->velocity.x;
		txExit = dxExit / rigidbody->velocity.x;
	}

	if (rigidbody->velocity.y == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / rigidbody->velocity.y;
		tyExit = dyExit / rigidbody->velocity.y;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime < 0.0f)
	{
		result = Direction::DOWN;
		return tyEntry;
	}

	if (entryTime > exitTime || txEntry < 0.0f && tyEntry < 0.0f ||txEntry > 1.0f || tyEntry > 1.0f)
	{
		return 1.0f;
	}

	if (txEntry > tyEntry)
	{
		if (dxEntry > 0.0f)
		{
			result = Direction::RIGHT;
		}
		else
		{
			result = Direction::LEFT;
		}
	}
	else
	{
		if (dyEntry > 0.0f)
		{
			result = Direction::UP;
		}
		else
		{
			result = Direction::DOWN;
		}
	}

	return entryTime;
}

BoxCollider2D Object2D::GetSweptBroadphaseBox()
{
	BoxCollider2D broadphaseBox;
	broadphaseBox.topLeft.x = rigidbody->velocity.x != 0.0f ? boxCollider->topLeft.x + rigidbody->velocity.x: boxCollider->topLeft.x;
	broadphaseBox.topLeft.y = rigidbody->velocity.y != 0.0f ? boxCollider->topLeft.y + rigidbody->velocity.y: boxCollider->topLeft.y;
	broadphaseBox.size.width = boxCollider->size.width;
	broadphaseBox.size.height = boxCollider->size.height;

	return broadphaseBox;
}

void Object2D::RenderDebugRectangle(const D3DXMATRIX& worldToViewportMat)
{
	if (!boxCollider || !boxCollider->isEnable)
		return;

	D3DXVECTOR4 tempPos;

	D3DXVECTOR3 position = { boxCollider->topLeft.x, boxCollider->topLeft.y, 0.0f };
	D3DXVec3Transform(&tempPos, &position, &worldToViewportMat);
	D3DRECT rectToDraw = { (LONG)tempPos.x, 
		(LONG)tempPos.y, 
		(LONG)(tempPos.x + boxCollider->size.width * WINDOW_CAMERA_SCALE_X), 
		(LONG)(tempPos.y + boxCollider->size.height * WINDOW_CAMERA_SCALE_Y) };

	if (rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		DeviceResources::GetDevice()->Clear(1, &rectToDraw, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 84, 236, 117), 1.0f, NULL);
	}
	else if (rigidbody->bodyType == Rigidbody::BodyType::Kinematic)
	{
		DeviceResources::GetDevice()->Clear(1, &rectToDraw, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 186, 3, 252), 1.0f, NULL);
	}
	else if (rigidbody->bodyType == Rigidbody::BodyType::Static)
	{
		DeviceResources::GetDevice()->Clear(1, &rectToDraw, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 249, 80, 80), 1.0f, NULL);
	}
	/*position = { broadphaseBox.topLeft.x, broadphaseBox.topLeft.y, 0.0f };
	D3DXVec3Transform(&tempPos, &position, &worldToViewportMat);
	rectToDraw = { (LONG)tempPos.x, 
		(LONG)tempPos.y, 
		(LONG)(tempPos.x + broadphaseBox.size.width),
		(LONG)(tempPos.y + broadphaseBox.size.height) };
	deviceResources->GetDevice()->Clear(1, &rectToDraw, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 0, 0), 1.0f, NULL);*/
}

void Object2D::AddChildObject(const std::shared_ptr<Object2D> child)
{
	childObjects.emplace_back(child);
}