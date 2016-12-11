#include "stdafx.h"
#include "cMonster.h"
#include "cUIObject.h"
#include "cUITextView.h"
#include "cUIImageView.h"


cMonster::cMonster(char* szFolder, char* szFilename)
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
	, m_pUIHp(NULL)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::cMonster()
	: m_fDetectRange(0.0f)
{
	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::~cMonster()
{
}


void cMonster::Update()
{
	if (m_pUIHp)
	{
		float fHpRatio = m_stInfo.fHp / m_stInfo.fMaxHp;

		char szStr[16] = { '\0', };
		sprintf_s(szStr, sizeof(szStr), "%.0f%%", fHpRatio * 100);
		((cUITextView*)m_pUIHp->FindChildByTag(2))->SetText(szStr);
		((cUIImageView*)m_pUIHp->FindChildByTag(1))->SetScaleX(fHpRatio);
	}
}


void cMonster::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
	cDynamicObj::UpdateAndRender(pmat);
}