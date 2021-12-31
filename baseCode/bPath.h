#pragma once
#include "bDirect.h"
#include <map>

class bPath
{
private:
	static std::map<std::wstring, bDirect> m_PathMap;
	static bDirect Root;

public:
	static inline void SetRootDir(const bDirect& _dir)
	{
		Root = _dir;
	}

	static inline bDirect RootDir() 
	{
		return Root;
	}

	static void CreatePath(const wchar_t* _path);
	static void CreatePath(const wchar_t* _name, const wchar_t* _path);

	static bDirect FindPathToDir(const wchar_t* _name);
	static std::wstring FindPathToString(const wchar_t* _name);

	static std::wstring PathToFileName(const wchar_t* _path);

public:
	bPath();
	~bPath();
};

