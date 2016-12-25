#include "stdafx.h"
#include "cGardener.h"
#include "cDynamicObj.h"
#include "cStateIdle.h"
#include "cStateWait.h"
#include "cStateRun.h"
#include "cStateDeath.h"
#include "cStateHit.h"
#include "cStateMonsterSkill2.h"
#include "cActionMoveToAttack.h"

cGardener::cGardener(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
	SetupStatus();
	SetBox();
	SetSound();
}


cGardener::cGardener()
{
	SetupState();
	SetupStatus();
	SetBox();
	SetSound();
}


cGardener::~cGardener()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cGardener::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	((cStateRun*)m_aStates[E_STATE_RUN])->GetVecTiming()->push_back(0.32f);
	((cStateRun*)m_aStates[E_STATE_RUN])->GetVecTiming()->push_back(0.78f);
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_DEATH] = new cStateDeath;
	m_aStates[E_STATE_DEATH]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateMonsterSkill2;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	m_aStates[E_STATE_HIT] = new cStateHit;
	m_aStates[E_STATE_HIT]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cGardener::SetupStatus()
{
	m_stInfo.sName = "Gardener";

	m_stInfo.fMaxHp = 1000;
	m_stInfo.fHp = m_stInfo.fMaxHp;
	m_stInfo.fMaxMp = 100;
	m_stInfo.fMp = m_stInfo.fMaxMp;

	m_stInfo.fMaxDamage = 78.0f;
	m_stInfo.fMinDamage = 58.0f;
	m_stInfo.fDefence = 8.0f;

	m_fDetectRange = 15.0f;

	m_skillRush.SetInfo(10.0f, 100);
	m_skillAttack.SetInfo(3.0f, 50);
}


void cGardener::SetSound()
{
	string sKey = m_stInfo.sName + "_Atk";
	m_eSoundKey[E_SOUND_ATK] = sKey;
	GETSINGLE(cSoundMgr)->Add(sKey, "Sound/" + sKey + ".ogg");
	sKey = m_stInfo.sName + "_Death";
	m_eSoundKey[E_SOUND_DEATH] = sKey;
	GETSINGLE(cSoundMgr)->Add(sKey, "Sound/" + sKey + ".ogg");
	sKey = m_stInfo.sName + "_Hit";
	m_eSoundKey[E_SOUND_HIT] = sKey;
	GETSINGLE(cSoundMgr)->Add(sKey, "Sound/" + sKey + ".ogg");
	sKey = m_stInfo.sName + "_Run";
	m_eSoundKey[E_SOUND_RUN] = sKey;
	GETSINGLE(cSoundMgr)->Add(sKey, "Sound/" + sKey + ".ogg");
}


void cGardener::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
	m_pState->Update();
	cMonster::UpdateAndRender(pmat);
}


void cGardener::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == pState)
			return;

	iState* pPrevState = m_pState;
	m_pState = pState;

	if (pPrevState && pState != m_aStates[E_STATE_DEATH])
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
		((cStateMonsterSkill2*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


void cGardener::ChangeState(int pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == m_aStates[pState])
			return;

	iState* pPrevState = m_pState;
	m_pState = m_aStates[pState];

	if (pPrevState && pState != E_STATE_DEATH)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
	{
		((cStateMonsterSkill2*)m_pState)->SetSkillIndex(nSkillIndex);
	}

	m_pState->Start();
}


bool cGardener::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_IDLE] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cGardener::Update()
{
	cMonster::Update();

	//비전투
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
	//전투
	else
	{
		float fElapsedTime = GETSINGLE(cTimeMgr)->getElapsedTime();
		m_skillRush.fPassedTime += fElapsedTime;
		m_skillAttack.fPassedTime += fElapsedTime;

		if (IsMoveAble())
		{
			if (m_skillAttack.fPassedTime >= m_skillAttack.fCoolTime)
			{
				if (IsTargetBoxCollision())
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
