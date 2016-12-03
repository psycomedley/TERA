#include "stdafx.h"
#include "cBoss.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cStateBossSkill.h"
#include "cAnimationController.h"
#include "cActionMoveToAttack.h"


cBoss::cBoss(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
	SetupStatus();
}


cBoss::cBoss()
{
}


cBoss::~cBoss()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cBoss::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cBoss::SetupStatus()
{
	m_stInfo.sName = "Orca";

	m_stInfo.nMaxHp = 100;
	m_stInfo.nHp = m_stInfo.nMaxHp;
	m_stInfo.nMaxMp = 100;
	m_stInfo.nMp = m_stInfo.nMaxMp;

	m_stInfo.fDamage = 100.0f;
	m_stInfo.fDefence = 100.0f;

	m_fDetectRange = 15.0f;

	m_skillLongMove.SetInfo(30.0f, 100);
	m_skillHeavyAtk.SetInfo(15.0f, 100);
	m_skillAttack.SetInfo(3.0f, 10);
}


void cBoss::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cBoss::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == pState)
			return;

	if (m_pState)
		m_pState->End();

	m_pState = pState;
	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	m_pState->Start();
}


void cBoss::ChangeState(int pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == m_aStates[pState])
			return;

	iState* pPrevState = m_pState;
	m_pState = m_aStates[pState];

	if (pPrevState)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
		((cStateBossSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


bool cBoss::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_IDLE] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cBoss::Update()
{
	cMonster::Update();

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
	else
	{
		float fElapsedTime = GETSINGLE(cTimeMgr)->getElapsedTime();
		m_skillHeavyAtk.fPassedTime += fElapsedTime;
		m_skillLongMove.fPassedTime += fElapsedTime;
		m_skillAttack.fPassedTime += fElapsedTime;

		if (IsMoveAble())
		{
			if (m_skillLongMove.fPassedTime >= m_skillLongMove.fCoolTime)
			{
				m_skillLongMove.fPassedTime = 0.0f;
				LookTarget();
				ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
			}
			else if (m_skillHeavyAtk.fPassedTime >= m_skillHeavyAtk.fCoolTime)
			{
				m_skillHeavyAtk.fPassedTime = 0.0f;
				LookTarget();
				ChangeState(E_STATE_SKILL, E_BOSS_HEAVYATK_START);
			}
			else if (m_skillAttack.fPassedTime >= m_skillAttack.fCoolTime)
			{
				if (IsTargetCollision())
				{
					if (m_pAction)
						SAFE_RELEASE(m_pAction);
					m_skillAttack.fPassedTime = 0.0f;
					LookTarget();
					ChangeState(E_STATE_SKILL, E_BOSS_ATK1);
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
				}
			}
			else
			{
				LookTarget();
			}
		}
	}
}