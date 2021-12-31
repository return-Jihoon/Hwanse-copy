#include "bIO.h"

bool bIO::isFile(const char* _fileName)
{
	return _access_s(_fileName, 0) == 0;
}
bool bIO::isFile(const wchar_t* _fileName)
{
	return _waccess_s(_fileName, 0) == 0;
}
