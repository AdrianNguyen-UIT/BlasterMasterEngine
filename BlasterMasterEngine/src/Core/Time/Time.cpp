#include "d3dpch.h"
#include "Time.h"

float Time::m_DeltaTime = 0.0f;
float Time::m_FixedDeltaTime = 0.0f;

float Time::GetDeltaTime()
{
	return m_DeltaTime;
}

void Time::SetDeltaTime(const float& p_DeltaTime)
{
	m_DeltaTime = p_DeltaTime;
}

void Time::SetFixedDeltaTime(const float& p_FixedDeltaTime)
{
	m_FixedDeltaTime = p_FixedDeltaTime;
}

float Time::GetTime()
{
	return (float)timeGetTime();
}

float Time::GetFixedDeltaTime()
{
	return m_FixedDeltaTime;
}
