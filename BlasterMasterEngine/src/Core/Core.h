#pragma once

#define WINDOW_TITLE L"D3DTutorial"
#define WIDTH  800.0f
#define HEIGHT 600.0f
#define MONITOR_REFESH_RATE 1.0f/60.0f

#define BITMAP_PATH L"Samples/Images/level1-side.png"
#define TEXTURE_PATH L"Samples/Images/SPA_Player_Ginger.png"

#define BGM_AUDIO "Samples/Sounds/Ensoniq-ZR-76-01-Dope-77.wav"
#define BIP_SOUND "Samples/Sounds/Blaster Master SFX (1).wav"


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