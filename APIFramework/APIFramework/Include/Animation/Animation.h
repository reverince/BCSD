#pragma once
#include "..\Reference.h"

class Animation : public Reference
{
	friend class Object;

	unordered_map<string, ANIMATIONCLIP *> m_mapClip;

	Animation();
	Animation(const Animation & anim);
	~Animation();

public:

	bool AddClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
		float timeMax, float optionTimeMax,
		int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
		const string & keyTexture, const wchar_t * pFileName, const string & keyPath = PATH_TEXTURE);

	bool Init();
	void Update(float time);
	Animation * Clone();
};
