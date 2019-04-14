#include "UI.h"
#include "..\Animation\Animation.h"
#include "..\Resource\Texture.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::Input(float deltaTime)
{
	Object::Input(deltaTime);
}

int UI::Update(float deltaTime)
{
	Object::Update(deltaTime);

	return 0;
}

int UI::LateUpdate(float deltaTime)
{
	Object::LateUpdate(deltaTime);

	return 0;
}

void UI::Collision(float deltaTime)
{
	Object::Collision(deltaTime);
}

void UI::Render(HDC hDC, float deltaTime)
{
	Object::Render(hDC, deltaTime);

	if (m_pTexture)
	{
		POSITION pos = m_pos - m_size * m_pivot;
		int pX = (int)pos.x, pY = (int)pos.y, sX = (int)m_size.x, sY = (int)m_size.y;

		POSITION posImage;

		if (m_pAnimation)
		{
			ANIMATIONCLIP* pClip = m_pAnimation->GetClipCurrent();
			if (pClip->type == AT_ATLAS)
			{
				posImage.x = pClip->frameX * pClip->sizeFrame.x;
				posImage.y = pClip->frameY * pClip->sizeFrame.y;
			}
		}

		if (m_pTexture->HasColorKey())
			TransparentBlt(hDC, pX, pY, sX, sY, m_pTexture->GetDC(), (int)posImage.x, (int)posImage.y, sX, sY, m_pTexture->GetColorKey());
		else
			BitBlt(hDC, pX, pY, sX, sY, m_pTexture->GetDC(), (int)posImage.x, (int)posImage.y, SRCCOPY);
	}

	// Ãæµ¹Ã¼ ·»´õ
	for (list<Collider*>::iterator iter = m_listCollider.begin(); iter != m_listCollider.end(); ++iter)
	{
		if (!(*iter)->IsEnabled())
			continue;

		(*iter)->Render(hDC, deltaTime);

		if (!(*iter)->IsAlive())
		{
			SAFE_RELEASE(*iter);
			iter = m_listCollider.erase(iter);
		}
	}
}
