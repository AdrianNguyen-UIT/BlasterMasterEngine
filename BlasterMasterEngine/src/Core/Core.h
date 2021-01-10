#pragma once

#define WINDOW_TITLE L"D3DTutorial"
#define WINDOW_WIDTH  800.0f
#define WINDOW_HEIGHT 600.0f
#define CAMERA_WIDTH 254.0f
#define CAMERA_HEIGHT 224.0f
#define WINDOW_CAMERA_SCALE_X WINDOW_WIDTH/CAMERA_WIDTH
#define WINDOW_CAMERA_SCALE_Y WINDOW_HEIGHT/CAMERA_HEIGHT
#define MONITOR_REFESH_RATE 1.0f/60.0f

#define OBJECTS_TMX "Assets/Terrains/Resources/Area2ObjectsTMX.tmx"

#define BGM_AUDIO "Samples/Sounds/Ensoniq-ZR-76-01-Dope-77.wav"
#define BIP_SOUND "Samples/Sounds/Blaster Master SFX (1).wav"

#define SOPHIA_JASON_TEXTURE_PATH L"Assets/Images/Jason-Sohpia-III-nobackground.png"

#define AREA2_MAP_PATH L"Assets/Images/Area2Map.png"
#define AREA2_MAP_WIDTH 3072
#define AREA2_MAP_HEIGHT 3072

#define ENDING_MAP_PATH L"Assets/Images/EndingCutscene.png"
#define ENDING_MAP_LESSCOLOR_PATH L"Assets/Images/EndingCutscene_LessColor.png"
#define ENDING_MAP_WIDTH 517
#define ENDING_MAP_HEIGHT 485

#define HEALTH_BLOCK_PATH L"Assets/Images/HealthBlock.png"
#define HEALTHBAR_FONT_PATH L"Assets/Images/HealthBarFont.png"
#define ENDING_FONT_PATH L"Assets/Images/EndingFont.png"

#define BLACK_BACKGROUND_PATH L"Assets/Images/BlackImage.png"
#define BLACK_BACKGROUND_WIDTH 800
#define BLACK_BACKGROUND_HEIGHT 600

#define WHITE_BACKGROUND_PATH L"Assets/Images/WhiteImage.png"
#define WHITE_BACKGROUND_WIDTH 800
#define WHITE_BACKGROUND_HEIGHT 600

#define OPENING_SCREEN_PATH L"Assets/Images/OpeningScreen.png"
#define OPENING_SCREEN_WIDTH 256
#define OPENING_SCREEN_HEIGHT 240

#define MAX_OBJECTS_QUADTREE 10
#define MAX_LEVELS_QUADTREE 5

#define ENEMY_TEXTURE_PATH L"Assets/Images/Enemy.png"
#define ENEMY_BULLET_TEXTURE_PATH L"Assets/Images/other.png"

#define BADGE_PATH L"Assets/Images/Badge.png"

#define OPENING_CUTSCENE_PATH L"Assets/Images/OpeningCutscene.png"
#define ROLLOUT_CUTSCENE_PATH L"Assets/Images/RollOutCutscene.png"
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