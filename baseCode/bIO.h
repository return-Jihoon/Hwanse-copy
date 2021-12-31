#pragma once
#include <iostream>
#include <io.h>

class bIO
{
public:
	static bool isFile(const char* _fileName);
	static bool isFile(const wchar_t* _fileName);

public:
	bIO();
	~bIO();
};

