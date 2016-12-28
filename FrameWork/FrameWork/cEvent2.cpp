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
		string str = "모작게임명 : Tera\n\n";
		str += "제작기간 : 11/25 ~ 12/28";
		str += "조장 : 송호정\n";
		str += "조원 : 홍기선, 설재규\n\n";
		
		str += "송호정\n";
		str += "- \n";
		str += "- \n\n";

		str += "홍기선\n";
		str += "- 프레임워크 제작\n";
		str += "- 카메라 매니져\n";
		str += "- 플레이어 / 몬스터\n";
		str += "- 플레이어 / 몬스터 HP UI\n";
		str += "- 텍스트 매니져\n";
		str += "- 사운드 매니져\n";
		str += "- 이펙트\n";
		str += "- 이벤트 매니져(컷신..?)\n\n";

		str += "설재규\n";
		str += "- \n";
		str += "- \n";

		pText->Setup(E_FONT_EVENT, "Ending", str, D3DXVECTOR2(GetWindowWidth() / 2, GetWindowHeight() + 200), ST_SIZE(500, 700), XWHITE,
			TEXT_MOVE | TEXT_SHOWTIME);
		pText->SetShowTime(60.0f);
	//	pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(0.5f);
		pText->SetDirection(DIRECTION_UP);
	//	pText->SetMoveTime(2.5f);
//		pText->SetShowAfterTime(1.5f);
//		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);

		GETSINGLE(cTextMgr)->AddList("Ending");

		m_bPlayed = true;

//		GETSINGLE(cUIMgr)->RemoveList("CrossHair");
//		GETSINGLE(cUIMgr)->RemoveList("Player");
	}
}