#pragma once
#include "GameRender.h"

class Sprite;

class TransRender : public GameRender
{
public:
	Sprite* m_Sprite;

private:
	int m_Index;
	int TransRenders;

public:
	void Sprite(const wchar_t* _name, int _index = 0);
	void Render() override;
	void SpriteSizeOn();

	float Percentage;

	int GetPosPixel(Pos _pos);

public:
	TransRender();
	~TransRender();
};

