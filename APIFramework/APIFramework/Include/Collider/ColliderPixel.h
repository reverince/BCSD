#pragma once
#include "Collider.h"
#include "..\Core\PathManager.h"

class ColliderPixel : public Collider
{
	vector<PIXEL> m_pixels;
	int m_width;
	int m_height;

protected:

	friend class Object;
	
	ColliderPixel();
	ColliderPixel(const ColliderPixel & collider);
	virtual ~ColliderPixel();

public:

	bool SetPixels(char * pFileName, const string & pathKey = PATH_TEXTURE)
	{
		const char * pPath = GET_SINGLE(PathManager)->FindPathMultiByte(pathKey);
		string path;

		if (pPath)
			path = pPath;

		path += pFileName;

		FILE * pFile = nullptr;

		fopen_s(&pFile, path.c_str(), "rb");
		if (!pFile)
			return false;

		BITMAPFILEHEADER fh;
		BITMAPINFOHEADER ih;

		fread(&fh, sizeof(fh), 1, pFile);
		fread(&ih, sizeof(ih), 1, pFile);

		m_width = ih.biWidth;
		m_height = ih.biHeight;
		m_pixels.clear();
		m_pixels.resize(m_width * m_height);
		fread(&m_pixels[0], sizeof(PIXEL), m_pixels.size(), pFile);
		
		// 상하 반전
		PIXEL * pTemp = new PIXEL[m_width];
		size_t size = sizeof(PIXEL) * m_width;
		int halfHeight = m_height / 2;
		for (int i = 0; i < halfHeight; ++i)
		{
			memcpy(pTemp, &m_pixels[i * m_width], size);
			memcpy(&m_pixels[i * m_width], &m_pixels[(m_height - 1 - i) * m_width], size);
			memcpy(&m_pixels[(m_height - 1 - i) * m_width], pTemp, size);
		}

		delete[] pTemp;
		fclose(pFile);

		//// 쓰기
		//fopen_s(&pFile, "test.bmp", "wb");

		//fwrite(&fh, sizeof(fh), 1, pFile);
		//fwrite(&ih, sizeof(ih), 1, pFile);
		//fwrite(&m_pixels[0], sizeof(PIXEL), m_pixels.size(), pFile);

		//fclose(pFile);

		//return true;
	}
	const vector<PIXEL> & GetPixels() const { return m_pixels; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider * pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual ColliderPixel * Clone();
};
