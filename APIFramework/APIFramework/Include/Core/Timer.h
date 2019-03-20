#pragma once
#include "..\Game.h"

class Timer
{
	LARGE_INTEGER m_second;
	LARGE_INTEGER m_time;
	float m_deltaTime;
	float m_timeScale;
	float m_fps;
	float m_fpsTime;
	int m_frame;
	int m_frameMax;

	DECLARE_SINGLE(Timer);

public:

	void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	float GetDeltaTime() const { return m_deltaTime * m_timeScale; }
	float GetTimeScale() const { return m_timeScale; }
	float GetFPS() const { return m_fps; }

	bool Init();
	void Update();
};
