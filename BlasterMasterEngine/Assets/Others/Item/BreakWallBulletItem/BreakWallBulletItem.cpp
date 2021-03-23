#include "d3dpch.h"
#include "BreakWallBulletItem.h"

#include "Assets/Characters/Jason/OverworldJason.h"
#include "Core/SceneManager/SceneManager.h"
#include "Core/AudioMixer/AudioMixer.h"

BreakWallBulletItem::BreakWallBulletItem(float x, float y)
	: Object2D(x, y)
{
	name = "Break Wall Bullet Item";
	tag = Tag::Item;
	rigidbody = GetComponent<Rigidbody>();
	boxCollider = GetComponent<BoxCollider2D>();
	spriteRenderer = GetComponent<SpriteRenderer>();
	layer = Layer::Projectile;
}

void BreakWallBulletItem::Start()
{
	boxCollider->size = { 25.0f, 17.0f };
	boxCollider->isTrigger = true;
	rigidbody->bodyType = Rigidbody::BodyType::Dynamic;
	rigidbody->gravityScale = 0.0f;

	spriteRenderer->rect = { 100,8,125,25 };
	transform->Scale(WINDOW_CAMERA_SCALE_X, WINDOW_CAMERA_SCALE_Y, 0.0f);
}

void BreakWallBulletItem::Update()
{
}

void BreakWallBulletItem::CreateResources()
{
	spriteRenderer->sprite = SpriteResources::GetSprite("Enemy_Bullet_Texture");
}

void BreakWallBulletItem::OnTriggerStay(std::shared_ptr<Object2D> object)
{
	if (object->tag == Tag::Player && object->rigidbody->bodyType == Rigidbody::BodyType::Dynamic)
	{
		std::shared_ptr<OverworldJason> overworldJason = std::dynamic_pointer_cast<OverworldJason>(object);
		if (overworldJason != NULL)
		{
			SceneManager::ReloadScene("EndingCutscene");
			Die();
		}
	}
}

void BreakWallBulletItem::Die()
{
	AudioMixer::PlayWaveFile("ITEM_PICKING", FALSE);
	SceneManager::DestroyObject(shared_from_this());
}
