#pragma once
#include "bIO.h"
#include <vector>
#include <string>

class bDirect
{
private:
	std::wstring m_FullPath;

public:
	std::wstring FolderName();

	const wchar_t* FullPath()
	{
		return m_FullPath.c_str();
	}

	std::wstring FullPathString()
	{
		return m_FullPath;
	}

	int FullPathSize()
	{
		return (int)m_FullPath.size();
	}

	void MoveParent();
	
	bool Move(const wchar_t* _folderName);

	bool IsFile(const wchar_t* _fileName);

public:
	//std::vector<std::wstring> AllFiles();

public:
	bDirect(const bDirect& _other);
	bDirect();
	~bDirect();
};

