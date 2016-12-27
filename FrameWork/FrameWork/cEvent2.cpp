#include "stdafx.h"
#include "cEvent2.h"
#include "cText.h"


cEvent2::cEvent2()
{
}


cEvent2::~cEvent2()
{
}


void cEvent2::Update()
{
	if (m_bProcess)
	{
		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();
	}
}


void cEvent2::Play()
{
	if (!m_bPlayed)
	{
		m_bProcess = true;

		cText* pText = new cText;
		pText->Setup(E_FONT_EVENT, "Ending", "산책나온", D3DXVECTOR2(GetWindowWidth() / 2, GetWindowHeight()), ST_SIZE(200, 50), XWHITE,
			TEXT_MOVE | TEXT_SHOWTIME);
		pText->SetShowTime(60.0f);
	//	pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(0.5f);
		pText->SetDirection(DIRECTION_UP);
	//	pText->SetMoveTime(2.5f);
//		pText->SetShowAfterTime(1.5f);
//		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);

		/*pText = new cText;
		pText->Setup(E_FONT_EVENT, "Event2", " 오르카", D3DXVECTOR2(GetWindowWidth() / 2 + 70, 600), ST_SIZE(200, 50), XWHITE,
			TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME | TEXT_SHOWAFTERTIME | TEXT_APPEARWITHALPHA);
		pText->SetShowTime(3.0f);
		pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(1.5f);
		pText->SetDirection(DIRECTION_RIGHT);
		pText->SetMoveTime(2.5f);
		pText->SetShowAfterTime(1.5f);
		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);*/

		GETSINGLE(cTextMgr)->AddList("Ending");
//		GETSINGLE(cTextMgr)->AddList("Event2");

		m_bPlayed = true;

		GETSINGLE(cUIMgr)->RemoveList("CrossHair");
		GETSINGLE(cUIMgr)->RemoveList("Player");
	}
}