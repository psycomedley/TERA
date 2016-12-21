#include "stdafx.h"
#include "cOrca.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cStateBossSkill.h"
#include "cStateDeath.h"
#include "cAnimationController.h"
#include "cActionMoveToAttack.h"
#include "cOrcaClone.h"
#include "cText.h"


cOrca::cOrca(char* szFolder, char* szFilename)
	: m_nNumClone(0)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
	SetupStatus();
}


cOrca::cOrca()
	: m_nNumClone(0)
{
}


cOrca::~cOrca()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cOrca::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	m_aStates[E_STATE_DEATH] = new cStateDeath;
	m_aStates[E_STATE_DEATH]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cOrca::SetupStatus()
{
	m_stInfo.sName = "Orca";

	m_stInfo.fMaxHp = 10000;
	m_stInfo.fHp = m_stInfo.fMaxHp;
	m_stInfo.fMaxMp = 100;
	m_stInfo.fMp = m_stInfo.fMaxMp;

	m_stInfo.fMaxDamage = 156.0f;
	m_stInfo.fMinDamage = 119.0f;
	m_stInfo.fDefence = 8.0f;

	m_fDetectRange = 15.0f;

	m_skillLongMove.SetInfo(60.0f, 100);
	m_skillLongMove.sSpeech = "나의 속도를 쬐끔만 느껴보아라!!";
//	GETSINGLE(cTextMgr)->AddAlphaText(E_FONT_BOSS, m_skillLongMove.sSpeech, m_skillLongMove.sSpeech, 3, D3DXVECTOR2(GetWindowWidth() / 2, 150), ST_SIZE(500, 50), XWHITE, TEXT_MOVEUP, 255, 1.0f);
	cText* pText = new cText;
	pText->Setup(E_FONT_BOSS, m_skillLongMove.sSpeech, m_skillLongMove.sSpeech, 
		D3DXVECTOR2(GetWindowWidth() / 2, 150), ST_SIZE(500, 50), 
		XWHITE, TEXT_SHOWTIME | TEXT_ALPHA | TEXT_MOVE | TEXT_MOVEAFTERTIME);
	pText->SetShowTime(3.0f);
	pText->SetAlphaTime(1.0f);
	pText->SetMoveSpeed(0.3f);
	pText->SetDirection(DIRECTION_UP);
	pText->SetMoveTime(3.0f);
	GETSINGLE(cTextMgr)->AddText(pText);

	m_skillHeavyAtk.SetInfo(35.0f, 100);
	
	m_skillHeavyAtk2.SetInfo(25.0f, 100);

	m_skillAttack.SetInfo(3.0f, 10);

	m_skillBackAtk.SetInfo(8.0f, 25);
}


void cOrca::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cOrca::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == pState)
			return;

	iState* pPrevState = m_pState;
	m_pState = pState;

	if (pPrevState)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
		((cStateBossSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


void cOrca::ChangeState(int pState, int nSkillIndex /*= -1*/)
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


bool cOrca::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_IDLE] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cOrca::Update()
{
	cMonster::Update();

	//비전투
	if (!m_bIsBattle)
	{
		D3DXVECTOR3 distance = m_vPosition - GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();
		if (D3DXVec3Length(&distance) < m_fDetectRange)
		{
			GETSINGLE(cUIMgr)->AddList("Orca");
			m_pUIHp = GETSINGLE(cUIMgr)->GetUIInList("Orca");
			m_bIsBattle = true;
			m_pTarget = GETSINGLE(cObjMgr)->GetPlayer();
			ChangeState(E_STATE_WAIT);
		}
	}
	//전투
	else
	{
		float fElapsedTime = GETSINGLE(cTimeMgr)->getElapsedTime();
		m_skillHeavyAtk.fPassedTime += fElapsedTime;
		m_skillLongMove.fPassedTime += fElapsedTime;
		m_skillAttack.fPassedTime += fElapsedTime;
		m_skillHeavyAtk2.fPassedTime += fElapsedTime;
		m_skillBackAtk.fPassedTime += fElapsedTime;

		if (IsMoveAble())
		{
			if (m_nNumClone > 0)
			{
				m_nNumClone = 3;
				auto cloneList = GETSINGLE(cObjMgr)->GetMonsterList("Orca_Clone");
	
				for (auto iter = cloneList->begin(); iter != cloneList->end(); iter++)
				{
					if (((cOrcaClone*)(*iter))->GetMoveEnd())
						m_nNumClone--;

//					if (!((cOrcaClone*)(*iter))->GetActive())
//					m_nNumClone--;
				}
				if (m_nNumClone == 0)
				{
					for (auto iter = cloneList->begin(); iter != cloneList->end(); iter++)
					{
//						((cOrcaClone*)(*iter))->SetActive(false);
						((cOrcaClone*)(*iter))->ChangeState(E_STATE_DEATH);
					}
				}

				return;
			}

			if (IsBehind())
			{
				if (IsTargetCollision())
				{
					if (m_skillBackAtk.fPassedTime >= m_skillBackAtk.fCoolTime)
					{
						if (m_pAction)
							SAFE_RELEASE(m_pAction); 
						m_skillBackAtk.fPassedTime = 0.0f;
						ChangeState(E_STATE_SKILL, E_BOSS_BACKATK);
						return;
					}
				}
			}
			if (m_skillLongMove.fPassedTime >= m_skillLongMove.fCoolTime)
			{
				//나중에 일정 체력 이하일 때로 변경 50%, 25%
				if (m_pAction)
					SAFE_RELEASE(m_pAction); 
				LongMove();
				return;
			}
			if (m_skillHeavyAtk.fPassedTime >= m_skillHeavyAtk.fCoolTime)
			{
				if (m_pAction)
					SAFE_RELEASE(m_pAction); 
				m_skillHeavyAtk.fPassedTime = 0.0f;
				LookTarget();
				ChangeState(E_STATE_SKILL, E_BOSS_HEAVYATK_START);
				return;
			}
			if (m_skillHeavyAtk2.fPassedTime >= m_skillHeavyAtk2.fCoolTime)
			{
				if (IsTargetCollision())
				{
					if (m_pAction)
						SAFE_RELEASE(m_pAction); 
					m_skillHeavyAtk2.fPassedTime = 0.0f;
					LookTarget();
					ChangeState(E_STATE_SKILL, E_BOSS_HEAVYATK2);
					return;
				}
			}
			if (m_skillAttack.fPassedTime >= m_skillAttack.fCoolTime)
			{
				if (IsTargetCollision())
				{
					if (m_pAction)
						SAFE_RELEASE(m_pAction);
					m_skillAttack.fPassedTime = 0.0f;
					LookTarget();
					ChangeState(E_STATE_SKILL, E_BOSS_ATK2);
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


void cOrca::LongMove()
{
//	RECT rect = RectMakeCenter(GetWindowWidth() / 2, 150, 500, 50);
//	GETSINGLE(cTextMgr)->AddText(E_FONT_BOSS, m_skillLongMove.sSpeech, 3, rect);
	GETSINGLE(cTextMgr)->AddList(m_skillLongMove.sSpeech);
	if (m_pAction)
		SAFE_RELEASE(m_pAction);
	m_skillLongMove.fPassedTime = 0.0f;
	m_nNumClone = 3;

	//본체
	D3DXVECTOR3 vEnemyPos = m_pTarget->GetPosition();
	int nRealOrca = GetInt(4);

	D3DXVECTOR3 vPos(0, 0, 0);
	switch (nRealOrca)
	{
	case 0:
		vPos = D3DXVECTOR3(30 * cosf(0), 0, 30 * sinf(0));
		break;
	case 1:
		vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 2), 0, 30 * sinf(D3DX_PI / 2));
		break;
	case 2:
		vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 3), 0, 30 * sinf(D3DX_PI / 4 * 3));
//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * -sinf(D3DX_PI / 4));
		break;
	case 3:
		vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 5), 0, 30 * sinf(D3DX_PI / 4 * 5));
//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * sinf(-D3DX_PI / 4));
		break;
	}

	SetPosition(vEnemyPos + vPos);
	LookTarget();

	//있으면 재사용
	auto cloneList = GETSINGLE(cObjMgr)->GetMonsterList("Orca_Clone");
	if (cloneList)
	{
		int i = 0;
		for (auto iter = cloneList->begin(); iter != cloneList->end(); i++)
		{
			if (i == nRealOrca)
				continue;

			D3DXVECTOR3 vPos(0, 0, 0);
			switch (i)
			{
			case 0:
				vPos = D3DXVECTOR3(30 * cosf(0), 0, 30 * sinf(0));
				break;
			case 1:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 2), 0, 30 * sinf(D3DX_PI / 2));
				break;
			case 2:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 3), 0, 30 * sinf(D3DX_PI / 4 * 3));
				//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * -sinf(D3DX_PI / 4));
				break;
			case 3:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 5), 0, 30 * sinf(D3DX_PI / 4 * 5));
				//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * sinf(-D3DX_PI / 4));
				break;
			}

			((cOrcaClone*)(*iter))->SetActive(true);
			((cOrcaClone*)(*iter))->SetMoveEnd(false);
			(*iter)->SetPosition(vEnemyPos + vPos);
			(*iter)->LookTarget();
			(*iter)->ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
			iter++;
		}
	}
	else
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, D3DX_PI / 2);

		for (int i = 0; i < 4; i++)
		{
			if (i == nRealOrca)
				continue;

			switch (i)
			{
			case 0:
				vPos = D3DXVECTOR3(30 * cosf(0), 0, 30 * sinf(0));
				break;
			case 1:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 2), 0, 30 * sinf(D3DX_PI / 2));
				break;
			case 2:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 3), 0, 30 * sinf(D3DX_PI / 4 * 3));
				//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * -sinf(D3DX_PI / 4));
				break;
			case 3:
				vPos = D3DXVECTOR3(30 * cosf(D3DX_PI / 4 * 5), 0, 30 * sinf(D3DX_PI / 4 * 5));
				//		vPos = D3DXVECTOR3(30 * -cosf(D3DX_PI / 4), 0, 30 * sinf(-D3DX_PI / 4));
				break;
			}

			cDynamicObj* clone = new cOrcaClone("Monster", "Orca.X");
			clone->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
			clone->SetRevision(matR);
			clone->SetPosition(vEnemyPos + vPos);
			clone->SetTarget(m_pTarget);
			clone->LookTarget();
			GETSINGLE(cObjMgr)->AddMonster("Orca_Clone", clone);
		}
	}
	ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
}


bool cOrca::IsBehind()
{
//	D3DXVECTOR3 vec = m_pTarget->GetPosition() - m_vPosition;
	D3DXVECTOR2 vec(m_pTarget->GetPosition().x - m_vPosition.x, m_pTarget->GetPosition().z - m_vPosition.z);
	D3DXVECTOR2 vec2(m_vDirection.x, m_vDirection.z);
	D3DXVec2Normalize(&vec, &vec);
	D3DXVec2Normalize(&vec2, &vec2);
	if (vec.x * vec2.x + vec.y * vec2.y >= sqrt(2) / 2)
		return true;
	return false;
}