#include "Timer.h"

DEFINE_SINGLE(Timer);

Timer::Timer() :
	m_timeScale(1)
{
}

Timer::~Timer()
{
}

bool Timer::Init()
{
	QueryPerformanceFrequency(&m_second);
	QueryPerformanceCounter(&m_time);

	m_deltaTime = 0.f;
	m_fps = 0.f;
	m_fpsTime = 0.f;

	m_frame = 0;
	m_frameMax = 60;

	return true;
}

void Timer::Update()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	m_deltaTime = (time.QuadPart - m_time.QuadPart) / (float)m_second.QuadPart;

	m_time = time;
}
