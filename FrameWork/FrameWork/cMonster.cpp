#include "stdafx.h"
#include "cMonster.h"
#include "cUIObject.h"
#include "cUITextView.h"
#include "cUIImageView.h"


cMonster::cMonster(char* szFolder, char* szFilename)
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
	, m_pUIHp(NULL)
	, m_pShotSphere(NULL)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::cMonster()
	: m_fDetectRange(0.0f)
	, m_pShotSphere(NULL)
{
	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::~cMonster()
{
	SAFE_DELETE(m_pShotSphere);
}


void cMonster::Update()
{
	if (m_pUIHp)
	{
		float fHpRatio = m_stInfo.fHp / m_stInfo.fMaxHp;

		char szStr[16] = { '\0', };
		sprintf_s(szStr, sizeof(szStr), "%.0f%%", fHpRatio * 100);
		((cUITextView*)m_pUIHp->FindChildByTag(E_UITAG_HPTEXT))->SetText(szStr);
		((cUIImageView*)m_pUIHp->FindChildByTag(E_UITAG_HP))->SetScaleX(fHpRatio);
	}
}


void cMonster::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
//	if (m_fPassedVanishTime < 1.0f)
		cDynamicObj::UpdateAndRender(pmat);
}


cBoundingSphere cMonster::GetShotSphere()
{
	cBoundingSphere sphere;
	sphere.SetCenter(m_vPosition);
	sphere.SetRadius(m_pShotSphere->GetRadius());
	return sphere;
}


void cMonster::SetShotSphere(float fRadius)
{
	m_pShotSphere = new cBoundingSphere;
	m_pShotSphere->SetRadius(fRadius);
}


void cMonster::ResetHp()
{
	m_stInfo.fHp = m_stInfo.fMaxHp;
}