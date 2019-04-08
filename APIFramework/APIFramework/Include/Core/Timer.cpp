#include "Timer.h"

DEFINE_SINGLE(Timer);

Timer::Timer() :
	m_timeScale(1)
{
}

Timer::~Timer()
{
}

bool Timer::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	QueryPerformanceFrequency(&m_second);
	QueryPerformanceCounter(&m_time);

	m_deltaTime = 0.f;
	m_fps = 0.f;
	m_fpsTime = 0.f;

	m_frame = 0;

	return true;
}

void Timer::Update()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	m_deltaTime = (time.QuadPart - m_time.QuadPart) / (float)m_second.QuadPart;

	m_time = time;

	m_fpsTime += m_deltaTime;
	++m_frame;

	if (m_fpsTime >= 1.f)
	{
		m_fps = m_frame / m_fpsTime;
		m_fpsTime = 0.f;
		m_frame = 0;

#ifdef _DEBUG
		char strFPS[64] = { };
		sprintf_s(strFPS, "FPS : %.f\n", m_fps);
		SetWindowTextA(m_hWnd, strFPS);
		OutputDebugStringA(strFPS);
#endif
	}
}
