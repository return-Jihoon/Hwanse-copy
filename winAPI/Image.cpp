#include "Image.h"
#include "GameCore.h"
#include <assert.h>
#include <bWindow.h>
#include <bFile.h>


Image::Image() : m_Image(nullptr)
				,m_Size({0,0})
				,m_BitMap(nullptr)
				,m_OldBitMap(nullptr)
{
}


Image::~Image()
{
	DeleteObject(m_OldBitMap);
	DeleteDC(m_Image);
}

int Image::GetPosPixel(Pos _pos)
{
	if (_pos.IX() < 0)
	{
		return 0;
	}

	if (_pos.IY() < 0)
	{
		return 0;
	}

	if (_pos.IX() >= m_Size.IX())
	{
		return 0;
	}

	if (_pos.IY() >= m_Size.IY())
	{
		return 0;
	}

	return GetPixel(m_Image, _pos.IX(), _pos.IY());
}

bool Image::Load(const wchar_t* _path)
{
	m_BitMap = (HBITMAP)LoadImageW(nullptr, _path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == m_BitMap)
	{
		assert(false);
		return false;
	}

	m_Image = CreateCompatibleDC(nullptr);

	m_OldBitMap = (HBITMAP)SelectObject(m_Image, m_BitMap);

	if (nullptr == m_Image)
	{
		assert(false);
	}

	CalSize(_path);
	
	return true;
}

bool Image::Create(pSize _size)
{
	m_Image = CreateCompatibleDC(nullptr);
	m_BitMap = CreateCompatibleBitmap(GameCore::mainWindow().DC()
		, _size.IX(), _size.IY());

	if (nullptr == m_Image || nullptr == m_BitMap)
	{
		assert(false);
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_Image, m_BitMap);

	if (nullptr == m_Image)
	{
		assert(false);
	}

	m_Size = _size;

	return true;
}

void Image::CalSize(const wchar_t* _path)
{
	bFileStream_R Stream = bFileStream_R(_path);
	Stream >> m_BitFileHeader;
	Stream >> m_BitMapInfo;

	m_Size.X = (float)m_BitMapInfo.biWidth;
	m_Size.Y = (float)m_BitMapInfo.biHeight;
}