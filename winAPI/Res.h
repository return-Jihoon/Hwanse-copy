#pragma once
#include "Image.h"
#include "Sprite.h"
#include <unordered_map>

class Image;
class Res
{
	class Destructor
	{
	public:
		~Destructor()
		{
			Res::End();
		}
	};
	static Destructor Des;
	friend Destructor;

private:
	static void End();

private:
	static std::unordered_map<std::wstring, Image*> ImageMap;

public:
	static Image* ImageFind(const wchar_t* _name);

	static Image* ImageLoad(const wchar_t* _path);
	static Image* ImageLoad(const wchar_t* _name, const wchar_t* _path); 

private:
	static std::unordered_map<std::wstring, Sprite*> SpriteMap;

public:
	static Sprite* SpriteFind(const wchar_t* _name);

	static Sprite* SpriteCreate(const wchar_t* _imagename, int _x, int _y);
	static Sprite* SpriteCreate(const wchar_t* _imagename, const wchar_t* _spritename, int _x, int _y);

public:
	Res();
	~Res();
};

