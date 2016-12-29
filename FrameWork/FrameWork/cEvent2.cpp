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
		if (m_fPassedTime >= 55.0f)
		{
			Next();
		}
	}
}


void cEvent2::Play()
{
	if (!m_bPlayed)
	{
		m_bProcess = true;

		cText* pText = new cText;
		string str = "모작게임명 : Tera\n\n";
		str += "제작기간 : 11/25 ~ 12/28\n\n";
		str += "조장 : 송호정\n";
		str += "조원 : 설재규, 홍기선\n\n";
		
		str += "송호정\n";
		str += "- 맵 / 광원\n";
		str += "- 스카이박스\n";
		str += "- 오브젝트 툴\n\n";

		str += "설재규\n";
		str += "- 플레이어 평타 / 스킬 이펙트\n\n";

		str += "홍기선\n";
		str += "- 프레임워크 제작\n";
		str += "- 카메라 매니져\n";
		str += "- 플레이어 / 몬스터\n";
		str += "- 플레이어 / 몬스터 HP UI\n";
		str += "- 텍스트 매니져\n";
		str += "- 사운드 매니져\n";
		str += "- 셰이더 이펙트\n";
		str += "- 이벤트 매니져(컷씬..?)\n\n\n";

		str += "한 줄 소감\n\n";

		str += "송호정\n";
		str += "이번에 많은걸 배웠습니다!\n\n";
		str += "설재규\n";
		str += "더 발전하고 싶습니다.\n\n";
		str += "홍기선\n";
		str += "나에게 희생된 초콜릿들에게 조의를 표합니다.\n\n\n";

		str += "봐주셔서 감사합니다.";

		pText->Setup(E_FONT_EVENT2, "Ending", str,
			D3DXVECTOR2(400, GetWindowHeight() + 500),
			ST_SIZE(700, 850), XWHITE,
			TEXT_MOVE | TEXT_SHOWTIME,
			DT_WORDBREAK | DT_VCENTER);
		pText->SetShowTime(60.0f);
	//	pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(0.5f);
		pText->SetDirection(DIRECTION_UP);
		
//		pText->SetMoveTime(2.5f);
//		pText->SetShowAfterTime(1.5f);
//		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);

		GETSINGLE(cTextMgr)->AddList("Ending");

		m_bPlayed = true;

//		GETSINGLE(cUIMgr)->RemoveList("CrossHair");
//		GETSINGLE(cUIMgr)->RemoveList("Player");
	}
}


void cEvent2::Next()
{
	m_fPassedTime = 0.0f;
	cText* pText = new cText;

	pText->Setup(E_FONT_EVENT3, "Fin", "Fin",
		D3DXVECTOR2(GetWindowWidth() / 2, GetWindowHeight() / 2 - 50),
		ST_SIZE(300, 300), XWHITE,
		TEXT_ALPHA | TEXT_SHOWTIME | TEXT_SHOWAFTERTIME | TEXT_APPEARWITHALPHA);
	pText->SetShowTime(2.0f);
	pText->SetAlphaTime(2.0f);
	pText->SetShowAfterTime(0.5f);
	pText->SetAppearTime(2.0f);
	GETSINGLE(cTextMgr)->AddText(pText);

	GETSINGLE(cTextMgr)->AddList("Fin");
}