#include "bDirect.h"
#include <assert.h>
#include <Windows.h>


bDirect::bDirect()
{
	wchar_t Arr[1000];
	GetCurrentDirectoryW(1000, Arr);
	m_FullPath = Arr;
}

bDirect::bDirect(const bDirect& _other) : m_FullPath(_other.m_FullPath)
{ }


bDirect::~bDirect()
{
}

void bDirect::MoveParent()
{
	size_t CutCount = m_FullPath.find_last_of(L"\\", m_FullPath.size());

	m_FullPath.replace(CutCount, m_FullPath.size(), L"");
}

bool bDirect::Move(const wchar_t* _folderName)
{
	std::wstring FindPath = m_FullPath + L"\\" + _folderName;

	if (false == bIO::isFile(FindPath.c_str()))
	{
		assert(false);
		return false;
	}

	m_FullPath = FindPath;
	return true;
}

std::wstring bDirect::FolderName()
{
	std::wstring FolderName = m_FullPath;

	size_t CutCount = FolderName.find_last_of(L"\\", m_FullPath.size());
	FolderName.replace(0, CutCount + 1, L"");
	return FolderName;
}

bool bDirect::IsFile(const wchar_t* _fileName)
{
	return bIO::isFile((m_FullPath + L"\\" + _fileName).c_str());
}

/*std::vector<std::wstring> bDirect::AllFiles()
{
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".\\*.*", &fd);

	if (handle == -1)
	{
		printf("There were no files.\n");
		return;
	}

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		result = _findnext(handle, &fd);
	}

	_findclose(handle);
	return;
}*/