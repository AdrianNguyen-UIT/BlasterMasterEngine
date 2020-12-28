#include "d3dpch.h"
#include "PlayerDeadExplosion.h"
#include "Core/SceneManager/SceneManager.h"
PlayerDeadExplosion::PlayerDeadExplosion(float x, float y)
	: Object2D(x, y)
{
	name = "Player Dead Explosion Particle";
	tag = Tag::Default;
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Particle;
}

void PlayerDeadExplosion::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");

	KeyFrame keyFrame;
	RECT smallRect = { 159, 3, 207, 43};
	RECT bigRect = {143, 44, 207, 92};

	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> explosion = std::make_shared<Animation>("Normal Bullet Explosion Animation");
	{
		explosion->SetAnimationFPS(20);
		explosion->SetIsLooping(false);

		keyFrame.rect = smallRect;
		explosion->AddKeyFrames(keyFrame);
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = bigRect;
		explosion->AddKeyFrames(keyFrame);
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = { 0, 0, 0, 0 };
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = bigRect;
		explosion->AddKeyFrames(keyFrame);
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = smallRect;
		explosion->AddKeyFrames(keyFrame);
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = { 0, 0, 0, 0 };
		explosion->AddKeyFrames(keyFrame);

		animationController->AddAnimation(explosion);
		animationController->SetDefaultAnimation(explosion);
	}
}

void PlayerDeadExplosion::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
	timeLapse = 0.0f;
}

void PlayerDeadExplosion::Update()
{
	if (timeLapse >= 1.5f)
	{
		timeLapse = 0.0f;
		SceneManager::DestroyObject(shared_from_this());

		return;
	}
	timeLapse += Time::GetDeltaTime();
}