#pragma once
#include <map>

class bTemplate
{
public:
	template<typename Return, typename Key, typename Map>
	static Return* MapFindToPointer(Key& _key, Map& _map)
	{
		typename Map::iterator FindIter = _map.find(_key);

		if (FindIter == _map.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

private:
	bTemplate();
	~bTemplate();
};

