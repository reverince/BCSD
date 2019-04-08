#include "..\Resource\Texture.h"
#include "Animation.h"
#include "..\Resource\ResourceManager.h"

Animation::Animation()
{
}

Animation::Animation(const Animation & anim)
{
	*this = anim;
	
	unordered_map<string, ANIMATIONCLIP *>::const_iterator iter;
	for (iter = anim.m_mapClip.begin(); iter != anim.m_mapClip.end(); ++iter)
	{
		ANIMATIONCLIP * pClip = new ANIMATIONCLIP;

		*pClip = *iter->second;
		for (size_t i = 0; i < pClip->textures.size(); ++i)
			pClip->textures[i]->AddRef();
	}
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

	m_mapClip.insert(make_pair(name, pClip));
	
	return true;
}

bool Animation::Init()
{
	return true;
}

void Animation::Update(float time)
{
}

Animation * Animation::Clone()
{
	return new Animation(*this);
}
