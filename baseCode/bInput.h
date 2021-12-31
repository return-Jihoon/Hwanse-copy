#pragma once
#include <string>
#include <vector>
#include <map>
#include <assert.h>

class Input
{
private: 
	class Destructor
	{
	public:
		~Destructor()
		{
			Input::InputEnd();
		}
	};
	static Destructor DES;
	friend Destructor;

private:
	class Key
	{
	private:
		friend Input;

	public:
		bool m_Up;
		bool m_UpAway;
		bool m_Down;
		bool m_Press;
		std::vector<int> m_KeyArray;

	public:
		bool IskeyCheck();
		void Update();

	private:
		Key();
		~Key();
	};

private:
	static std::map<std::wstring, Key*>::iterator KeyStart;
	static std::map<std::wstring, Key*>::iterator KeyEnd;
	static std::map<std::wstring, Key*> m_AllKey;

	static void InputEnd();

private:
	static Key* FindKey(const wchar_t* _name);

public:
	static void Update();

public:
	static Key* NewKey;

	template<typename ...Rest>
	static void CreateKey(const wchar_t* _name, Rest ..._arg)
	{
		NewKey = FindKey(_name);

		if (nullptr != NewKey)
		{
			assert(false);
		}

		NewKey = new Key();

		NewKey->m_KeyArray.reserve(sizeof...(_arg));
		PushKey(_arg...);

		m_AllKey.insert(std::map<std::wstring, Key*>::value_type(_name, NewKey));
	}
	template<typename ...Rest>
	static void PushKey(int _key, Rest ..._arg)
	{
		NewKey->m_KeyArray.push_back(_key);
		PushKey(_arg...);
	}

	static void PushKey() {}

public:
	static bool Down(const wchar_t* _name);
	static bool Press(const wchar_t* _name);
	static bool Up(const wchar_t* _name);
	static bool UpAway(const wchar_t* _name);

public:
	Input();
	~Input();
};

