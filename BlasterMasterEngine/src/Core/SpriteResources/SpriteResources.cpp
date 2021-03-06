#include "d3dpch.h"
#include "SpriteResources.h"
#include "Core/DeviceResources/DeviceResources.h"
std::vector<std::shared_ptr<Sprite>> SpriteResources::sprites;
SpriteResources::SpriteResources()
{
}

SpriteResources::~SpriteResources()
{
}

HRESULT SpriteResources::CreateSpriteResources()
{
	sprites.reserve(19);

	std::shared_ptr<Sprite> sprite1 = DeviceResources::LoadTexture(SOPHIA_JASON_TEXTURE_PATH, 0);
	sprite1->name = "Sophia_Jason_Texture";

	std::shared_ptr<Sprite> sprite2 = DeviceResources::LoadTexture(ENEMY_TEXTURE_PATH, 0);
	sprite2->name = "Enemy_Texture";

	std::shared_ptr<Sprite> sprite3 = DeviceResources::LoadTexture(ENEMY_BULLET_TEXTURE_PATH, 0);
	sprite3->name = "Enemy_Bullet_Texture";

	std::shared_ptr<Sprite> sprite4 = DeviceResources::LoadTexture(HEALTH_BLOCK_PATH, 0);
	sprite4->name = "Health_Block_Texture";

	std::shared_ptr<Sprite> sprite5 = DeviceResources::LoadTexture(HEALTHBAR_FONT_PATH, 0);
	sprite5->name = "Health_Bar_Font_Texture";

	std::shared_ptr<Sprite> sprite6 = DeviceResources::LoadTexture(AREA2_MAP_PATH, 0);
	sprite6->name = "Area2_Texture";

	std::shared_ptr<Sprite> sprite7 = DeviceResources::LoadTexture(OPENING_CUTSCENE_PATH, 0);
	sprite7->name = "Opening_Cutscene";

	std::shared_ptr<Sprite> sprite8 = DeviceResources::LoadTexture(BLACK_BACKGROUND_PATH, 0);
	sprite8->name = "Black_Background";

	std::shared_ptr<Sprite> sprite9 = DeviceResources::LoadTexture(WHITE_BACKGROUND_PATH, 0);
	sprite9->name = "White_Background";

	std::shared_ptr<Sprite> sprite10 = DeviceResources::LoadTexture(OPENING_SCREEN_PATH, 0);
	sprite10->name = "Opening_Screen";

	std::shared_ptr<Sprite> sprite11 = DeviceResources::LoadTexture(ROLLOUT_CUTSCENE_PATH, 0);
	sprite11->name = "RollOut_Cutscene";

	std::shared_ptr<Sprite> sprite12 = DeviceResources::LoadTexture(ENDING_MAP_PATH, 0);
	sprite12->name = "Ending_Cutscene";

	std::shared_ptr<Sprite> sprite13 = DeviceResources::LoadTexture(ENDING_FONT_PATH, 0);
	sprite13->name = "Ending_Font_Texture";

	std::shared_ptr<Sprite> sprite14 = DeviceResources::LoadTexture(ENDING_MAP_LESSCOLOR_PATH, 0);
	sprite14->name = "Ending_LessColor_Cutscene";

	std::shared_ptr<Sprite> sprite15 = DeviceResources::LoadTexture(BADGE_PATH, 0);
	sprite15->name = "Badge_Texture";

	std::shared_ptr<Sprite> sprite16 = DeviceResources::LoadTexture(BODY_BOSS_TEXTURE_PATH, 0);
	sprite16->name = "Body_Boss_Texture";

	std::shared_ptr<Sprite> sprite17 = DeviceResources::LoadTexture(ARM_BOSS_TEXTURE_PATH, 0);
	sprite17->name = "Arm_Boss_Texture";

	std::shared_ptr<Sprite> sprite18 = DeviceResources::LoadTexture(AREA2_BOSSROOM_PATH, 0);
	sprite18->name = "Boss_Room_Texture";

	std::shared_ptr<Sprite> sprite19 = DeviceResources::LoadTexture(AREA2OVERWORLD_MAP_PATH, 0);
	sprite19->name = "Area2_Overworld_Texture";




	sprites.emplace_back(sprite1);
	sprites.emplace_back(sprite2);
	sprites.emplace_back(sprite3);
	sprites.emplace_back(sprite4);
	sprites.emplace_back(sprite5);
	sprites.emplace_back(sprite6);
	sprites.emplace_back(sprite7);
	sprites.emplace_back(sprite8);
	sprites.emplace_back(sprite9);
	sprites.emplace_back(sprite10);
	sprites.emplace_back(sprite11);
	sprites.emplace_back(sprite12);
	sprites.emplace_back(sprite13);
	sprites.emplace_back(sprite14);
	sprites.emplace_back(sprite15);
	sprites.emplace_back(sprite16);
	sprites.emplace_back(sprite17);
	sprites.emplace_back(sprite18);
	sprites.emplace_back(sprite19);
	return S_OK;
}

std::shared_ptr<Sprite> SpriteResources::GetSprite(const std::string& name)
{
	for (auto sprite : sprites)
	{
		if (sprite->name == name)
		{
			return sprite;
			break;
		}
	}
}
