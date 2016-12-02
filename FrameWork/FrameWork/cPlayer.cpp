#include "stdafx.h"
#include "cPlayer.h"
#include "cDynamicMesh.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cAnimationController.h"


cPlayer::cPlayer(char* szFolder, char* szFilename) //: cDynamicMesh(szFolder, szFilename)
	: m_pRightWeapon(NULL)
	, m_pLeftWeapon(NULL)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
	//임시
	SetupBaseWeapon();
	SetupState();
}


cPlayer::cPlayer()
	: m_pRightWeapon(NULL)
	, m_pLeftWeapon(NULL)
{
}


cPlayer::~cPlayer()
{
	for (int i = 0; i < E_STATE_END; i++)
	{
		SAFE_DELETE(m_pStates[i]);
	}

	//SAFE_DELETE(m_pStateIdle);
	//SAFE_DELETE(m_pStateRun);
	//SAFE_DELETE(m_pStateDefence);
	//SAFE_DELETE(m_pStateAttack);
}


void cPlayer::ChangeState(iState* pState)
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


void cPlayer::ChangeState(int pState)
{
	if (m_pState)
		if (m_pState == m_pStates[pState])
			return;

	iState* pPrevState = m_pState;
	m_pState = m_pStates[pState];

	if (pPrevState)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	m_pState->Start();
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
	m_pStates[E_STATE_IDLE] = new cStateIdle;
	m_pStates[E_STATE_IDLE]->SetParent(this);
	m_pStates[E_STATE_RUN] = new cStateRun;
	m_pStates[E_STATE_RUN]->SetParent(this);
	m_pStates[E_STATE_DEFENCE] = new cStateDefence;
	m_pStates[E_STATE_DEFENCE]->SetParent(this);
	m_pStates[E_STATE_COMBO] = new cStateCombo;
	m_pStates[E_STATE_COMBO]->SetParent(this);
	m_pStates[E_STATE_WAIT] = new cStateWait;
	m_pStates[E_STATE_WAIT]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cPlayer::CheckControl()
{
	if (KEYBOARD->IsStayKeyDown(DIK_W))
	{
		if (IsMoveAble())
		{
			m_vPosition = m_vPosition - m_vDirection * 0.1;
			ChangeState(E_STATE_RUN);
		}
	}
	else if (KEYBOARD->IsStayKeyDown(DIK_S))
	{
		if (IsMoveAble())
		{
			m_vPosition = m_vPosition + m_vDirection * 0.1;
			ChangeState(E_STATE_RUN);
		}
	}
	else
	{
		if (m_pState == m_pStates[E_STATE_RUN])
			ChangeState(E_STATE_WAIT);
	}
	if (KEYBOARD->IsStayKeyDown(DIK_A))
	{
		if (IsMoveAble())
			m_fAngle -= 0.1f;
	}
	else if (KEYBOARD->IsStayKeyDown(DIK_D))
	{
		if (IsMoveAble())
			m_fAngle += 0.1f;
	}

	/*if (KEYBOARD->IsOnceKeyDown(DIK_O))
	{
		ChangeState(E_STATE_IDLE);
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_P))
	{
		ChangeState(E_STATE_RUN);
	}*/
	if (KEYBOARD->IsOnceKeyDown(DIK_SPACE))
	{
		ChangeState(E_STATE_COMBO);
	}
	if (MOUSE->IsStayKeyDown(MOUSEBTN_RIGHT))
	{
		ChangeState(E_STATE_DEFENCE);
	}
	if (MOUSE->IsOnceKeyUp(MOUSEBTN_RIGHT))
	{
		ChangeState(E_STATE_WAIT);
	}


	if (KEYBOARD->IsOnceKeyDown(DIK_M))
	{
		//임시
		dlatl();
	}
}


void cPlayer::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	CheckControl();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
	
	if (m_pRightWeapon)
	{
		m_pRightWeapon->Update();
		m_pRightWeapon->Render();
	}
	if (m_pLeftWeapon)
	{
		m_pLeftWeapon->Update();
		m_pLeftWeapon->Render();
	}
}


bool cPlayer::IsMoveAble()
{
	if (m_pState == m_pStates[E_STATE_RUN] ||
		m_pState == m_pStates[E_STATE_IDLE] ||
		m_pState == m_pStates[E_STATE_WAIT])
		return true;
	return false;
}


void cPlayer::dlatl()
{
	m_pLeftWeapon = new cWeapon("Weapon", "Gauntlet04_L.X");
	m_pLeftWeapon->SetHolderKey("Popori", "Popori.X");
	m_pLeftWeapon->SetParentKey("FxHand00");
	m_pLeftWeapon->SetParentMat();


	m_pRightWeapon = new cWeapon("Weapon", "Gauntlet04_R.X");
	m_pRightWeapon->SetHolderKey("Popori", "Popori.X");
	m_pRightWeapon->SetParentKey("FxHand01");
	m_pRightWeapon->SetParentMat();
}