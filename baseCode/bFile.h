#pragma once
#include <iostream>
#include "bIO.h"

class bFileStream
{
protected:
	FILE* filePtr;

public:
	bool isOpen()
	{
		return nullptr != filePtr;
	}

public:
	bFileStream(const char* _fileName, const char* _mode);
	bFileStream(const wchar_t* _fileName, const wchar_t* _mode);
	virtual ~bFileStream();
};

class bFileStream_W : public bFileStream
{
public:
	template<typename T>
	void operator << (const T& _data)
	{
		fwrite(&_data, sizeof(T), 1, filePtr);
	}

public:
	bFileStream_W(const char* _fileName);
	bFileStream_W(const wchar_t* _fileName);
	~bFileStream_W() {}
};

class bFileStream_R : public bFileStream
{
public:
	template<typename T>
	void operator >> (T& _data)
	{
		fread_s(&_data, sizeof(T), sizeof(T), 1, filePtr);
	}

public:
	bFileStream_R(const char* _fileName);
	bFileStream_R(const wchar_t* _fileName);
	~bFileStream_R() {}
};