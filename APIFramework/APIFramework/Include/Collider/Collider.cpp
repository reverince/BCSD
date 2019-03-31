#include "Collider.h"
#include "..\Object\Object.h"

Collider::Collider()
{
}

Collider::Collider(const Collider & collider)
{
	*this = collider;
}

Collider::~Collider()
{
	for (list<Collider *>::iterator iter = m_listCollision.begin(); iter != m_listCollision.end(); ++iter)
		(*iter)->EraseCollision(this);
}

bool Collider::CollisionRectVsRect(const RECTANGLE & src, const RECTANGLE & dest)
{
	if (src.l > dest.r || src.r < dest.l || src.t > dest.b || src.b < dest.t)
		return false;

	return true;
}

bool Collider::CollisionRectVsCircle(const RECTANGLE & rect, const CIRCLE & circle)
{
	// 7 8 9
	// 4 5 6
	// 1 2 3

	// 십자가 영역 2, 4, 6, 8
	if ((rect.l <= circle.p.x && circle.p.x <= rect.r) ||
		(rect.t <= circle.p.y && circle.p.y <= rect.b))
	{
		RECTANGLE rc = rect;
		// 반지름만큼 확장
		rc.l -= circle.r;
		rc.t -= circle.r;
		rc.r += circle.r;
		rc.b += circle.r;
		
		if (circle.p.x < rc.l || circle.p.x > rc.r || circle.p.y < rc.t || circle.p.y > rc.b)
			return false;

		return true;
	}

	// 대각선 영역 1, 3, 7, 9 : 사각형 4개의 꼭짓점 중 하나라도 원 안에 있으면 충돌
	POSITION pos[4];
	pos[0] = POSITION(rect.l, rect.t);
	pos[1] = POSITION(rect.l, rect.b);
	pos[2] = POSITION(rect.r, rect.t);
	pos[3] = POSITION(rect.r, rect.b);

	for (int i = 0; i < 4; ++i)
	{
		float dist = sqrtf(pow(circle.p.x - pos[i].x, 2) + pow(circle.p.y - pos[i].y, 2));
		
		if (dist <= circle.r)
			return true;
	}

	return false;
}

bool Collider::CollisionCircleVsCircle(const CIRCLE & src, const CIRCLE & dest)
{
	float dist = sqrtf((src.p.x - dest.p.x) * (src.p.x - dest.p.x) + (src.p.y - dest.p.y) * (src.p.y - dest.p.y));

	return dist <= src.r + dest.r;
}

bool Collider::Init()
{
	return false;
}

void Collider::Input(float deltaTime)
{
}

int Collider::Update(float deltaTime)
{
	return 0;
}

int Collider::LateUpdate(float deltaTime)
{
	return 0;
}

bool Collider::Collision(Collider * pDest)
{
	return false;
}

void Collider::Render(HDC hDC, float deltaTime)
{
}

Collider * Collider::Clone()
{
	return nullptr;
}
