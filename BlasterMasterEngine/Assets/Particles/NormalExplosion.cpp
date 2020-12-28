#include "d3dpch.h"
#include "NormalExplosion.h"
#include "Core/SceneManager/SceneManager.h"
NormalExplosion::NormalExplosion(float x, float y)
	: Object2D(x, y)
{
	name = "Normal Explosion Particle";
	tag = Tag::Default;
	animationController = GetComponent<AnimationController>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Particle;
}

void NormalExplosion::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Sophia_Jason_Texture");

	KeyFrame keyFrame;
	RECT rect;
	keyFrame.scale = { 1.0f, 1.0f, 0.0f };

	std::shared_ptr<Animation> explosion = std::make_shared<Animation>("Normal Bullet Explosion Animation");
	{
		explosion->SetAnimationFPS(20);
		explosion->SetIsLooping(false);

		rect.left = 166;
		rect.top = 97;
		rect.right = 182;
		rect.bottom = 113;

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = {0, 0, 0, 0};
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		rect.left = 149;
		rect.top = 97;
		rect.right = 165;
		rect.bottom = 113;

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		rect.left = 140;
		rect.top = 101;
		rect.right = 147;
		rect.bottom = 108;

		keyFrame.rect = rect;
		explosion->AddKeyFrames(keyFrame);

		keyFrame.rect = { 0, 0, 0, 0 };
		explosion->AddKeyFrames(keyFrame);

		animationController->AddAnimation(explosion);
		animationController->SetDefaultAnimation(explosion);
	}
}

void NormalExplosion::Start()
{
	transform->scale = { WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f };
	timeLapse = 0.0f;
}

void NormalExplosion::Update()
{
	if (timeLapse >= 1.5f)
	{
		timeLapse = 0.0f;
		SceneManager::DestroyObject(shared_from_this());

		return;
	}
	timeLapse += Time::GetDeltaTime();
}