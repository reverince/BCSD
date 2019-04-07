#include "Stage.h"
#include "..\Core\Core.h"
#include "..\Core\Camera.h"
#include "..\Resource\Texture.h"

Stage::Stage()
{
}

Stage::Stage(const Stage & stage) :
	StaticObject(stage)
{
}

Stage::~Stage()
{
}

Stage * Stage::Clone()
{
	return new Stage(*this);
}

bool Stage::Init()
{
	SetPos(0.f, 0.f);
	SetSize((float)WND_WIDTH, (float)WND_HEIGHT);
	SetPivot(0.f, 0.f);
	SetTexture("Stage1", STAGE_TEXTURE_L);

	return true;
}

void Stage::Input(float deltaTime)
{
	StaticObject::Input(deltaTime);
}

int Stage::Update(float deltaTime)
{
	StaticObject::Update(deltaTime);

	return 0;
}

int Stage::LateUpdate(float deltaTime)
{
	StaticObject::LateUpdate(deltaTime);

	return 0;
}

void Stage::Collision(float deltaTime)
{
	StaticObject::Collision(deltaTime);
}

void Stage::Render(HDC hDC, float deltaTime)
{
	//StaticObject::Render(hDC, deltaTime);
	if (m_pTexture)
	{
		POSITION pos = m_pos - m_size * m_pivot;
		POSITION posCam = GET_SINGLE(Camera)->GetPos();

		//BitBlt(hDC, (int)pos.x, (int)pos.y, (int)m_size.x, (int)m_size.y, m_pTexture->GetDC(), (int)posCam.x, (int)posCam.y, SRCCOPY);
		BitBlt(hDC, (int)pos.x, (int)pos.y, (int)m_size.x, (int)m_size.y, m_pTexture->GetDC(), 0, 0, SRCCOPY);
	}
}
