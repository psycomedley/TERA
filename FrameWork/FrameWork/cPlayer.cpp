#include "stdafx.h"
#include "cPlayer.h"
#include "cDynamicMesh.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cStateSkill.h"
#include "cStateDeath.h"
#include "cAnimationController.h"
#include "cCamera.h"
#include "cUITextView.h"
#include "cUIImageView.h"


cPlayer::cPlayer(char* szFolder, char* szFilename) //: cDynamicMesh(szFolder, szFilename)
	: m_pRightWeapon(NULL)
	, m_pLeftWeapon(NULL)
	, m_bIsBattle(false)
	, m_fWaitTime(IDLESWITCHTIME)
	, m_nKeyDir(DIRECTION_NONE)
	, m_fTempAngle(0.0f)
	/*, m_pArm(NULL)
	, m_pLeg(NULL)
	, m_pHead(NULL)*/
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);		//Body
//	m_pArm = new cDynamicObj(szFolder, "Popori_Arm.X");		//Arm
	//Leg
	//Head

	SetBoundingPos();
	SetupStatus();

	GETSINGLE(cUIMgr)->AddList("Player");
	m_pUIHp = GETSINGLE(cUIMgr)->GetUIInList("Player");

	//임시
	SetupBaseWeapon();
	SetupState();
}


cPlayer::cPlayer()
	: m_pRightWeapon(NULL)
	, m_pLeftWeapon(NULL)
	, m_bIsBattle(false)
	, m_fWaitTime(IDLESWITCHTIME)
	, m_nKeyDir(DIRECTION_NONE)
	, m_fTempAngle(0.0f)
	/*, m_pArm(NULL)
	, m_pLeg(NULL)
	, m_pHead(NULL)*/
{
	SetupStatus();
	GETSINGLE(cUIMgr)->AddList("Player");
	m_pUIHp = GETSINGLE(cUIMgr)->GetUIInList("Player");
}


cPlayer::~cPlayer()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);

	SAFE_RELEASE(m_pRightWeapon);
	SAFE_RELEASE(m_pLeftWeapon);

	//SAFE_DELETE(m_pStateIdle);
	//SAFE_DELETE(m_pStateRun);
	//SAFE_DELETE(m_pStateDefence);
	//SAFE_DELETE(m_pStateAttack);
}


void cPlayer::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
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
		((cStateSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


void cPlayer::ChangeState(int pState, int nSkillIndex /*= -1*/)
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
		((cStateSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


void cPlayer::Attack()
{
	ChangeState(E_STATE_COMBO);
}


void cPlayer::SetupBaseWeapon()
{
	m_pLeftWeapon = new cWeapon("Weapon", "Gauntlet00_L.X");
	m_pLeftWeapon->SetHolderKey("Popori", "Popori.X");
	m_pLeftWeapon->SetParentKey("FxHand00");
	m_pLeftWeapon->SetParentMat();


	m_pRightWeapon = new cWeapon("Weapon", "Gauntlet00_R.X");
	m_pRightWeapon->SetHolderKey("Popori", "Popori.X");
	m_pRightWeapon->SetParentKey("FxHand01");
	m_pRightWeapon->SetParentMat();
}


void cPlayer::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_DEFENCE] = new cStateDefence;
	m_aStates[E_STATE_DEFENCE]->SetParent(this);
	m_aStates[E_STATE_COMBO] = new cStateCombo;
	m_aStates[E_STATE_COMBO]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	m_aStates[E_STATE_DEATH] = new cStateDeath;
	m_aStates[E_STATE_DEATH]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cPlayer::CheckState()
{
	if (m_bIsBattle && m_pState == m_aStates[E_STATE_WAIT])
	{
		m_fWaitTime -= GETSINGLE(cTimeMgr)->getElapsedTime();
		if (m_fWaitTime <= 0.0f)
		{
			m_bIsBattle = false;
			ChangeState(m_aStates[E_STATE_IDLE]);
			m_fWaitTime = IDLESWITCHTIME;
		}
	}
	else if (m_bIsBattle)
		m_fWaitTime = IDLESWITCHTIME;
}


void cPlayer::CheckControl()
{
	bool bControl = false;
	m_nKeyDir = DIRECTION_NONE;
	if (KEYBOARD->IsStayKeyDown(DIK_W))
	{
		m_nKeyDir |= DIRECTION_UP;
		bControl = true;
	}
	if (KEYBOARD->IsStayKeyDown(DIK_S))
	{
		m_nKeyDir |= DIRECTION_DOWN;
		bControl = true;
	}
	if (KEYBOARD->IsStayKeyDown(DIK_A))
	{
		m_nKeyDir |= DIRECTION_LEFT;
		bControl = true;
	}
	if (KEYBOARD->IsStayKeyDown(DIK_D))
	{
		m_nKeyDir |= DIRECTION_RIGHT;
		bControl = true;
	}

	//이동
	if (m_nKeyDir == DIRECTION_NONE)
	{
		if (m_pState == m_aStates[E_STATE_RUN])
		{
			if (m_bIsBattle)
				ChangeState(E_STATE_WAIT);
			else
				ChangeState(E_STATE_IDLE);
		}
	}
	else
	{
		float fCameraAngle = CAMERA->GetCamRotX();
//		float fAngle = 0;
		m_fTempAngle = 0.0f;
		int nKeys = 0;

		if (m_nKeyDir & DIRECTION_UP)
			nKeys++;
		if (m_nKeyDir & DIRECTION_DOWN)
		{
			m_fTempAngle += D3DX_PI;
			nKeys++;
		}
		if (m_nKeyDir & DIRECTION_LEFT)
		{
			m_fTempAngle -= D3DX_PI / 2;
			nKeys++;
			if (m_nKeyDir & DIRECTION_DOWN)
				m_fTempAngle += D3DX_PI * 2;
		}
		else if (m_nKeyDir & DIRECTION_RIGHT)
		{
			m_fTempAngle += D3DX_PI / 2;
			nKeys++;
		}
		if (nKeys >= 2)
			m_fTempAngle /= 2;

//		m_fAngle = fCameraAngle + fAngle;

		if (IsMoveAble())
		{
			m_fAngle = fCameraAngle + m_fTempAngle;
			m_vPosition = m_vPosition - m_vDirection * 0.1;
			ChangeState(E_STATE_RUN);
			bControl = true;
		}
	}


	if (KEYBOARD->IsOnceKeyDown(DIK_1))
	{
		if (IsMoveAble())
		{
			ChangeState(E_STATE_SKILL, E_ANI_STRIKE);
			m_bIsBattle = true;
			bControl = true;
		}
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_2))
	{
		if (IsMoveAble())
		{
			ChangeState(E_STATE_SKILL, E_ANI_DOUBLEATTACK);
			m_bIsBattle = true;
			bControl = true;
		}
	}

	if (KEYBOARD->IsOnceKeyDown(DIK_M))
	{
		//임시
		dlatl();
	}


	//마우스 좌,우클릭은 ESC 눌렸을 때 작동 안함
	if (CAMERA->GetControl())
	{
		if (MOUSE->IsStayKeyDown(MOUSEBTN_LEFT))
		{
			if (m_pState != m_aStates[E_STATE_SKILL])
			{
				if (m_nKeyDir == DIRECTION_NONE &&
					m_pState != m_aStates[E_STATE_COMBO])
					m_fAngle = GETSINGLE(cCameraMgr)->GetCamera()->GetCamRotX();
				ChangeState(E_STATE_COMBO);
				m_bIsBattle = true;
			}
		}
		if (MOUSE->IsStayKeyDown(MOUSEBTN_RIGHT))
		{
			ChangeState(E_STATE_DEFENCE);
		}
		if (MOUSE->IsOnceKeyUp(MOUSEBTN_RIGHT))
		{
			if (m_bIsBattle)
				ChangeState(E_STATE_WAIT);
			else
				ChangeState(E_STATE_IDLE);
		}
	}

	if (bControl == true && !CAMERA->GetControl())
	{
		CAMERA->SetControl(true);
		ShowCursor(false);
		GETSINGLE(cUIMgr)->AddList("CrossHair");
	}
}


void cPlayer::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	UpdateUI();
	CheckState();
	m_pState->Update();
	CheckControl();
	cDynamicObj::UpdateAndRender(pmat);
//	GetBox();
//	m_pArm->UpdateAndRender();
	
	if (m_pRightWeapon)
	{
		m_pRightWeapon->Update();
		m_pRightWeapon->Render();
		m_pRightWeapon->Bounding_Render();
		m_pRightWeapon->GetBox();
	}
	if (m_pLeftWeapon)
	{
		m_pLeftWeapon->Update();
		m_pLeftWeapon->Render();
		m_pLeftWeapon->Bounding_Render();
	}
}


bool cPlayer::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_IDLE] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cPlayer::dlatl()
{
	SAFE_RELEASE(m_pLeftWeapon);
	m_pLeftWeapon = new cWeapon("Weapon", "Gauntlet04_L.X");
	m_pLeftWeapon->SetHolderKey("Popori", "Popori.X");
	m_pLeftWeapon->SetParentKey("FxHand00");
	m_pLeftWeapon->SetParentMat();

	SAFE_RELEASE(m_pRightWeapon);
	m_pRightWeapon = new cWeapon("Weapon", "Gauntlet04_R.X");
	m_pRightWeapon->SetHolderKey("Popori", "Popori.X");
	m_pRightWeapon->SetParentKey("FxHand01");
	m_pRightWeapon->SetParentMat();
}


void cPlayer::SetScale(D3DXVECTOR3 vScale)
{
	cGameObject::SetScale(vScale);
//	m_pLeftWeapon->SetScale(vScale);
//	m_pRightWeapon->SetScale(vScale);
}


void cPlayer::UpdateUI()
{
	float fHpRatio = m_stInfo.fHp / m_stInfo.fMaxHp;
	float fMpRatio = m_stInfo.fMp / m_stInfo.fMaxMp;

	char szStr[16] = { '\0', };
	//HP
	sprintf_s(szStr, sizeof(szStr), "%.0f / %.0f", m_stInfo.fHp, m_stInfo.fMaxHp);
	((cUITextView*)m_pUIHp->FindChildByTag(E_UITAG_HPTEXT))->SetText(szStr);
	((cUIImageView*)m_pUIHp->FindChildByTag(E_UITAG_HP))->SetScaleX(fHpRatio * 1.5f);
	//MP
	sprintf_s(szStr, sizeof(szStr), "%.0f / %.0f", m_stInfo.fMp, m_stInfo.fMaxMp);
	((cUITextView*)m_pUIHp->FindChildByTag(E_UITAG_MPTEXT))->SetText(szStr);
	((cUIImageView*)m_pUIHp->FindChildByTag(E_UITAG_MP))->SetScaleX(fMpRatio * 1.5f);
}


void cPlayer::SetupStatus()
{
	m_stInfo.sName = "Player";

	m_stInfo.fMaxHp = 2438;
	m_stInfo.fHp = m_stInfo.fMaxHp;
	m_stInfo.fMaxMp = 1100;
	m_stInfo.fMp = m_stInfo.fMaxMp;

	m_stInfo.fDamage = 197.0f;
	m_stInfo.fDefence = 29.0f;
}