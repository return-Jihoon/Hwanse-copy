#include "Sprite.h"


Sprite::Sprite(Image* _image) : m_Image(_image)
{
}


Sprite::~Sprite()
{
}

int Sprite::GetPosPixel(Pos _pos)
{
	return m_Image->GetPosPixel(_pos);
}

void Sprite::Cut(int _x, int _y)
{
	pSize Size = { m_Image->Size().X / _x, m_Image->Size().Y / _y };
	Pos pos = Pos::ZERO;

	bRect RT;

	for (int Y = 0; Y < _y; ++Y)
	{
		for (int X = 0; X < _x; ++X)
		{
			RT.pos = pos;
			RT.size = Size;
			m_SpriteRect.push_back(RT);
			pos.X += Size.X;
		}

		pos.Y += Size.Y;
		pos.X = 0;
	}
}
