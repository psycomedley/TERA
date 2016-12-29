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
		string str = "���۰��Ӹ� : Tera\n\n";
		str += "���۱Ⱓ : 11/25 ~ 12/28\n\n";
		str += "���� : ��ȣ��\n";
		str += "���� : �����, ȫ�⼱\n\n";
		
		str += "��ȣ��\n";
		str += "- �� / ����\n";
		str += "- ��ī�̹ڽ�\n";
		str += "- ������Ʈ ��\n\n";

		str += "�����\n";
		str += "- �÷��̾� ��Ÿ / ��ų ����Ʈ\n\n";

		str += "ȫ�⼱\n";
		str += "- �����ӿ�ũ ����\n";
		str += "- ī�޶� �Ŵ���\n";
		str += "- �÷��̾� / ����\n";
		str += "- �÷��̾� / ���� HP UI\n";
		str += "- �ؽ�Ʈ �Ŵ���\n";
		str += "- ���� �Ŵ���\n";
		str += "- ���̴� ����Ʈ\n";
		str += "- �̺�Ʈ �Ŵ���(�ƾ�..?)\n\n\n";

		str += "�� �� �Ұ�\n\n";

		str += "��ȣ��\n";
		str += "�̹��� ������ ������ϴ�!\n\n";
		str += "�����\n";
		str += "�� �����ϰ� �ͽ��ϴ�.\n\n";
		str += "ȫ�⼱\n";
		str += "������ ����� ���ݸ��鿡�� ���Ǹ� ǥ�մϴ�.\n\n\n";

		str += "���ּż� �����մϴ�.";

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