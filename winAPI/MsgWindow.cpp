#include "MsgWindow.h"
#include <Windows.h>
#include <bTime.h>
#include <bInput.h>
#include "ImageRender.h"
#include "TransRender.h"
#include "GameCore.h"
#include <bWindow.h>



MsgWindow::MsgWindow() : CountMsg(0.0f)
{
}


MsgWindow::~MsgWindow()
{
}

MsgWindow* MsgWindow::MsgWin = nullptr;
std::vector<int> MsgWindow::MsgVector = {	0,2,1,0,0,
											2,9,1,2,9, //10
											9,9,0,9,1,
											9,1,9,0,9, //20
											0,9,1,9,9,
											0,9,1,9,9, //30
											0,1,2,9,9,
											9,1,0,2,9, //40
											9,0,9,9,9,
											0,0,0,1,0, //50
											0,0,0,0,0,
											0,0,0,0,0 //60
};
int MsgWindow::StartNum = 0;
int MsgWindow::EndNum = 0;

void MsgWindow::MsgEv(int _msgNumStart, int msgNumEnd)
{
	if (nullptr == MsgWin || true == MsgWin->IsUpdate())
		return;

	MsgWin->On();

	StartNum = _msgNumStart;
	EndNum = msgNumEnd;

}

bool MsgWindow::init()
{
	m_Face = CreateRender<TransRender>(3000);
	m_Face->RenderPosMode(Pivot::LT);
	m_Face->Sprite(L"Faces.bmp", 0);
	m_Face->RenderPos({ 56.0f, 240.0f });

	m_Msg = CreateRender<TransRender>(3001);
	m_Msg->RenderPosMode(Pivot::LT);
	m_Msg->Sprite(L"Faces.bmp", 0);
	m_Msg->RenderPos({ 144.0f, 240.0f });

	m_Face->CamerEffectOff();
	m_Msg->CamerEffectOff();

	return true;
}
void MsgWindow::Update()
{
	if (3 > MsgVector[StartNum] && 0 <= MsgVector[StartNum])
	{
		MsgWin->m_Face->On();
		MsgWin->m_Face->Sprite(L"Faces.bmp", MsgVector[StartNum]);
	}
	else
		MsgWin->m_Face->Off();

	MsgWin->m_Msg->Sprite(L"MsgV.bmp", StartNum);
	CountMsg += 1.0f * bTime::DeltaTime();

	
	if (2.5f < CountMsg || true == Input::Down(L"ENTER"))
	{
		CountMsg = 0.0f;
		if (++StartNum > EndNum)
		{
			MsgWin->Off();
			return;
		}
	}
}