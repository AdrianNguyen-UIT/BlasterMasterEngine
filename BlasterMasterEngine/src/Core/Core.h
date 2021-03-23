#pragma once

#define WINDOW_TITLE L"Blaster Master"
#define WINDOW_WIDTH  800.0f
#define WINDOW_HEIGHT 600.0f
#define CAMERA_WIDTH 254.0f
#define CAMERA_HEIGHT 224.0f
#define WINDOW_CAMERA_SCALE_X WINDOW_WIDTH/CAMERA_WIDTH
#define WINDOW_CAMERA_SCALE_Y WINDOW_HEIGHT/CAMERA_HEIGHT
#define MONITOR_REFESH_RATE 1.0f/60.0f

#define AREA2_OBJECTS_TMX "Assets/Others/Terrains/Resources/Area2ObjectsTMX.tmx"

#define AREA2OVERWORLD_OBJECTS_TMX "Assets/Others/Terrains/Resources/Area2OverworldObjectsTMX.tmx"

#define SOPHIA_JASON_TEXTURE_PATH L"Assets/Images/Jason-Sohpia-III-nobackground.png"

#define AREA2_BOSSROOM_PATH L"Assets/Images/Boss Room.png"

#define AREA2_MAP_PATH L"Assets/Images/Area2Map.png"
#define AREA2_MAP_WIDTH 3072
#define AREA2_MAP_HEIGHT 3072

#define AREA2OVERWORLD_MAP_PATH L"Assets/Images/Area2OverworldMap.png"
#define AREA2OVERWORLD_MAP_WIDTH 2048
#define AREA2OVERWORLD_MAP_HEIGHT 2048

#define ENDING_MAP_PATH L"Assets/Images/EndingCutscene.png"
#define ENDING_MAP_LESSCOLOR_PATH L"Assets/Images/EndingCutscene_LessColor.png"
#define ENDING_MAP_WIDTH 517
#define ENDING_MAP_HEIGHT 485

#define HEALTH_BLOCK_PATH L"Assets/Images/HealthBlock.png"
#define HEALTHBAR_FONT_PATH L"Assets/Images/HealthBarFont.png"
#define ENDING_FONT_PATH L"Assets/Images/EndingFont.png"

#define TRANSPARENT_BACKGROUND_PATH L"Assets/Images/TransparentImage.png"
#define TRANSPARENT_BACKGROUND_WIDTH 800
#define TRANSPARENT_BACKGROUND_HEIGHT 600

#define BLACK_BACKGROUND_PATH L"Assets/Images/BlackImage.png"
#define BLACK_BACKGROUND_WIDTH 800
#define BLACK_BACKGROUND_HEIGHT 600

#define WHITE_BACKGROUND_PATH L"Assets/Images/WhiteImage.png"
#define WHITE_BACKGROUND_WIDTH 800
#define WHITE_BACKGROUND_HEIGHT 600

#define OPENING_SCREEN_PATH L"Assets/Images/OpeningScreen.png"
#define OPENING_SCREEN_WIDTH 256
#define OPENING_SCREEN_HEIGHT 240

#define BODY_BOSS_TEXTURE_PATH L"Assets/Images/bodyBoss.png"
#define ARM_BOSS_TEXTURE_PATH L"Assets/Images/armBoss.png"

#define MAX_OBJECTS_QUADTREE 10
#define MAX_LEVELS_QUADTREE 5

#define ENEMY_TEXTURE_PATH L"Assets/Images/Enemy.png"
#define ENEMY_BULLET_TEXTURE_PATH L"Assets/Images/other.png"

#define BADGE_PATH L"Assets/Images/Badge.png"

#define OPENING_CUTSCENE_PATH L"Assets/Images/OpeningCutscene.png"
#define ROLLOUT_CUTSCENE_PATH L"Assets/Images/RollOutCutscene.png"

#define BOSS_INTRO "Assets/Sounds/BossIntro.wav"
#define BOSS_THEME_1 "Assets/Sounds/Boss_Theme_1.wav"
#define BOSS_SHOOTING "Assets/Sounds/Boss_Shooting.wav"
#define BOSS_HIT_1 "Assets/Sounds/Boss_hit_1.wav"
#define BOSS_DIE "Assets/Sounds/Boss_Die.wav"
#define NORMAL_BULLET_SHOOT "Assets/Sounds/Normal_Bullet_Shoot.wav"
#define ENEMY_DIE_NORMAL "Assets/Sounds/Enemy_Die_Normal.wav"
#define SOPHIA_ROCKET "Assets/Sounds/Sophia_Rocket.wav"
#define BEE_FLY "Assets/Sounds/Bee_Fly.wav"
#define AREA2_THEME "Assets/Sounds/Area2.wav"
#define SOPHIA_JUMP "Assets/Sounds/Sophia_Jump.wav"
#define SOPHIA_LANDING "Assets/Sounds/Sophia_Landing.wav"
#define WORM_WALKING "Assets/Sounds/Worm_Walking.wav"
#define ITEM_PICKING "Assets/Sounds/Item_Picking.wav"
#define ENEMY_SKULL_ATTACK "Assets/Sounds/Enemy_Skull_Attack.wav"
#define PLAYER_DIE "Assets/Sounds/Player_Die.wav"
#define ROLLING "Assets/Sounds/Rolling.wav"
#define OPENING "Assets/Sounds/Opening.wav"
#define FOREST "Assets/Sounds/Forest.wav"
#define ENDING_STAFF_ROLL "Assets/Sounds/EndingStaffRoll.wav"

////////////////////////////////
////////////////////////////////

#ifdef __DEBUG
#define __ENABLE_ASSERT
#endif

#ifdef __ENABLE_ASSERT
#define __ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define __ASSERT(x, ...)
#endif

#define LOG_TRACE(...)        Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)         Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)         Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)        Log::GetLogger()->error(__VA_ARGS__)

template<typename Base, typename T>
inline bool Instanceof(const T*) 
{
	return is_base_of<Base, T>::value;
}

struct Size
{
	float width;
	float height;

	Size(const float& p_Width = 0.0f, const float& p_Height = 0.0f)
		: width(p_Width), height(p_Height)
	{
	}
};

struct Color
{
	int red;
	int green;
	int blue;
	int alpha;

	Color(const int& r = 255, const int& g = 255, const int& b = 255, const int& a = 255)
		: red(r), green(g), blue(b), alpha(a)
	{
	}
};

struct Sprite
{
	LPDIRECT3DTEXTURE9 spriteImage;
	std::string name;
	Sprite()
	{
		spriteImage = NULL;
	}

	~Sprite()
	{
		spriteImage = NULL;
	}
	Sprite(const LPDIRECT3DTEXTURE9& p_SpriteImage = NULL, const std::string& n = "")
		: spriteImage(p_SpriteImage), name(n)
	{}
};

enum class CutsceneType
{
	None,
	Opening,
	RollOut,
	Ending
};