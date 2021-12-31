#pragma once
#include "Actor.h"
#include <vector>

class GameRender;
class TransRender;
class AniRender;

class MsgWindow :
	public Actor
{
public:
	static MsgWindow* MsgWin;
	static void MsgEv(int _msgNumStart, int msgNumEnd);

private:
	static int StartNum;
	static int EndNum;
	static std::vector<int> MsgVector;

	float CountMsg;

private:
	TransRender* m_Face;
	TransRender* m_Msg;

public:
	bool init() override;
	void Update() override;

public:
	MsgWindow();
	~MsgWindow();
};
