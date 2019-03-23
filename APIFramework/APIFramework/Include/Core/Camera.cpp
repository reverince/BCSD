#include "Camera.h"
#include "..\Object\Object.h"

DEFINE_SINGLE(Camera);

Camera::Camera() :
	m_pTarget(nullptr)
{
}

Camera::~Camera()
{
	SAFE_RELEASE(m_pTarget);
}

void Camera::SetTarget(Object * pObj)
{
	SAFE_RELEASE(m_pTarget);
	m_pTarget = pObj;

	if (m_pTarget)
		m_pTarget->AddRef();
}

bool Camera::Init(const POSITION & pos, const RESOLUTION & rsClient, const RESOLUTION & rsWorld)
{
	m_pos = pos;
	m_pivot = POSITION(0.5f, 0.5f);
	m_rsClient = rsClient;
	m_rsWorld = rsWorld;

	return true;
}

void Camera::Input(float deltaTime)
{
	if (!m_pTarget)
	{

	}
}

void Camera::Update(float deltaTime)
{
	if (m_pTarget)
	{
		POSITION pos = m_pTarget->GetPos();
		POSITION pivot = m_pTarget->GetPivot();
		_SIZE size = m_pTarget->GetSize();

		float left = pos.x - pivot.x * size.x;
		float top = pos.y - pivot.y * size.y;
		float right = left + size.x;
		float bottom = top + size.y;

		float areaLeft = m_rsClient.w * m_pivot.x;
		float areaRight = m_rsClient.w - areaLeft;
		float areaTop = m_rsClient.h * pivot.y;
		float areaBottom = m_rsClient.h - areaTop;

		if (left <= areaLeft)
			m_pos.x = 0.f;
		else if (right >= m_rsWorld.w - areaRight)
			m_pos.x = (float)(m_rsWorld.w - m_rsClient.w);
		else
			m_pos.x = pos.x - m_rsClient.w * m_pivot.x;

		if (top <= areaTop)
			m_pos.y = 0.f;
		else if (bottom >= m_rsWorld.h - areaBottom)
			m_pos.y = (float)(m_rsWorld.h - m_rsClient.h);
		else
			m_pos.y = pos.y - m_rsClient.h * m_pivot.y;
	}
}
