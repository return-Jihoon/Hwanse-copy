#pragma once
#include "Image.h"
#include <assert.h>

class Res;

class Sprite
{
public:
	friend Res;

private:
	Image * m_Image;
	std::vector<bRect> m_SpriteRect;

public:
	Image * Images()
	{
		return m_Image;
	}

public:
	bool IsMulti()
	{
		return 1 < m_SpriteRect.size();
	}

	bool Count()
	{
		return m_SpriteRect.size();
	}

	bRect operator [](int _index)
	{
		if (0 >= m_SpriteRect.size())
		{
			assert(false);
		}
		return m_SpriteRect[_index];
	}

	bRect Rect(int count = 0)
	{
		if (0 >= m_SpriteRect.size())
		{
			assert(false);
		}
		return m_SpriteRect[count];
	}

public:
	void Cut(int _x, int _y);

public:
	int GetPosPixel(Pos _pos);

public:
	Sprite(Image* _image);
	~Sprite();
};

