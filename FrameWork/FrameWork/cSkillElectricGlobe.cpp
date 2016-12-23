#include "stdafx.h"
#include "cSkillElectricGlobe.h"
#include "iState.h"
#include "cStateWait.h"
#include "cStateDeath.h"
#include "cEffect.h"


cSkillElectricGlobe::cSkillElectricGlobe()
	: m_bActive(false)
	, m_pEffect(NULL)
	, m_fPassedTime(0.0f)
{
}


cSkillElectricGlobe::~cSkillElectricGlobe()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cSkillElectricGlobe::Setup()
{
	SetupState();
	SetupStatus();
}


void cSkillElectricGlobe::Update()
{
	if (m_pState == m_aStates[E_STATE_WAIT])
	{
		cBoundingSphere sphere;
		sphere.SetCenter(m_vPosition);
		sphere.SetRadius(5.0f);


		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();
		if (m_fPassedTime >= 2.5f)
		{
			D3DXMATRIXA16 matR, matI;
			D3DXMatrixRotationX(&matR, D3DX_PI / 2);
			D3DXMatrixIdentity(&matI);
			D3DXVECTOR3 vec = m_pEffect->GetPosition();

			vec.y = m_vPosition.y;

			GETSINGLE(cBattleMgr)->EnemyDamage(this, sphere, true);
			GETSINGLE(cEffectMgr)->AddList("GlobeAtk", vec, matR);
		//	GETSINGLE(cEffectMgr)->AddList("GlobeAtk2", vec, matI);
			m_fPassedTime -= 2.5f;
		}
	}
}


void cSkillElectricGlobe::SetupState()
{
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_DEATH] = new cStateDeath;
	m_aStates[E_STATE_DEATH]->SetParent(this);
	ChangeState(E_STATE_WAIT);
}


void cSkillElectricGlobe::SetupStatus()
{
	m_stInfo.sName = "Globe";

	m_stInfo.fMaxHp = 500;
	m_stInfo.fHp = m_stInfo.fMaxHp;
	m_stInfo.fMaxMp = 100;
	m_stInfo.fMp = m_stInfo.fMaxMp;

	m_stInfo.fMaxDamage = 96.0f;
	m_stInfo.fMinDamage = 52.0f;
	m_stInfo.fDefence = 8.0f;
}


void cSkillElectricGlobe::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == pState)
			return;

	iState* pPrevState = m_pState;
	m_pState = pState;

	if (pPrevState)
		pPrevState->End();

	m_pState->Start();
}


void cSkillElectricGlobe::ChangeState(int pState, int nSkillIndex /*= -1*/)
{
	m_pState = m_aStates[pState];

	if (pState == E_STATE_DEATH)
	{
		m_pEffect->NextTech();
		GETSINGLE(cObjMgr)->AddInMonsterPoolFromMap("Globe", this);
	}


	if (m_pState)
		if (m_pState == m_aStates[pState])
			return;

	iState* pPrevState = m_pState;
	m_pState = m_aStates[pState];

	if (pPrevState)
		pPrevState->End();

	m_pState->Start();
}


bool cSkillElectricGlobe::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cSkillElectricGlobe::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
//	m_pState->Update();
//	cDynamicObj::UpdateAndRender(pmat);
}