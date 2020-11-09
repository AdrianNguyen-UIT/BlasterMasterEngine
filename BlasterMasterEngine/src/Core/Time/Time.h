#pragma once
class Time
{
private:
	static float m_DeltaTime;
	static float m_FixedDeltaTime;

public:
	Time() = default;
	Time(const Time& p_Time) = delete;
	Time& operator=(const Time& p_Time) = delete;

	static float GetDeltaTime();
	static float GetFixedDeltaTime();
	static void SetDeltaTime(const float& p_DeltaTime);	
	static void SetFixedDeltaTime(const float& p_FixedDeltaTime);
	static float GetTime();
};
