#include "stdafx.h"
#include "cGuardian.h"
#include "cDynamicObj.h"
#include "cStateWait.h"
#include "cStateRun.h"
#include "cStateDeath.h"
#include "cStateBossSkill.h"
#include "cActionMoveToAttack.h"

cGuardian::cGuardian(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
	SetupStatus();
}


cGuardian::cGuardian()
{
}


cGuardian::~cGuardian()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cGuardian::SetupState()
{
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_DEATH] = new cStateDeath;
	m_aStates[E_STATE_DEATH]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cGuardian::SetupStatus()
{
	m_stInfo.sName = "Guardian";
	
	m_stInfo.fMaxHp = 1000;
	m_stInfo.fHp = m_stInfo.fMaxHp;
	m_stInfo.fMaxMp = 100;
	m_stInfo.fMp = m_stInfo.fMaxMp;

	m_stInfo.fMaxDamage = 78.0f;
	m_stInfo.fMinDamage = 58.0f;
	m_stInfo.fDefence = 8.0f;

	m_fDetectRange = 15.0f;

	m_skillRush.SetInfo(10.0f, 100);
}


void cGuardian::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cGuardian::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{

}


void cGuardian::ChangeState(int pState, int nSkillIndex /*= -1*/)
{

}


bool cGuardian::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cGuardian::Update()
{
	cMonster::Update();

	//������
	if (!m_bIsBattle)
	{
		D3DXVECTOR3 distance = m_vPosition - GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();
		if (D3DXVec3Length(&distance) < m_fDetectRange)
		{
			m_bIsBattle = true;
			m_pTarget = GETSINGLE(cObjMgr)->GetPlayer();
			ChangeState(E_STATE_WAIT);
		}
	}
	//����
	else
	{
		float fElapsedTime = GETSINGLE(cTimeMgr)->getElapsedTime();
		m_skillRush.fPassedTime += fElapsedTime;

		if (IsMoveAble())
		{
			if (m_skillRush.fPassedTime >= m_skillRush.fCoolTime)
			{
				if (m_pAction)
					SAFE_RELEASE(m_pAction);
				m_skillRush.fPassedTime = 0.0f;
				LookTarget();
				ChangeState(E_STATE_SKILL, E_ANI_SKILL1);
				return;
			}
			if (m_skillAttack.fPassedTime >= m_skillAttack.fCoolTime)
			{
				if (IsTargetCollision())
				{
					if (m_pAction)
						SAFE_RELEASE(m_pAction);
					m_skillAttack.fPassedTime = 0.0f;
					LookTarget();
					ChangeState(E_STATE_SKILL, E_ANI_ATTACK);
					return;
				}
				else
				{
					cActionMoveToAttack* pActionMove = new cActionMoveToAttack;
					pActionMove->SetFrom(m_vPosition);
					pActionMove->SetTo(m_pTarget->GetPosition());
					float fDist = D3DXVec3Length(&(m_vPosition - m_pTarget->GetPosition()));
					pActionMove->SetActionTime(fDist * 0.2);
					pActionMove->SetTarget(this);
					SetAction(pActionMove);
					SAFE_RELEASE(pActionMove);
					return;
				}
			}
			LookTarget();
		}
	}
}