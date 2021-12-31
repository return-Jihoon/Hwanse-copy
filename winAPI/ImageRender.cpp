#include "ImageRender.h"
#include <assert.h>
#include "Res.h"
#include "GameCore.h"
#include "Actor.h"


ImageRender::ImageRender()
{
}


ImageRender::~ImageRender()
{
}

void ImageRender::Images(const wchar_t* _name)
{
	m_Image = Res::ImageFind(_name);

	if (nullptr == m_Image)
		assert(false);
}

void ImageRender::Render()
{
	if (nullptr == m_Image)
		assert(false);

	BitBlt(GameCore::mainWindow().DC()
		, m_Actor->pos().IX(), m_Actor->pos().IY()
		, 45, 57
		, m_Image->DC()
		, 79, 123
		, SRCCOPY);
}