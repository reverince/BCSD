#include "..\Resource\Texture.h"
#include "Animation.h"
#include "..\Resource\ResourceManager.h"
#include "..\Object\Object.h"

Animation::Animation() :
	m_pClipCurrent(nullptr), m_isClipOver(false)
{
}

Animation::Animation(const Animation & anim)
{
	*this = anim;

	m_isClipOver = false;
	m_mapClip.clear();
	
	unordered_map<string, ANIMATIONCLIP *>::const_iterator iter;
	for (iter = anim.m_mapClip.begin(); iter != anim.m_mapClip.end(); ++iter)
	{
		ANIMATIONCLIP * pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;
		for (size_t i = 0; i < pClip->textures.size(); ++i)
			pClip->textures[i]->AddRef();
	}

	m_pClipCurrent = nullptr;
	m_nameClipCurrent = "";
	SetClipCurrent(anim.m_nameClipCurrent);
}

Animation::~Animation()
{
	unordered_map<string, ANIMATIONCLIP *>::iterator iter;
	for (iter = m_mapClip.begin(); iter != m_mapClip.end(); ++iter)
	{
		for (size_t i = 0; i < iter->second->textures.size(); ++i)
			SAFE_RELEASE(iter->second->textures[i]);
		SAFE_DELETE(iter->second);
	}
	m_mapClip.clear();
}

ANIMATIONCLIP * Animation::FindClip(const string & nameClip)
{
	unordered_map<string, ANIMATIONCLIP *>::iterator iter = m_mapClip.find(nameClip);

	if (iter == m_mapClip.end())
		return nullptr;

	return iter->second;
}

void Animation::SetClipCurrent(const string & nameClipCurrent)
{
	ChangeClip(nameClipCurrent);
}

void Animation::SetClipDefault(const string & nameClipDefault)
{
	m_nameClipDefault = nameClipDefault;
}

void Animation::ChangeClip(const string & nameClip)
{
	if (m_nameClipCurrent == nameClip)
		return;

	m_nameClipCurrent = nameClip;

	if (m_pClipCurrent)
	{
		m_pClipCurrent->frameX = m_pClipCurrent->startX;
		m_pClipCurrent->frameY = m_pClipCurrent->startY;
		m_pClipCurrent->time = 0.f;
		m_pClipCurrent->optionTime = 0.f;
	}

	m_pClipCurrent = FindClip(nameClip);
	if (m_pClipCurrent->type == AT_ATLAS)
		m_pObj->SetTexture(m_pClipCurrent->textures[0]);
	else if (m_pClipCurrent->type == AT_FRAME)
		m_pObj->SetTexture(m_pClipCurrent->textures[m_pClipCurrent->frameX]);
}

void Animation::ReturnClip()
{
	ChangeClip(m_nameClipDefault);
}

bool Animation::AddClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
	float timeMax, float optionTimeMax,
	int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
	const string & keyTexture, const wchar_t * pFileName, const string & keyPath)
{
	ANIMATIONCLIP * pClip = new ANIMATIONCLIP;

	pClip->type = type;
	pClip->option = option;
	pClip->time = 0.f;
	pClip->timeMax = timeMax;
	pClip->timeFrame = timeMax / (lengthX * lengthY);
	pClip->optionTime = 0.f;
	pClip->optionTimeMax = optionTimeMax;
	pClip->frameX = 0;
	pClip->frameMaxX = frameMaxX;
	pClip->frameY = 0;
	pClip->frameMaxY = frameMaxY;
	pClip->startX = startX;
	pClip->startY = startY;
	pClip->lengthX = lengthX;
	pClip->lengthY = lengthY;
	
	Texture * pTexture = GET_SINGLE(ResourceManager)->LoadTexture(keyTexture, pFileName, keyPath);
	pClip->sizeFrame.x = (float)pTexture->GetWidth() / frameMaxX;
	pClip->sizeFrame.y = (float)pTexture->GetHeight() / frameMaxY;
	pClip->textures.push_back(pTexture);

	m_mapClip.insert(make_pair(name, pClip));

	if (m_nameClipDefault.empty())
		SetClipDefault(name);
	if (m_nameClipCurrent.empty())
		SetClipCurrent(name);
	
	return true;
}

bool Animation::AddClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option, float timeMax, float optionTimeMax, int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY, const string & keyTexture, const vector<wstring> & fileNames, const string & keyPath)
{
	ANIMATIONCLIP * pClip = new ANIMATIONCLIP;

	pClip->type = type;
	pClip->option = option;
	pClip->time = 0.f;
	pClip->timeMax = timeMax;
	pClip->timeFrame = timeMax / (lengthX * lengthY);
	pClip->optionTime = 0.f;
	pClip->optionTimeMax = optionTimeMax;
	pClip->frameX = 0;
	pClip->frameMaxX = frameMaxX;
	pClip->frameY = 0;
	pClip->frameMaxY = frameMaxY;
	pClip->startX = startX;
	pClip->startY = startY;
	pClip->lengthX = lengthX;
	pClip->lengthY = lengthY;

	for (size_t i = 0; i < fileNames.size(); ++i)
	{
		char key[MAX_PATH] = { };
		sprintf_s(key, "%s%d", keyTexture.c_str(), i);
		Texture * pTexture = GET_SINGLE(ResourceManager)->LoadTexture(key, fileNames[i].c_str(), keyPath);
		pClip->textures.push_back(pTexture);
	}
	pClip->sizeFrame.x = (float)pClip->textures[0]->GetWidth() / frameMaxX;
	pClip->sizeFrame.y = (float)pClip->textures[0]->GetHeight() / frameMaxY;

	m_mapClip.insert(make_pair(name, pClip));

	if (m_nameClipDefault.empty())
		SetClipDefault(name);
	if (m_nameClipCurrent.empty())
		SetClipCurrent(name);

	return true;
}

bool Animation::Init()
{
	return true;
}

void Animation::Update(float time)
{
	m_isClipOver = false;

	m_pClipCurrent->time += time;

	while (m_pClipCurrent->time >= m_pClipCurrent->timeFrame)
	{
		m_pClipCurrent->time -= m_pClipCurrent->timeFrame;
		++m_pClipCurrent->frameX;

		if (m_pClipCurrent->frameX - m_pClipCurrent->startX == m_pClipCurrent->lengthX)
		{
			m_pClipCurrent->frameX = m_pClipCurrent->startX;
			++m_pClipCurrent->frameY;
			if (m_pClipCurrent->frameY - m_pClipCurrent->startY == m_pClipCurrent->lengthY)
			{
				m_pClipCurrent->frameY = m_pClipCurrent->startY;
				m_isClipOver = true;
				switch (m_pClipCurrent->option)
				{
				case AO_ONCE_RETURN:
					ChangeClip(m_nameClipDefault);
					break;
				case AO_ONCE_DESTROY:
					m_pObj->Die();
					break;
				case AO_TIME_RETURN:
					break;
				case AO_TIME_DESTROY:
					break;
				}
			}
		}
		else
		{
			if (m_pClipCurrent->type == AT_FRAME)
				m_pObj->SetTexture(m_pClipCurrent->textures[m_pClipCurrent->frameX]);
		}
	}
}

Animation * Animation::Clone()
{
	return new Animation(*this);
}
