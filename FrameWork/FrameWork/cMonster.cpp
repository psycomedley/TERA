#include "stdafx.h"
#include "cMonster.h"


cMonster::cMonster(char* szFolder, char* szFilename)
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
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

}


void cMonster::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
	cDynamicObj::UpdateAndRender(pmat);
}


void cMonster::LookTarget()
{
	if (m_pTarget)
	{
		D3DXVECTOR3 vTargetPos = m_pTarget->GetPosition();
		m_vDirection = m_vPosition - vTargetPos;
		D3DXVec3Normalize(&m_vDirection, &m_vDirection);

		float nX = vTargetPos.x - m_vPosition.x;
		float nZ = vTargetPos.z - m_vPosition.z;

		m_fAngle = D3DX_PI / 2 - atan2(nZ, nX);
	}
}