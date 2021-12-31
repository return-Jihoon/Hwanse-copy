#include "bPath.h"
#include <assert.h>


std::map<std::wstring, bDirect> bPath::m_PathMap;
bDirect bPath::Root;

bPath::bPath()
{
}


bPath::~bPath()
{
}

void bPath::CreatePath(const wchar_t* _path)
{
	CreatePath(_path, _path);
}

void bPath::CreatePath(const wchar_t* _name, const wchar_t* _path)
{
	bDirect NewPath = Root;

	if (false == NewPath.Move(_path))
	{
		return;
	}

	m_PathMap.insert(std::map<std::wstring, bDirect>::value_type(_name, NewPath));
	return;
}

bDirect bPath::FindPathToDir(const wchar_t* _name)
{
	std::map<std::wstring, bDirect>::iterator Iter = m_PathMap.find(_name);

	if (Iter == m_PathMap.end())
	{
		assert(false);
		return bDirect();
	}
	return Iter->second;
}

std::wstring bPath::FindPathToString(const wchar_t* _name)
{
	return FindPathToDir(_name).FullPath();
}

std::wstring bPath::PathToFileName(const wchar_t* _path)
{
	std::wstring FileName = _path;
	size_t CutCount = FileName.find_last_of(L"\\", FileName.size());
	return FileName.replace(0, CutCount + 1, L"");
}
