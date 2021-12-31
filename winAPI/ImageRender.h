#pragma once
#include "GameRender.h"

class Image;

class ImageRender : public GameRender
{
private:
	Image * m_Image;

public:
	void Images(const wchar_t* _name);

	void Render() override;

public:
	ImageRender();
	~ImageRender();
};

