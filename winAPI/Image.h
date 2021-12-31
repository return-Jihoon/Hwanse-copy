#pragma once
#include <bDirect.h>
#include <bGeo.h>
#include <Windows.h>


class Res;
class Image
{
public:
	friend Res;

private:
	HDC m_Image;
	pSize m_Size;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	BITMAPFILEHEADER m_BitFileHeader;
	BITMAPINFOHEADER m_BitMapInfo;

public:
	int GetPosPixel(Pos _pos);
	HDC DC() { return m_Image; }
	pSize Size() { return m_Size; }
	bool Create(pSize _size);
	bool Load(const wchar_t* _path);
	void CalSize(const wchar_t* _path);

public:
	Image();
	~Image();
};

