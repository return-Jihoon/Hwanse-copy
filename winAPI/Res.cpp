#include "Res.h"
#include <assert.h>
#include <bPath.h>


std::unordered_map<std::wstring, Image*> Res::ImageMap;
std::unordered_map<std::wstring, Sprite*> Res::SpriteMap;
Res::Destructor Res::Des;

void Res::End()
{
	std::unordered_map<std::wstring, Image*>::iterator StartIter = ImageMap.begin();
	std::unordered_map<std::wstring, Image*>::iterator EndIter = ImageMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}

		delete StartIter->second;
		StartIter->second = nullptr;
	}

	std::unordered_map<std::wstring, Sprite*>::iterator StartSIter = SpriteMap.begin();
	std::unordered_map<std::wstring, Sprite*>::iterator EndSIter = SpriteMap.end();

	for (; StartSIter != EndSIter; ++StartSIter)
	{
		if (nullptr == StartSIter->second)
		{
			continue;
		}

		delete StartSIter->second;
		StartSIter->second = nullptr;
	}
}

Image* Res::ImageFind(const wchar_t* _name)
{
	std::unordered_map<std::wstring, Image*>::iterator FindImageIter = ImageMap.find(_name);

	if (FindImageIter == ImageMap.end())
	{
		return nullptr;
	}
	return FindImageIter->second;
}

Image* Res::ImageLoad(const wchar_t* _path)
{
	std::wstring Key = bPath::PathToFileName(_path);
	return ImageLoad(Key.c_str(), _path);
}

Image* Res::ImageLoad(const wchar_t* _name, const wchar_t* _path)
{
	Image* NewLoadImage = ImageFind(_name);

	if (nullptr != NewLoadImage)
	{
		assert(false);
		return nullptr;
	}

	NewLoadImage = new Image();

	if (false == NewLoadImage->Load(_path))
	{
		assert(false);
		delete NewLoadImage;
		return nullptr;
	}

	ImageMap.insert(std::unordered_map<std::wstring, Image*>::value_type(_name, NewLoadImage));

	return NewLoadImage;
}

Res::Res()
{
}


Res::~Res()
{
}

Sprite* Res::SpriteFind(const wchar_t* _name)
{
	std::unordered_map<std::wstring, Sprite*>::iterator FindSpriteIter = SpriteMap.find(_name);

	if (FindSpriteIter == SpriteMap.end())
	{
		return nullptr;
	}

	return FindSpriteIter->second;
}

Sprite* Res::SpriteCreate(const wchar_t* _imageName, int _X, int _Y)
{
	return SpriteCreate(_imageName, _imageName, _X, _Y);
}

Sprite* Res::SpriteCreate(const wchar_t* _ImageName, const wchar_t* _SpriteName, int _X, int _Y)
{
	Image* FindImg = ImageFind(_ImageName);

	if (nullptr == FindImg)
	{
		assert(false);
	}

	Sprite* FindSprite = SpriteFind(_SpriteName);

	if (nullptr != FindSprite)
	{
		assert(false);
	}

	FindSprite = new Sprite(FindImg);

	FindSprite->Cut(_X, _Y);

	SpriteMap.insert(std::unordered_map<std::wstring, Sprite*>::value_type(_SpriteName, FindSprite));

	return FindSprite;
}