#pragma once
#include "..\Reference.h"

class Animation : public Reference
{
	friend class Object;

	unordered_map<string, ANIMATIONCLIP *> m_mapClip;
	ANIMATIONCLIP * m_pClipCurrent;
	string m_nameClipCurrent;
	string m_nameClipDefault;
	class Object * m_pObj;
	bool m_isClipOver;

	Animation();
	Animation(const Animation & anim);
	~Animation();

	ANIMATIONCLIP * FindClip(const string & nameClip);

public:

	void SetObj(class Object * pObj) { m_pObj = pObj; }
	void SetClipCurrent(const string & nameClipCurrent);
	void SetClipDefault(const string & nameClipDefault);
	ANIMATIONCLIP * GetClipCurrent() const { return m_pClipCurrent; }
	void ChangeClip(const string & nameClip);
	void ReturnClip();

	bool IsClipOver() const { return m_isClipOver; }

	bool AddClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
		float timeMax, float optionTimeMax,
		int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
		const string & keyTexture, const wchar_t * pFileName, const string & keyPath = PATH_TEXTURE);
	bool AddClip(const string & name, ANIMATION_TYPE type, ANIMATION_OPTION option,
		float timeMax, float optionTimeMax,
		int frameMaxX, int frameMaxY, int startX, int startY, int lengthX, int lengthY,
		const string & keyTexture, const vector<wstring> & fileNames, const string & keyPath = PATH_TEXTURE);

	bool Init();
	void Update(float time);
	Animation * Clone();
};
