#include "stdafx.h"
#include "cBoss.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cStateSkill.h"
#include "cAnimationController.h"


cBoss::cBoss(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
}


cBoss::cBoss()
{
}


cBoss::~cBoss()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cBoss::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	CheckState();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cBoss::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	/*m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_DEFENCE] = new cStateDefence;
	m_aStates[E_STATE_DEFENCE]->SetParent(this);
	m_aStates[E_STATE_COMBO] = new cStateCombo;
	m_aStates[E_STATE_COMBO]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);*/
	ChangeState(E_STATE_IDLE);
}


void cBoss::CheckState()
{

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
		((cStateSkill*)m_pState)->SetSkillIndex(nSkillIndex);

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
