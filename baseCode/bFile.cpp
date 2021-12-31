#include "bFile.h"


bFileStream::bFileStream(const char* _fileName, const char* _mode)
{
	fopen_s(&filePtr, _fileName, _mode);
}

bFileStream::bFileStream(const wchar_t* _fileName, const wchar_t* _mode)
{
	_wfopen_s(&filePtr, _fileName, _mode);
}

bFileStream::~bFileStream()
{
	if (nullptr != filePtr)
		fclose(filePtr);
}

bFileStream_W::bFileStream_W(const char* _fileName) : bFileStream(_fileName, "wb") {}
bFileStream_W::bFileStream_W(const wchar_t* _fileName) : bFileStream(_fileName, L"wb") {}

bFileStream_R::bFileStream_R(const char* _fileName) : bFileStream(_fileName, "rb") {}
bFileStream_R::bFileStream_R(const wchar_t* _fileName) : bFileStream(_fileName, L"rb") {}