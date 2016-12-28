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
		string str = "���۰��Ӹ� : Tera\n\n";
		str += "���۱Ⱓ : 11/25 ~ 12/28";
		str += "���� : ��ȣ��\n";
		str += "���� : ȫ�⼱, �����\n\n";
		
		str += "��ȣ��\n";
		str += "- \n";
		str += "- \n\n";

		str += "ȫ�⼱\n";
		str += "- �����ӿ�ũ ����\n";
		str += "- ī�޶� �Ŵ���\n";
		str += "- �÷��̾� / ����\n";
		str += "- �÷��̾� / ���� HP UI\n";
		str += "- �ؽ�Ʈ �Ŵ���\n";
		str += "- ���� �Ŵ���\n";
		str += "- ����Ʈ\n";
		str += "- �̺�Ʈ �Ŵ���(�ƽ�..?)\n\n";

		str += "�����\n";
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